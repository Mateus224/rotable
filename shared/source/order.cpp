#include "order.h"
#include <QtGui>

//------------------------------------------------------------------------------

#ifndef QJSONARRAY_H
#include <QJsonArray>
#endif

//------------------------------------------------------------------------------

using namespace rotable;

//rotable::Order::Order(const QJsonValue& jval, QObject* parent)
//  : Order(parent)
//{

//}

//------------------------------------------------------------------------------

Order::Order(QObject* parent)
: QObject(parent), _change(false)
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

void Order::recalcChange()
{
    foreach(OrderItem* item, _items)
        if(item->isReadyToChange())
        {
            _change =  true;
            return;
        }
    _change =  false;
}

//------------------------------------------------------------------------------

QQmlListProperty<OrderItem> Order::doneItems()
{

    QList<rotable::OrderItem*> items;
    foreach(OrderItem* item, _items)
        if(item->isDone())
            items.append(item);

    return QQmlListProperty<OrderItem>(this, items);
}

//------------------------------------------------------------------------------

QQmlListProperty<OrderItem> Order::unDoneItems()
{

    QList<rotable::OrderItem*> items;
    foreach(OrderItem* item, _items)
        if(!item->isDone())
            items.append(item);

    return QQmlListProperty<OrderItem>(this, items);
}

//------------------------------------------------------------------------------

QJsonValue Order::toJSON() const
{
    QJsonObject o;

    o["id"] = _id;
    o["state"] = _state;
    o["waiterState"] = _waiterState;
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
        && o.contains("waiterState")
        && o.contains("clientId")
        && o.contains("timeSend")
        && o.contains("items")
        )
    {
      // Create new OrederItem base one JSON
      Order* order = new Order();
      order->_id = o["id"].toInt();
      order->_state = o["state"].toInt();
      order->_waiterState = o["waiterState"].toInt();
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

    if (isNew())
        setState(rotable::Order::Sent);
    else if (isToPay())
        setState(rotable::Order::Prepared);
    else if(isDone())
        setState(rotable::Order::Close);
}

void Order::RemoveProductAmount()
{
    foreach (OrderItem* item, _items) {
        if(item->isReadyToChange()){
            item->setAmount(item->amount()-1);
        }
    }
}

//------------------------------------------------------------------------------

void Order::changeWaiterState(int state)
{
    if (_readyToChangeWStatus) _waiterState = state;
    _readyToChangeWStatus = false;
}

//------------------------------------------------------------------------------

void Order::prepareOrderToChange()
{
//   static int changeStatus = true;
   foreach(OrderItem *item, _items){
//        item->setChange(changeStatus);
       item->setChange(true);
   }
   _readyToChangeWStatus = true;
//   changeStatus = !changeStatus;
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

bool Order::isClose() const
{
    if(_state == Order::Close || _state == Order::Paid)
        return true;
    return false;
}

//------------------------------------------------------------------------------

bool Order::isDone() const
{
    //We check if any item is not done

    foreach (OrderItem *item, _items) {
        if(!item->isDone())
            return false;       // Not done so we return false
    }

    return true;
}

//------------------------------------------------------------------------------

bool Order::isUnDone() const
{
    //We check if any item is done

    foreach (OrderItem *item, _items) {
        if(item->isDone())
            return false;       // Done so we return false
    }

    return true;
}

//------------------------------------------------------------------------------

bool Order::isNew() const
{
    //We check if any item is new

    foreach (OrderItem *item, _items) {
        if(item->isNew())
            return true;       // Yes, so we return true
    }

    return false;
}

bool Order::isToPay() const
{
    //Checks if any item is toPay/Accepred by waiter
    foreach (OrderItem *item, _items) {
        if(item->isToPay())
            return true;       // Yes, so we return true
    }

    return false;
}

//------------------------------------------------------------------------------

int Order::countProducts()
{
  int count = 0;
  for(auto item: _items)
  {
    if(item->isNew())
      ++count;
  }
  return count;
}

//------------------------------------------------------------------------------

void Order::itemChanged()
{
    recalcChange();
    emit itemsChanged();
}

//------------------------------------------------------------------------------

void Order::forceSend() { emit forceSendRequest(); }

//------------------------------------------------------------------------------

void Order::itemIsReadyToChanged()
{
    OrderItem* item = dynamic_cast<OrderItem*>(QObject::sender());
    if(item)
        emit readyToChanged(item->isReadyToChange());
}

//------------------------------------------------------------------------------

void Order::checkOrderState()
{
    switch (state()) {
    case State::Sent:
        if(!isNew())
            setState(State::Prepared);
    case State::Prepared:
        if(isDone())
            setState(State::Close);
    }
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
