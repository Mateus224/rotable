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

void Order::updateOrder(rotable::Order *order)
{
    if(state() != order->state())
    {
        setState(order->state());
    }

    //That should never be happened
    if(itemCount() != order->itemCount())
        qCritical() << "Order items count are different!!";

    int count = order->itemCount();
    for(int i=0; i < count; ++i)
        _items[i]->updateOrderItem(order->_items[i]);

}

//------------------------------------------------------------------------------

void Order::changeState(int state)
{
    foreach (OrderItem* item, _items) {
        if(item->isReadyToChange()){
            item->setState(state);
        }
    }
}

void Order::prepareOrderToChange()
{
   static int changeStatus = true;
   foreach(OrderItem *item, _items){
        item->setChange(changeStatus);
   }
   changeStatus = !changeStatus;
}

//------------------------------------------------------------------------------

void Order::disconnectOrder()
{
    disconnect(this, &Order::readyToChanged, 0, 0);
}

//------------------------------------------------------------------------------

double Order::toPay()
{
    double sum = 0;
    foreach (OrderItem *item, _items) {
        sum += item->toPay();
    }

    return sum;
}

//------------------------------------------------------------------------------

void Order::closeOrder(QList<int> toChange, int newState)
{
    foreach(OrderItem *item, _items)
        if(toChange.contains(item->state()))
            item->setState(newState);

    setState(Close);
}

//------------------------------------------------------------------------------

void Order::itemChanged()
{
    emit itemsChanged();
}

//------------------------------------------------------------------------------

void Order::itemIsReadyToChanged()
{
    OrderItem* item = dynamic_cast<OrderItem*>(QObject::sender());
    if(item)
        emit readyToChanged(item->isReadyToChange());
}

//------------------------------------------------------------------------------

QJsonValue OrderItem::toJSON() const
{
    QJsonObject o;
    o["id"] = _id;
    o["productId"] = _productId;
    o["state"] = _state;
    o["amount"] = _amount;
    o["price"] = _price;
    o["time"] = _time.msec();

    return QJsonValue(o);
}

//------------------------------------------------------------------------------

rotable::OrderItem *OrderItem::fromJSON(const QJsonValue &jval)
{
    QJsonObject o = jval.toObject();
    // Check if all requaier fields are exists
    if (o.contains("id")
        && o.contains("amount")
        && o.contains("productId")
        && o.contains("state")
        && o.contains("price")
        && o.contains("time")
        )
    {
      // Create new OrederItem base one JSON
      OrderItem* oi = new OrderItem();
      oi->_id = o["id"].toInt();
      oi->_amount = o["amount"].toInt();
      oi->_productId = o["productId"].toInt();
      oi->_state = o["state"].toInt();
      oi->_price = o["price"].toDouble();
      QTime time; time = time.addMSecs(o["time"].toInt());
      oi->_time = time;

      return oi;
    }

    return 0;
}

//------------------------------------------------------------------------------

void OrderItem::updateOrderItem(rotable::OrderItem *item)
{
    if(amount() != item->amount())
        setAmount(item->amount());

    if(state() != item->state())
            setState(item->state());


    if(time() != item->time())
            setTime(item->time());


}

//------------------------------------------------------------------------------


OrderItem::OrderItem(QObject *parent): QObject(parent), _readyToChange(false)
{

}

//------------------------------------------------------------------------------
