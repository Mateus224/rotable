#include "private/precomp.h"
#include "productorder.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ProductOrder::ProductOrder( ProductContainer &productcontainer, QObject *parent) : QObject(parent), _productcontainer(productcontainer)
{
    ClientProductHash=new QHash<int,productChoosen>;
    ClientProductHash->reserve(250);

}


void ProductOrder::sendOrderToServer()
{
    qDebug()<<"sending";
}


void ProductOrder::acceptOrder()
{

}



int ProductOrder::getStopWatchTime()
{
    return 0;
}



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

    if (o.contains("id")
        && o.contains("pieces")
        && o.contains("orderState")
        && o.contains("waitingTime")
        && o.contains("orderID"))
    {
        //ProductOrder* p = new ProductOrder(*_productcontainer);
        //p->_id = o["id"].toInt();
        //p->_pieces = o["pieces"].toInt();
        //p->_orderState = o["orderState"].toInt();
        //p->_waitingTime = o["waitingTime"].toInt();

        //return p;
    }
    return 0;

}

QJsonValue ProductOrder::toJSON() const
{
    /*QJsonObject o;
    o["id"] = _id;
    o["pieces"] = _categoryId;
    o["orderState"] = _name;
    o["waitingTime"] = _icon;*/

    //return QJsonValue(o);
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
