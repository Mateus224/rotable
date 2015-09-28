#ifndef ROTABLE_ORDER_H
#define ROTABLE_ORDER_H

//------------------------------------------------------------------------------

#ifndef QJSONOBJECT_H
#include <QJsonObject>
#endif

#ifndef QLIST_H
#include <QList>
#endif

#ifndef QDATETIME_H
#include <QDateTime>
#endif

#ifndef QQMLLIST_H
#include <QQmlListProperty>
#endif

#ifdef QJSONVALUE_H
#include <QJsonValue>
#endif

//------------------------------------------------------------------------------

namespace rotable {
class OrderItem;
class Order;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::OrderItem class defines an ordered item.
 */
class rotable::OrderItem : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
  Q_PROPERTY(int amount READ amount WRITE setAmount NOTIFY amountChanged)
  Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)

public:

  explicit OrderItem(QObject *parent = 0);
  explicit OrderItem(const QJsonValue& jval, QObject *parent = 0);

  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; emit idChanged();}

  inline int amount() const { return _amount; }
  inline void setAmount(int amount) { _amount = amount; emit amountChanged(); }

  inline int state() const { return _state; }
  inline void setState(int state) {_state = state; emit stateChanged();}

  QJsonValue toJSON() const;
  static OrderItem* fromJSON(const QJsonValue& jval);

  void updateOrderItem(OrderItem *item);

signals:
  void amountChanged();
  void idChanged();
  void stateChanged();

private:
  int _id;
  int _amount;
  int _state;
}; // class OrderItem

//------------------------------------------------------------------------------

/**
 * @brief The rotable::Order class defines an order made by a client.
 */
class rotable::Order : public QObject
{
  Q_OBJECT

public:
  /**
   * Possible order states.
   */
  enum State {
    /* User is currently collecting items for his order */
    Temporarily,

    /* Order has been sent */
    Sent,

    /* Order has been accepted by a waiter */
    Accepted,

    /* Order has been delivered by a waiter */
    Delivered,

    /* Order has been paid */
    Paid
  };

private:
  Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
  Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
  Q_PROPERTY(int clientId READ clientId WRITE setClientId NOTIFY clientIdChanged)
  Q_PROPERTY(​QQmlListProperty<OrderItem> items READ items NOTIFY itemsChanged)

public:
  /**
   * Constructor
   *
   * @param jval          JSON value
   * @param parent        parent object
   */
  explicit Order(const QJsonValue& jval, QObject *parent = 0);

  /**
   * Constructor
   *
   * @param parent        parent object
   */
  explicit Order(QObject *parent = 0);

  ~Order();

  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; emit idChanged();}

  inline int state() const { return _state; }
  inline void setState(int state) { _state = state; emit stateChanged(); }

  inline int clientId() const { return _clientId; }
  inline void setClientId(int clientId) { _clientId = clientId; emit clientIdChanged(); }

  /**
   * Get QML list of items.
   *
   * @return            list of items for QML
   */
  inline QQmlListProperty<OrderItem> items() {
    return QQmlListProperty<OrderItem>(this, _items);
  }

  /**
   * Get number of order items.
   *
   * @return            order item count
   */
  inline int itemCount() const { return _items.count(); }

  /**
   * Get item from order
   *
   * @param idx         idx of item
   * @return
   */
  inline OrderItem* item(int idx) { return _items.at(idx); }

  /**
   * Add an item to the order.
   *
   * @param item        item to add
   */
  inline void addItem(OrderItem* item);

  /**
   * Convert this order into a QJsonObject.
   *
   * @return            QJsonValue
   */
  QJsonValue toJSON() const;

  /**
   * Create an order object from a JSON value.
   *
   * @param jval        JSON value
   * @return            created order object or NULL on error
   */
  static Order *fromJSON(const QJsonValue& jval);

  /**
   * Update order base on Order object
   *
   * @param order           Order object
   */
  void updateOrder(Order *order);

signals:
  void stateChanged();
  void itemsChanged();
  void timeSentChanged();
  void clientIdChanged();
  void idChanged();

private slots:
  void itemChanged();

private:
  /* Unique order ID */
  int _id;

  /* Order state */
  int _state;

  /* Order items */
  QList<OrderItem *> _items;

  /* Timestamp the order has been sent */
  QDateTime _timeSent;

  /* Table from which the order came from */
  int _clientId;
}; // class Order

//------------------------------------------------------------------------------

#endif // ROTABLE_ORDER_H
