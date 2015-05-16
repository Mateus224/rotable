#include "private/precomp.h"
#include "productorder.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ProductOrder::ProductOrder( ProductContainer &productcontainer, QObject *parent) : QObject(parent), _productcontainer(productcontainer)
{
    ClientProductHash=new QHash<int,productChoosen>;
    ClientProductHash->reserve(250);
    _quantity=0;
    //ProductList=new QList<QObject*>;


}

ProductOrder::ProductOrder::~ProductOrder()
{

}


//------------------------------------------------------------------------------

void ProductOrder::addProductToOrder(int id)
{
    //L_quantity->append(_productId);
    //L_OrderList->append(_quantity);
}

void ProductOrder::removeProductFromOrder(int id)
{

}

void ProductOrder::sendOrderToServer()
{

}

void ProductOrder::sendOrderToWaitor()
{

}

void ProductOrder::acceptOrder()
{

}

void ProductOrder::setStopWatchTime()
{

}

int ProductOrder::getStopWatchTime()
{

    return 0;
}

int ProductOrder::sendWaitTimeForClient()
{

    return 0;
}
//------------------------------------------------------------------------------

void ProductOrder::setproductId(int productId)
{

}
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------

  void ProductOrder::getListForMyOrderPage()
  {
      _productcontainer._orderProducts->clear();
      QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
      while (i != ClientProductHash->constEnd()) {
            if (_productcontainer._products->contains(i.value()._s_id)) {
                _productcontainer.addForOrderProduct_(i.value()._s_id);
                _productcontainer._orderProducts->value(i.value()._s_id)->setAmount(QString::number(i.value()._s_quantity));
           }
          ++i;
      }
  }

//------------------------------------------------------------------------------

ProductOrder *ProductOrder::fromJSON(const QJsonValue &jval)
{

    QJsonObject o = jval.toObject();

    if (o.contains("name")
        && o.contains("info")
        && o.contains("icon")
        && o.contains("id")
        && o.contains("price")
        && o.contains("categoryId")
        && o.contains("amount"))
    {
        //ProductOrder* p = new ProductOrder();
        //p->_name = o["name"].toString();
        //p->_info = o["info"].toString();
       // p->_icon = o["icon"].toString();
        //p->_id = o["id"].toInt();
        //p->_price = o["price"].toInt();
        //p->setPrice(p->_price);
        //p->_categoryId = o["categoryId"].toInt();
       // p->_amount = o["amount"].toString();

        //return p;
    }
    return 0;

}

QJsonValue ProductOrder::toJSON() const
{
        return 0;
}

//------------------------------------------------------------------------------
//get Gui Information
//------------------------------------------------------------------------------


void ProductOrder::addToProductHash(int ProductID)
{
    if(ClientProductHash->contains(ProductID))
    {
        _Product=ClientProductHash->take(ProductID);
        _Product._s_quantity++;
        ClientProductHash->insert(_Product._s_id, _Product);
        /*
        QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
        while (i != ClientProductHash->constEnd()) {
            qDebug() <<  "quantity: " << i.value()._s_quantity <<  "id: " << i.value()._s_id ;
            ++i;
        }*/
        setquantity(_Product._s_quantity);

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
        setquantity(1);
    }

}

//-----------------------------------------------------------------

void ProductOrder::setquantity( int quantity)
{
    _Product._s_quantity = quantity;
    emit quantityChanged();
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
                setquantity(_Product._s_quantity);
                QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();

                while (i != ClientProductHash->constEnd())
                {
                    qDebug() <<  "rm; quantity: " << i.value()._s_quantity <<  "id: " << i.value()._s_id ;
                    ++i;
                }
            }
            else if(_Product._s_quantity==1)
            {
                setquantity(0);
                ClientProductHash->remove(ProductID); //take(ProductID);
            }
        }
    }
    else
    {
        qDebug()<<"Fehler in rmFromProductHash2";
    }

    setquantity(_Product._s_quantity);
}

//-----------------------------------------------------------------

void ProductOrder::getQuantity(int ProductID)
{
    if(ClientProductHash->contains(ProductID))
    {
        _Product=ClientProductHash->take(ProductID);
        ClientProductHash->insert(_Product._s_id,_Product);
        setquantity (_Product._s_quantity);
    }
    else
    {
        int zero=0;
        setquantity (zero);
    }
}
