#include "table.h"
using rotable::Table;

//------------------------------------------------------------------------------

Table::~Table()
{
    qDeleteAll(_orders.begin(), _orders.end());
    _orders.clear();     //Clear list
}

//------------------------------------------------------------------------------

Table::Table(): rotable::Client()
{
    _change = false;
    _waiterIsNeeded = false;
}

//------------------------------------------------------------------------------

void Table::updateOrder(Order* order){
    if(_orders.contains(order->id()))
        delete _orders[order->id()];
    _orders[order->id()] = order;
    _change = true;
    //emit orderChanged();
}

//------------------------------------------------------------------------------
void Table::updateTableStatus(const rotable::Table *table)
{
    bool change = false;

    if(_waiterIsNeeded != table->_waiterIsNeeded)
    {
        change = true;
        _waiterIsNeeded = table->_waiterIsNeeded;
    }

    _change = _change || change;
}
//------------------------------------------------------------------------------
