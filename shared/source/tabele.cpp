#include "table.h"
using rotable::Table;

//------------------------------------------------------------------------------

Table::~Table()
{
    // Delete all orders
    qDeleteAll(_orders.begin(), _orders.end());
    _orders.clear();     //Clear map
}

//------------------------------------------------------------------------------

Table::Table(): rotable::Client()
{
    // Set default value
    _change = false;
    _waiterIsNeeded = false;
}

//------------------------------------------------------------------------------

void Table::updateOrder(Order* order){
    // Check if order contains order
    if(_orders.contains(order->id()))
        //Clear memory
        delete _orders[order->id()];
    // Add order
    _orders[order->id()] = order;
    //Change are made, set change value on true
    _change = true;
    //emit orderChanged();
}

//------------------------------------------------------------------------------
void Table::updateTableStatus(const rotable::Table *table)
{
    // Change value create
    bool change = false;

    // Chaeck if something change
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
