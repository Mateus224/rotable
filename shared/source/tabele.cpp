#include "table.h"
using namespace rotable;

//------------------------------------------------------------------------------

Table::~Table()
{
    // Delete all orders
    qDeleteAll(_orders.begin(), _orders.end());
    _orders.clear();     //Clear map
}

//------------------------------------------------------------------------------

Table::Table(QObject *parent): rotable::Client(parent), _change(false), _waiterIsNeeded(false)
{

}

//------------------------------------------------------------------------------

void Table::updateOrder(rotable::Order* order){
    // Check if order contains order
    if(_orders.contains(order->id()))
    {
        _orders.value(order->id())->updateOrder(order);
        delete order;
    }
    else
    {
        // Add order
        _orders[order->id()] = order;
        connect(order, &rotable::Order::itemsChanged, this, &rotable::Table::orderChanged);
    }
    emit tableChanged();
    //Change are made, set change value on true
}

//------------------------------------------------------------------------------

void Table::updateTableStatus(const rotable::Table *table)
{
    // Change value create
    bool change = false;

    // Check if something change
    if(_waiterIsNeeded != table->_waiterIsNeeded)
    {
        // Change so we set change
        change = true;
        _waiterIsNeeded = table->_waiterIsNeeded;
    }

    // We do logic OR
    _change = _change || change;
}

//------------------------------------------------------------------------------

QList<rotable::Order*> Table::orderList()
{
    return _orders.values();
}

//------------------------------------------------------------------------------

bool Table::hasOrder(const int &orderId) const
{
    if(_orders.contains(orderId))
        return true;
    return false;
}

//------------------------------------------------------------------------------

QJsonValue Table::toJSON() const
{
    QJsonObject o;

    o["id"] = _id;
    o["connected"] = _isConnected;
    o["waiterIsNeeded"] = _waiterIsNeeded;
    o["name"] = _name;

    return QJsonValue(o);
}

//------------------------------------------------------------------------------

rotable::Table *Table::fromJSON(const QJsonValue &jval)
{
    QJsonObject o = jval.toObject();
    // Check if all requaier fields are exists
    if (o.contains("id")
        && o.contains("connected")
        && o.contains("waiterIsNeeded")
        && o.contains("name")
        )
    {
      // Create new OrederItem base one JSON
      Table* table = new Table();
      table->_id = o["id"].toInt();
      table->_isConnected = o["connected"].toBool();
      table->_waiterIsNeeded = o["waiterIsNeeded"].toBool();
      table->_name = o["name"].toString();

      return table;
    }

    return 0;
}

//------------------------------------------------------------------------------

void Table::orderChanged()
{
    _change = true;
    emit tableChanged();
}

//------------------------------------------------------------------------------
