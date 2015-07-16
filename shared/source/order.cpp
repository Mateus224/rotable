#include "order.h"

//------------------------------------------------------------------------------

#ifndef QJSONARRAY_H
#include <QJsonArray>
#endif

//------------------------------------------------------------------------------

using namespace rotable;

rotable::Order::Order(const QJsonValue& jval, QObject* parent)
  : QObject(parent)
{

}

//------------------------------------------------------------------------------

Order::Order(QObject* parent)
: QObject(parent)
{

}

//------------------------------------------------------------------------------

Order::~Order()
{
    // Clear memory from pointers
    qDeleteAll(_items.begin(), _items.end());
    _items.clear();     //Clear list
}

//------------------------------------------------------------------------------

QJsonValue Order::toJSON() const
{
    QJsonObject o;

    o["id"] = _id;
    o["state"] = _state;
    o["clientId"] = _clientId;
    o["timeSend"] = _timeSent.toString();

    // Convert list of OrderItem to JSON array
    QJsonArray arr;
    foreach(OrderItem* item, _items){
        arr.append(item->toJSON());
    }

    QJsonValue value(arr);
    o["items"] = value;

    return QJsonValue(o);
}

//------------------------------------------------------------------------------

rotable::Order *Order::fromJSON(const QJsonValue &jval)
{
    QJsonObject o = jval.toObject();
    // Check if all requaier fields are exists
    if (o.contains("id")
        && o.contains("state")
        && o.contains("clientId")
        && o.contains("timeSend")
        && o.contains("items")
        )
    {
      // Create new OrederItem base one JSON
      Order* order = new Order();
      order->_id = o["id"].toInt();
      order->_state = o["state"].toInt();
      order->_clientId = o["clientId"].toInt();
      //Conver to string and next to QDateTime
      order->_timeSent = QDateTime::fromString(o["timeSend"].toString());

      QJsonArray array = o["items"].toArray();
      foreach(QJsonValue value, array){
         order->addItem(OrderItem::fromJSON(value));
      }

      return order;
    }

    return 0;
}

//------------------------------------------------------------------------------

QJsonValue OrderItem::toJSON() const
{
    QJsonObject o;
    o["id"] = _id;
    o["amount"] = _amount;

    return QJsonValue(o);
}

//------------------------------------------------------------------------------

rotable::OrderItem *OrderItem::fromJSON(const QJsonValue &jval)
{
    QJsonObject o = jval.toObject();
    // Check if all requaier fields are exists
    if (o.contains("id")
        && o.contains("amount")
        )
    {
      // Create new OrederItem base one JSON
      OrderItem* oi = new OrderItem();
      oi->_id = o["id"].toInt();
      oi->_amount = o["amount"].toInt();


      return oi;
    }

    return 0;
}

//------------------------------------------------------------------------------

OrderItem::OrderItem(QObject *parent): QObject(parent)
{

}

//------------------------------------------------------------------------------
