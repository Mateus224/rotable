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
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)

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
    inline void setwaiterIsNeedede(bool waiterIsNeeded) { _waiterIsNeeded = waiterIsNeeded; emit waiterIsNeededChanged();}


    inline bool isConnected() const { return _isConnected; }
    inline void setIsConnected(bool isConnected)  { _isConnected = isConnected; emit isConnectedChanged(); }

    inline int lastOrderId() const { return _lastOrder; }
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
        int count = 0;
        foreach (Order* order, _orders) {
            if(!order->isClose())
                ++count;
        }
        return count;
    }

    /**
     * Add new order to table
     *
     * @param order     order object
     */
    inline void addOrder(rotable::Order* order){
        _orders[order->id()] = order;
        connect(order, &rotable::Order::itemsChanged, this, &rotable::Table::orderChanged);
        #ifdef WAITER
        connect(order, &rotable::Order::stateChanged, this, &rotable::Table::recalcLastOrder);
        order->setState(order->state());
        #endif
        emit  tableChanged();
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

    void disconnectTable();

    /**
     * Check if table has new order
     *
     * @return          true or false
     */
    bool isNewOrder() const;

    //------------------------------------------------------------------------------
    // JSON ( for network communication )
    //------------------------------------------------------------------------------

    /**
     * Convert Table to JSON
     *
     * @return          QJsonValue
     */
    QJsonValue toJSON() const;

    /**
     * Create Table object from JSON
     *
     * @param jval      JSON object
     * @return          Table object
     */
    static Table *fromJSON(const QJsonValue &jval);

    QMap<int, QJsonValue> *getOrderJSON() const;

private:
    /**
     * Calc last number of new order
     */
    void recalcLastOrder();

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

    /**
     * Store information about enabled of table (table is on/off)
     */
    bool _isConnected;

    /**
     * Store id of last new order, if not order, return -1
     */
    int _lastOrder;

signals:
    void tableChanged();
    void waiterIsNeededChanged();
    void isConnectedChanged();
    void sendOrders();
    void orderStateChanged();

public slots:
    void diconnectRemote();
    void prepareOrderToSend();

private slots:
    void orderChanged();

};  // class Table

//------------------------------------------------------------------------------

#endif
