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
    _orders[order->id()] = order;
    //emit orderChanged();
}
//------------------------------------------------------------------------------
