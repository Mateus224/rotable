#ifndef TABLE_ROTABLE_H
#define TABLE_ROTABLE_H

//------------------------------------------------------------------------------
#include "client.h"
#include "order.h"

#ifndef QMAP_H
#include <QMap>
#endif

#ifndef QLIST_H
#include <QList>
#endif

#ifndef QOBJECT_H
#include <QObject>
#endif

namespace rotable {
  class Table;
}

//------------------------------------------------------------------------------

/**
 * @brief
 *
 */
class rotable::Table : public rotable::Client {

  Q_OBJECT

  Q_PROPERTY(bool waiterIsNeeded READ waiterIsNeeded WRITE setwaiterIsNeedede
                 NOTIFY waiterIsNeededChanged)
  Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY
                 isConnectedChanged)
  Q_PROPERTY(int orderedProductCount READ getOrderedProductCount WRITE
                 setOrderedProductCount NOTIFY orderedProductCountChanged)
  Q_PROPERTY(int incomingOrderCount READ getincomingOrderCount NOTIFY incomingOrderCountChanged)

public:
  // Default destructor
  /**
   * @brief
   *
   */
  ~Table();

  // Default constructor
  /**
   * @brief
   *
   * @param parent
   */
  explicit Table(QObject *parent = 0);

  //------------------------------------------------------------------------------
  // Implement inherit class
  //------------------------------------------------------------------------------

  /**
   * Return account type
   *
   * @return      type of account (int, ComPackage::AcountType)
   */
  inline virtual int accountType() const { return 1; }

  //------------------------------------------------------------------------------
  // Property
  //------------------------------------------------------------------------------

  /**
   * @brief
   *
   * @return bool
   */
  inline bool waiterIsNeeded() const { return _waiterIsNeeded; }
  /**
   * @brief
   *
   * @param waiterIsNeeded
   */
  inline void setwaiterIsNeedede(bool waiterIsNeeded) {
    _waiterIsNeeded = waiterIsNeeded;
    emit waiterIsNeededChanged();
  }

  /**
   * @brief
   *
   * @return bool
   */
  inline bool isConnected() const { return _isConnected; }
  /**
   * @brief
   *
   * @param isConnected
   */
  inline void setIsConnected(bool isConnected) {
    _isConnected = isConnected;
    emit isConnectedChanged();
  }

  /**
   * @brief
   *
   * @return int
   */
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
  inline rotable::Order *getOrder(int orderId) {
    if (_orders.contains(orderId))
      return _orders[orderId];
    return NULL;
  }

  /**
   * Get order number from table
   *
   * @return  order count
   */
  inline int orderCount() {
    int count = 0;
    foreach (Order *order, _orders) {
      if (!order->isClose())
        ++count;
    }
    return count;
  }

  /**
   * Add new order to table
   *
   * @param order     order object
   */
  inline void addOrder(rotable::Order *order) {
    _orders[order->id()] = order;
    connect(order, &rotable::Order::itemsChanged, this,
            &rotable::Table::orderChanged);
#ifdef WAITER
    connect(order, &rotable::Order::stateChanged, this,
            &rotable::Table::recalcLastOrder);
    connect(order, &rotable::Order::stateChanged, this,
            &rotable::Table::recalcIncomingOrders);
    connect(order, &rotable::Order::forceSendRequest, this,
            &rotable::Table::prepareOrderToSend);
    recalcIncomingOrders();
    if (order->isNew()) _lastOrder = order->id();
    emit lastOrderChange();
#endif
    emit tableChanged();
    emit newOrderAdded();
  }

  /**
   * Add order to table, if exist change order object
   *
   * @param order     order object
   */
  void updateOrder(rotable::Order *order);

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
  QList<rotable::Order *> orderList();

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

  QMap<int, QJsonValue> *getOrderJSON() const;

  int getOrderedProductCount() const { return _orderedProductCount; }

  void setOrderedProductCount(int orderedProductCount) {
    _orderedProductCount = orderedProductCount;
  }

  int getincomingOrderCount() const { return _incomingOrderCount; }

  /**
   * Store orders, int - orderId
   */
  QMap<int, rotable::Order *> _orders;

protected:
  virtual void addAdditionalData(QJsonObject &obj) const;
  virtual void setAdditionalData(QJsonObject &obj);

private:
  /**
   * Calc last number of new order
   */
  void recalcLastOrder();



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

  /**
   * Stores how many orders are actually stored in the incoming category
   */
  int _incomingOrderCount;

  int _orderedProductCount;

signals:
  /**
   * @brief
   *
   */
  void tableChanged();
  /**
   * @brief
   *
   */
  void waiterIsNeededChanged();
  /**
   * @brief
   *
   */
  void isConnectedChanged();
  /**
   * @brief
   *
   */
  void sendOrders();
  /**
   * @brief
   *
   */
  void lastOrderChange();

  void incomingOrderCountChanged();

  void orderedProductCountChanged();

  void newOrderAdded();

public slots:
  /**
   * @brief
   *
   */
  void diconnectRemote();
  /**
   * @brief
   *
   */
  void prepareOrderToSend();

private slots:
  /**
   * @brief
   *
   */
  void orderChanged();

  /**
   * @brief Slot use for recalc how many products is ordered
   *
   */
  void recalcOrderedProductsCount();

  /**
   * @brief This slot counts, how many orders are in incoming category.
   *
   */
  void recalcIncomingOrders();

}; // class Table

//------------------------------------------------------------------------------

#endif
