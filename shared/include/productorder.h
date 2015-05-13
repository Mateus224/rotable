#ifndef ROTABLE_PRODUCTORDER_H
#define ROTABLE_PRODUCTORDER_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QList>
//#include "orderpage.h"
#include "product.h"
#include "productcontainer.h"
#include "private/precomp.h"

//------------------------------------------------------------------------------

namespace rotable {
  class ProductOrder;
  class ProductContainer;
  class OrderPage;
  class Product;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::ProductOrder class contains a product order.
 */
class rotable::ProductOrder : public QObject //, rotable::ProductContainer
{
  Q_OBJECT

  //Q_PROPERTY(int quantity READ _quantity WRITE set_quantity NOTIFY quantityChanged)
  //Q_PROPERTY(QString session READ session WRITE setSession NOTIFY sessionChanged)
  //Q_PROPERTY(QString waitorId READ waitorId WRITE setWaitorId NOTIFY waitorChanged)
  //Q_PROPERTY(int timestamp READ timestamp WRITE setTimeStamp NOTIFY timestampChanged)
  //Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
  Q_PROPERTY(int productId READ productId WRITE setproductId NOTIFY productIdChanged)
  Q_PROPERTY(int quantity READ quantity WRITE setquantity NOTIFY quantityChanged)
  //Q_PROPERTY(WRITE getListForMyOrderPage)


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
   ProductOrder(const QJsonValue& jval, QObject *parent = 0);
   ProductOrder( rotable::ProductContainer &Productcontainer,QObject *parent = 0);
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

  //QList<rotable::Product>  getProductInformation();


  //For Gui interface
  //------------------------------------------------------------------------------
  inline int productId() const { return _productId; }
  void setproductId(  int productId);


  inline  int quantity() const { return  _Product._s_quantity; }
  void setquantity( int quantity);

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



  struct productChoosen{
      int _s_id;
      int _s_quantity;
  };
  productChoosen _Product;

  QHash<int,productChoosen> *ClientProductHash;

  /* Products (Mapping of product id to object) */
  QHash<int, rotable::Product*> _products;
  QList<rotable::Product*> ProductList;
  rotable::Product* _addProduct;
  rotable::ProductContainer* _getProduct;

public:
  rotable::ProductContainer &_productcontainer;
private:


  /* Unique category ID */
  int _productId;
  int _quantity;

  int _orderID;
  int _clientID;

//------------------------------------------------------------------------------

  void getQuantity(int ProductID);


//------------------------------------------------------------------------------


signals:
  void productIdChanged();
  void quantityChanged();

//------------------------------------------------------------------------------


public slots:

  void addToProductHash(int ProductID);
  void rmFromProductHash(int ProductID);
  void setproductid(int ProductID){
    _productId=ProductID;
      getQuantity(_productId);
  }
  void getListForMyOrderPage();

  /**
    get all information from added Product
   * @brief getProductInformation
   * @param ProductId
   */
  //void getProductInformation(int ProductId);

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




}; // class ProductOrder

//------------------------------------------------------------------------------

#endif // ROTABLE_PRODUCTORDER_H
