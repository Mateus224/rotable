#include "table.h"
using rotable::Table;

//------------------------------------------------------------------------------

Table::~Table()
{
    qDeleteAll(_orders.begin(), _orders.end());
    _orders.clear();     //Clear list
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
