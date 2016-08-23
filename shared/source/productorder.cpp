#include "private/precomp.h"
#include "productorder.h"
#include "order.h"
#include <QJsonArray>

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ProductOrder::ProductOrder( ProductContainer &productcontainer, QObject *parent) : QObject(parent), _productcontainer(productcontainer)
{
    ClientProductHash=new QHash<int,productChoosen>;
    ClientProductHash->reserve(250);
    _acceptOrder=1;
}


//------------------------------------------------------------------------------

ComPackageDataSet ProductOrder::prepareOrderToSend() const
{
    //if(acceptOrder())
    QJsonArray array;
    QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
    while (i != ClientProductHash->constEnd()) {
        if (_productcontainer._products->contains(i.value()._s_id)){
            OrderItem item;
            item.setProductId(i.value()._s_id);
            item.setAmount(i.value()._s_quantity);
            item.setState(rotable::OrderItem::New);
            item.setPrice(0); //ToDo: Get property price
            item.setTime(QTime(0,0,0));
            array.append(item.toJSON());
        }
        ++i;
    }
    ComPackageDataSet sendOrder;
    if(array.count() != 0)
        sendOrder.setDataCategory(ComPackage::SetOrder);
    else
        //If we don't have items change datacategory to invalid
        sendOrder.setDataCategory((ComPackage::DataSetCategory)-1);
    sendOrder.setData(array);
    return sendOrder;
}

//------------------------------------------------------------------------------

bool ProductOrder::b_acceptOrder()
{
    if(!ClientProductHash->empty())
    {
        _acceptOrder=1;
        _s_acceptOrder=tr("Sending...");
    }
    else
    {
        _acceptOrder=0;
        _s_acceptOrder= tr("Order is Empty");
    }
    setacceptOrder();
    return _acceptOrder;
}

void ProductOrder::setacceptOrder(){
    if(this->_s_acceptOrder.compare(tr("Sending..."))==0){
        QTimer::singleShot(2000, this, SLOT(OrderQueueTextSlot()));

    }
    emit acceptOrderChanged();
}

void ProductOrder::OrderQueueTextSlot(){
    this->_s_acceptOrder=tr("orders before you");
    setacceptOrder();
}

//------------------------------------------------------------------------------

int ProductOrder::getStopWatchTime()
{
    return 0;
}

//------------------------------------------------------------------------------

void ProductOrder::getListForMyOrderPage()
{
    QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
   _productcontainer._orderProducts->clear();
    while (i != ClientProductHash->constEnd())
    {

        if (_productcontainer._products->contains(i.value()._s_id))
        {
            _productcontainer.addForOrderProduct_(i.value()._s_id);
            _productcontainer._orderProducts->value(i.value()._s_id)->setAmount(QString::number(i.value()._s_quantity));
        }
    ++i;
    }
}

//------------------------------------------------------------------------------
void ProductOrder::addProductFromGuiTo_orderProducts(int ProductID){
    if (_productcontainer._products->contains(ProductID))
    {
        if(!_productcontainer._orderProducts->contains(ProductID))
            _productcontainer.addForOrderProduct_(ProductID);
        _productcontainer._orderProducts->value(ProductID)->setAmount(QString::number(_Product._s_quantity));
    }
    _productcontainer.updateProduct(_productcontainer.product(ProductID));
    emit AmountChanged();
    setPriceOfOrder();
}

//------------------------------------------------------------------------------
void ProductOrder::removeProductFromGuiTo_orderProducts(int ProductID){
    if (_productcontainer._products->contains(ProductID))
    {
        _productcontainer._orderProducts->value(ProductID)->setAmount(QString::number(_Product._s_quantity));
        emit AmountChanged();
        setPriceOfOrder();
    }
}


//------------------------------------------------------------------------------
//get Gui Information client
//------------------------------------------------------------------------------


void ProductOrder::addToProductHash(int ProductID)
{
    if(ClientProductHash->contains(ProductID))
    {
        _Product=ClientProductHash->take(ProductID);
        _Product._s_quantity++;
        ClientProductHash->insert(_Product._s_id, _Product);
        setpieces(_Product._s_quantity);
    }
    else
    {
        productChoosen* _Product=new productChoosen;
        _Product->_s_id=ProductID;
        _Product->_s_quantity=1;
        ClientProductHash->insert(_Product->_s_id,*_Product);
        QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
        while (i != ClientProductHash->constEnd()) {
            ++i;
        }
        setpieces(1);
    }

}

//-----------------------------------------------------------------

void ProductOrder::setpieces( int quantity)
{
    _Product._s_quantity = quantity;
    emit piecesChanged();
}

//-----------------------------------------------------------------

void ProductOrder::rmFromProductHash(int ProductID)
{
    if(ClientProductHash->contains(ProductID))
    {
        _Product=ClientProductHash->take(ProductID);
        if(_Product._s_quantity>0)
        {
            if(_Product._s_quantity>1)
            {
                _Product._s_quantity--;
                ClientProductHash->insert(_Product._s_id,_Product);
                setpieces(_Product._s_quantity);
            }
            else if(_Product._s_quantity==1)
            {
                setpieces(0);
                ClientProductHash->remove(ProductID); //take(ProductID);
                if(ClientProductHash->empty())
                {
                    ClientProductHash->clear();
                }
            }
        }
    }
    else
    {
        qDebug()<<"Fehler in rmFromProductHash2";
    }
    setpieces(_Product._s_quantity);
    setPriceOfOrder();
}

//-----------------------------------------------------------------

void ProductOrder::getpieces(int ProductID)
{
    if(ClientProductHash->contains(ProductID))
    {
        _Product=ClientProductHash->take(ProductID);
        ClientProductHash->insert(_Product._s_id,_Product);
        setpieces (_Product._s_quantity);
    }
    else
    {
        setpieces (0);
    }
}

//-----------------------------------------------------------------

double ProductOrder::setPriceOfOrder()
{
    _toPay=0;
    QHash<int, rotable::Product*>::const_iterator i = _productcontainer._orderProducts->constBegin();
    while (i != _productcontainer._orderProducts->constEnd())
    {
        QString qs_amountOfOrderedProduct=_productcontainer._orderProducts->value(i.value()->id())->amount();
        int amountOfOrderedProduct=qs_amountOfOrderedProduct.toInt();
        double priceOfOrderedProduct=_productcontainer._orderProducts->value(i.value()->id())->price();
        _toPay+=amountOfOrderedProduct*priceOfOrderedProduct;
    ++i;
    }
    _toPay=_toPay/100;
    emit PriceOfOrderChanged();
    return _toPay;
}

//-----------------------------------------------------------------
void ProductOrder::clearList(){
    _productcontainer._orderProducts->clear();
    AmountChanged();
    ClientProductHash->clear();
}

void ProductOrder::clearGuiList(){

}
