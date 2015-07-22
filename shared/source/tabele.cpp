#include "table.h"
using rotable::Table;

//------------------------------------------------------------------------------
void Table::updateOrder(Order* order){
    _orders[order->id()] = order;
    emit orderChange();
}
//------------------------------------------------------------------------------
