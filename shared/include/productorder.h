#ifndef ROTABLE_PRODUCTORDER_H
#define ROTABLE_PRODUCTORDER_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QList>

//------------------------------------------------------------------------------

namespace rotable {
  class ProductOrder;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::ProductOrder class contains a product order.
 */
class rotable::ProductOrder : public QObject
{
  Q_OBJECT

  //Q_PROPERTY(int productId READ productId WRITE setProductId NOTIFY productIdChanged)



  //Q_PROPERTY(int quantity READ _quantity WRITE set_quantity NOTIFY quantityChanged)
  //Q_PROPERTY(int productId READ _productId WRITE set_ProductId NOTIFY productIdChanged)
  /*
    Q_PROPERTY(int count READ count WRITE setSetCount NOTIFY countChanged)
  Q_PROPERTY(QString session READ session WRITE setSession NOTIFY sessionChanged)
  Q_PROPERTY(QString waitorId READ waitorId WRITE setWaitorId NOTIFY waitorChanged)
  Q_PROPERTY(int timestamp READ timestamp WRITE setTimeStamp NOTIFY timestampChanged)
  Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
  Q_PROPERTY(QString tableId READ tableId WRITE setTableId NOTIFY tableIdChanged)
  */

public:
    /*write into the database the state*/
  enum OrderState {
    /* The client is currently collecting this order */
    e_preparing = 0,

    /* The order has been submitted */
    e_submitted,

    /* The order has been accepted by a waitor */
    //e_accepted,

    /* The order has been delivered to the client */
    e_delivered,

    /* The order has been paid and is finished */
    e_finished,

    /* The order has been canceled */
    e_canceled
  };


  //QList<int>* L_OrderList;
  QList<int>* L_quantity;

  //ProductOrder();
  explicit ProductOrder(int orderID,int clientID, QObject *parent = 0);
  ~ProductOrder();



  /**
   * send order to the server and the server
   * @brief sendOrder
   */
  void sendOrderToServer();

  /**
   * send order to the server and the server
   * @brief sendOrderToWaitor
   */
  void sendOrderToWaitor();

  /**
   * order is accepted or rejected by the waitor
   * @brief acceptOrder
   */
  void acceptOrder();

  /**
   * @brief setStopWatchTime
   * by incomming orders the time will be start to measured
   */
  void setStopWatchTime();

  /**
   * @brief getStopWatchTime
   * @return
   * returns (for the waitorGui) the time which the clients are
   * waiting for the orders
   */
  int getStopWatchTime();

  /**
   * @brief sendWaitTimeForClient
   * @return
   * send to the client the probeble waiting time for the order
   */
  int sendWaitTimeForClient();
  //------------------------------------------------------------------------------

  /**
   * @brief set_quantity
   * @param id
   * set quantity of this Product and send to GUI
   */
  void set_quantity(int id);

  void set_ProductId(int id);


  /**
   * @brief id
   * @return
   * return the Product ID
   */
  inline int get_quantity() const { return _productId; }

  inline int get_ProductId() const { return _productId; }


  //------------------------------------------------------------------------------

  /**
   * Convert this order into a QJsonObject.
   *
   * @return            QJsonObject
   */
  QJsonValue toJSON() const;

  /**
   * Create an order object from a JSON value.
   *
   * @param jval        JSON value
   * @return            created order or NULL on error
   */
  static ProductOrder *fromJSON(const QJsonValue& jval);







//------------------------------------------------------------------------------


signals:
  void productIdChanged();
  void quantityChanged();

public slots:
  /**
   * add from the MyOrderButton.qml
   * Products which are choosen
   */
  void addProductToOrder(int id);

  /**
   * add from the MyOrderButton.qml
   * Products which are choosen
   * @brief removeProductFromOrder
   */
  void removeProductFromOrder(int id);

private:

  /* Unique category ID */
  int _productId;
  int _quantity;
}; // class ProductOrder

//------------------------------------------------------------------------------

#endif // ROTABLE_PRODUCTORDER_H
