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
