#include "order.h"

using namespace rotable;

rotable::Order::Order(const QJsonValue& jval, QObject* parent)
  : QObject(parent)
{

}

Order::Order(QObject* parent)
: QObject(parent)
{

}

QJsonValue OrderItem::toJSON() const
{
    QJsonObject o;
    o["id"] = _id;
    o["amount"] = _amount;

    return QJsonValue(o);
}

rotable::OrderItem *OrderItem::fromJSON(const QJsonValue &jval)
{
    QJsonObject o = jval.toObject();

    if (o.contains("id")
        && o.contains("amount")
        )
    {
      OrderItem* oi = new OrderItem();
      oi->_id = o["id"].toInt();
      oi->_amount = o["amount"].toInt();


      return oi;
    }

    return 0;
}


OrderItem::OrderItem(QObject *parent): QObject(parent)
{

}
