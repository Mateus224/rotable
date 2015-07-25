#ifndef TABLE_ROTABLE_H
#define TABLE_ROTABLE_H

//------------------------------------------------------------------------------

#include "order.h"
#include "client.h"

#ifndef QMAP_H
#include<QMap>
#endif

//------------------------------------------------------------------------------

namespace rotable {
    class Table;
}

//------------------------------------------------------------------------------

class rotable::Table : public Client{
public:

    // Default destructor
    ~Table();

    //------------------------------------------------------------------------------
    // Implement inherit class
    //------------------------------------------------------------------------------

    /**
     * Return account type
     *
     * @return      type of account (int, ComPackage::AcountType)
     */
    inline virtual int accountType(){
        return 1;
    }

    //------------------------------------------------------------------------------
    // Method
    //------------------------------------------------------------------------------

    /**
     * Get order from table
     *
     * @param orderId           order Id
     * @return                  order object
     */
    inline Order*  getOrder(int orderId){
        if(_orders.contains(orderId))
            return _orders[orderId];
        return NULL;
    }
    /**
     * Get order number from table
     *
     * @return  order count
     */
    inline int orderCount(){
        return _orders.count();
    }

    /**
     * Add new order to table
     *
     * @param order     order object
     */
    inline void addOrder(Order* order){
        _orders[order->id()] = order;
    }

    /**
     * Add order to table, if exist change order object
     *
     * @param order     order object
     */
    void updateOrder(Order* order);


private:
    /**
     * Store orders, int - orderId
     */
    QMap<int,Order*> _orders;

    /**
     * Store status table
     * If something change, set on true
     * When waiter check what is change set on false
     */
    bool _change;

signals:
    //void orderChanged();
};  // class Table

//------------------------------------------------------------------------------

#endif
