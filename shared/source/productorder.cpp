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

}


//------------------------------------------------------------------------------

ComPackageDataSet ProductOrder::prepareOrderToSend() const
{
    QJsonArray array;
    QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
    while (i != ClientProductHash->constEnd()) {
        if (_productcontainer._products->contains(i.value()._s_id)){
            OrderItem item;
            item.setId(i.value()._s_id);
            item.setAmount(i.value()._s_quantity);
            array.append(item.toJSON());
        }
        ++i;
    }
    ComPackageDataSet sendOrder;
    sendOrder.setDataCategory(ComPackage::SetOrder);
    sendOrder.setData(array);
    return sendOrder;
}

//------------------------------------------------------------------------------

void ProductOrder::acceptOrder()
{

}

//------------------------------------------------------------------------------

int ProductOrder::getStopWatchTime()
{
    return 0;
}

<<<<<<< HEAD
//------------------------------------------------------------------------------

void ProductOrder::getListForMyOrderPage()
{
    _productcontainer._orderProducts->clear();
    QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
    while (i != ClientProductHash->constEnd())
    {
        if (_productcontainer._products->contains(i.value()._s_id))
        {
            _productcontainer.addForOrderProduct_(i.value()._s_id);
            _productcontainer._orderProducts->value(i.value()._s_id)->setAmount(QString::number(i.value()._s_quantity));
        }
    ++i;
    }
=======
//------------------------------------------------------------------------------

void ProductOrder::getListForMyOrderPage()
{
    _productcontainer._orderProducts->clear();
    QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
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

////ProductOrder *ProductOrder::fromJSON(const QJsonValue &jval)
////{

////    QJsonObject o = jval.toObject();

////    if ( o.contains("pieces"))
////        && o.contains("orderState")
////        && o.contains("waitingTime")
////        && o.contains("orderID")
///         && o.contains("clientID"))
////    {
////        //ProductOrder* p = new ProductOrder(*_productcontainer);
////        //p->_id = o["id"].toInt();
////        //p->_pieces = o["pieces"].toInt();
////        //p->_orderState = o["orderState"].toInt();
////        //p->_waitingTime = o["waitingTime"].toInt();
////        //p->_clientID= o["tableID"].toInt();

////        //return p;
////    }
////}

//------------------------------------------------------------------------------

QJsonValue ProductOrder::toJSON(int id, int pieces) const
{
    QJsonObject o;
    o["ID"] = id;
    o["pieces"] = pieces;
    ////o["tableID"] = _clientID;

    return QJsonValue(o);
>>>>>>> 5f42123cbf2b039f8425a37c4ede58ac7972ed15
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
            qDebug() <<  "first; quantity: " << i.value()._s_quantity <<  "id: " << i.value()._s_id ;
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
            }
        }
    }
    else
    {
        qDebug()<<"Fehler in rmFromProductHash2";
    }
    setpieces(_Product._s_quantity);
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


