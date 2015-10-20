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
  Q_PROPERTY(int productId READ productId WRITE setProductId NOTIFY productIdChanged)
  Q_PROPERTY(double price READ price WRITE setPrice NOTIFY priceChanged)
  Q_PROPERTY(QTime time READ time WRITE setTime NOTIFY timeChanged)

public:

  explicit OrderItem(QObject *parent = 0);
  explicit OrderItem(const QJsonValue& jval, QObject *parent = 0);

  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; emit idChanged(); }

  inline int productId() const { return _productId; }
  inline void setProductId(int productId) { _productId = productId; emit productIdChanged(); }

  inline int amount() const { return _amount; }
  inline void setAmount(int amount) { _amount = amount; emit amountChanged(); }

  inline int state() const { return _state; }
  inline void setState(int state) { _state = state; emit stateChanged(); }

  inline double price() const { return _price; }
  inline void setPrice(double price) {_price = price; emit priceChanged(); }

  inline QTime time() const { return _time; }
  inline void setTime(QTime time) { _time = time; emit timeChanged(); }

  inline bool isReadyToChange() { return _readyToChange; }

  QJsonValue toJSON() const;
  static OrderItem* fromJSON(const QJsonValue& jval);

  void updateOrderItem(OrderItem *item);

  Q_INVOKABLE inline void readyToChange(bool state) { _readyToChange = state;  emit readyToChanged();}

  enum State{
      New,
      Accept,
      Rejected,
      Done
  };

signals:
  void amountChanged();
  void idChanged();
  void stateChanged();
  void productIdChanged();
  void priceChanged();
  void timeChanged();
  void readyToChanged();

private:
  int _id;
  int _productId;
  int _amount;
  int _state;
  double _price;
  QTime _time;

  /** This value will be store information: "do you want change _state of this orderItem" **/
  bool _readyToChange;
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
  inline void addItem(rotable::OrderItem* item){
      _items.append(item);
      connect(item, &rotable::OrderItem::amountChanged, this, &rotable::Order::itemChanged);
      connect(item, &rotable::OrderItem::stateChanged, this, &rotable::Order::itemChanged);
      connect(item, &rotable::OrderItem::priceChanged, this, &rotable::Order::itemChanged);
      connect(item, &rotable::OrderItem::timeChanged, this, &rotable::Order::itemChanged);
      connect(item, &rotable::OrderItem::readyToChanged, this, &rotable::Order::itemIsReadyToChanged);
  }

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

  Q_INVOKABLE void changeState(int state);

  Q_INVOKABLE void prepareOrderToChange();
signals:
  void stateChanged();
  void itemsChanged();
  void timeSentChanged();
  void clientIdChanged();
  void idChanged();
  void readyToChanged(bool);

private slots:
  void itemChanged();
  void itemIsReadyToChanged();

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
