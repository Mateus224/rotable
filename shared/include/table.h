#ifndef TABLE_ROTABLE_H
#define TABLE_ROTABLE_H

//------------------------------------------------------------------------------

#include "client.h"
#include "order.h"

#ifndef QMAP_H
#include<QMap>
#endif

//------------------------------------------------------------------------------

namespace rotable {
    class Table;
}

//------------------------------------------------------------------------------

class rotable::Table :public Client{
public:
    // Return account type
    inline virtual int accountType(){ return 1; }
    // Get order from table
    inline Order*  getOrder(int orderId){
        if(_orders.contains(orderId))
            return _orders[orderId];
        return NULL;
    }
    inline int orderCount(){
        return _orders.count();
    }
    inline addOrder(Order* order){
        _orders[order->id()] = order;
    }
    void updateOrder(Order* order);
private:
    QMap<int,Order*> _orders;

signals:
    void orderChange();
};  // class Table

//------------------------------------------------------------------------------

#endif
