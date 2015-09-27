#ifndef TABLE_ROTABLE_H
#define TABLE_ROTABLE_H

//------------------------------------------------------------------------------

#include "order.h"
#include "client.h"

#ifndef QMAP_H
#include <QMap>
#endif

#ifndef QLIST_H
#include <QList>
#endif

#ifndef QOBJECT_H
#include <QObject>
#endif

//------------------------------------------------------------------------------

namespace rotable {
    class Table;
}

//------------------------------------------------------------------------------

class rotable::Table : public rotable::Client{

    Q_OBJECT
    Q_PROPERTY(bool waiterIsNeeded READ waiterIsNeeded WRITE setwaiterIsNeedede NOTIFY waiterIsNeededChanged)

public:

    // Default destructor
    ~Table();

    //Default constructor
    explicit Table(QObject *parent = 0);

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
    // Property
    //------------------------------------------------------------------------------

    inline bool waiterIsNeeded() const { return _waiterIsNeeded; }
    inline void setwaiterIsNeedede(bool waiterIsNeeded) { _waiterIsNeeded = waiterIsNeeded; emit tableChanged();}

    //------------------------------------------------------------------------------
    // Method
    //------------------------------------------------------------------------------

    /**
     * Get order from table
     *
     * @param orderId           order Id
     * @return                  order object
     */
    inline rotable::Order*  getOrder(int orderId){
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
    inline void addOrder(rotable::Order* order){
        _orders[order->id()] = order;
    }

    /**
     * Add order to table, if exist change order object
     *
     * @param order     order object
     */
    void updateOrder(rotable::Order* order);

    /**
     * Update table status base on table object
     *
     * @param table     table object
     */
    void updateTableStatus(const Table *table);

    /**
     * Return list with orders
     *
     * @return          orderList
     */
    QList<rotable::Order*> orderList();

    /**
     * Check if table has order
     *
     * @param orderId   order id
     * @return          true if order exists
     */
    bool hasOrder(const int &orderId) const;


private:
    /**
     * Store orders, int - orderId
     */
    QMap<int,rotable::Order*> _orders;

    /**
     * Store status table
     * If something change, set on true
     * When waiter check what is change set on false
     */
    bool _change;

    /**
     * Store information about waiter needed on table
     */
    bool _waiterIsNeeded;

signals:
    void tableChanged();
    void waiterIsNeededChanged();

private slots:
    void orderChanged();
};  // class Table

//------------------------------------------------------------------------------

#endif
