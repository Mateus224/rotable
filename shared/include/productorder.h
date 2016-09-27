#ifndef ROTABLE_PRODUCTORDER_H
#define ROTABLE_PRODUCTORDER_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QList>
#include "product.h"
#include "productcontainer.h"
#include "private/precomp.h"
#include "compackage.h"
#ifndef QTIMER_H
#include <QTimer>
#endif

//------------------------------------------------------------------------------

namespace rotable {
  class ProductOrder;
  class ProductContainer;
  class Product;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::ProductOrder class contains a product order.
 */
class rotable::ProductOrder : public QObject //, rotable::ProductContainer
{
  Q_OBJECT

  Q_PROPERTY(int productId READ productId NOTIFY productIdChanged)
  Q_PROPERTY(int quantity READ pieces WRITE setpieces NOTIFY piecesChanged)
  Q_PROPERTY(double PriceOfOrder READ PriceOfOrder NOTIFY PriceOfOrderChanged)
  Q_PROPERTY(QString acceptOrder READ acceptOrder NOTIFY acceptOrderChanged)


public:
    /*write into the database the state*/
  enum OrderState {
    /* The client is currently collecting this order */
    e_preparing = 0,

    /* The order has been submitted */
    e_submitted,

    /* The order has been accepted by a waitor */
    e_accepted,

    /* The order has been delivered to the client */
    e_delivered,

    /* The order has been paid and is finished */
    e_finished,

    /* The order has been canceled */
    e_canceled
  };


  //QList<int>* L_OrderList;
  QList<int>* L_quantity; /**< TODO: describe */



   /**
    * @brief
    *
    * @param jval
    * @param parent
    */
   explicit ProductOrder(const QJsonValue& jval, QObject *parent = 0);
   /**
    * @brief
    *
    * @param Productcontainer
    * @param parent
    */
   ProductOrder( rotable::ProductContainer &Productcontainer,QObject *parent = 0);
   /**
    * @brief
    *
    * @param parent
    */
   ProductOrder(QObject *parent = 0);
  /**
   * send order to the server and the server
   * @brief sendOrderToWaitor
   */
  void sendOrderToWaitor();


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
  /**
   * @brief
   *
   * @return int
   */
  inline int productId() const { return _productId; }
  /**
   * @brief
   *
   * @return int
   */
  inline  int pieces() const { return  _Product._s_quantity; }
  /**
   * @brief
   *
   * @param quantity
   */
  void setpieces( int quantity);
  /**
   * @brief
   *
   */
  void setacceptOrder();
  /**
   * @brief
   *
   * @return double
   */
  inline double PriceOfOrder() const{return _toPay;}
  /**
   * @brief
   *
   * @return QString
   */
  QString acceptOrder()const{return _s_acceptOrder;}
  //------------------------------------------------------------------------------

  /**
   * @brief getpieces
   * @param ProductID
   * gives you the  of a product
   * through ClientProductHash
   */
  void getpieces(int ProductID);


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

signals:
  /**
   * @brief
   *
   */
  void productIdChanged();
  /**
   * @brief
   *
   */
  void PriceOfOrderChanged();
  /**
   * @brief
   *
   */
  void piecesChanged();
  /**
   * @brief
   *
   */
  void AmountChanged();
  /**
   * @brief
   *
   */
  void acceptOrderChanged();



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

public slots:

  /**
   * order is accepted or rejected by the waitor
   * @brief acceptOrder
   */
  bool b_acceptOrder();

  /**
   * @brief addToProductHash
   * @param ProductID
   * Here we add through the gui the product id into the ClientProductHash
   * and count the pieces
   */
  void addToProductHash(int ProductID);
  void addProductFromGuiTo_orderProducts(int ProductID);

  /**
   * @brief rmFromProductHash
   * @param ProductID
   * Here we remove through the gui the product id into the ClientProductHash
   * and count the pieces
   */
  void rmFromProductHash(int ProductID);
  void removeProductFromGuiTo_orderProducts(int ProductID);

  /**
   * @brief setproductid
   * @param ProductID
   * set the Product ID
   */
  void setproductid(int ProductID){
    _productId=ProductID;
      getpieces(_productId);
  }

  /**
   * @brief getListForMyOrderPage
   * We clear the _productcontainer._orderProducts hash
   * and add all products again which are stored in ClientProductHash
   *
   */
  void getListForMyOrderPage();

  /**
   * send order to the server and the server
   * @brief sendOrder
   */
  ComPackageDataSet prepareOrderToSend() const;

  /**
   * Add prices all prices maked in THIS Order and set it in the GUI
   */
  double setPriceOfOrder();

  /**
    *Clear OrderList if is sended to Waiter
    */
  void clearList();

  /**
   * @brief clearGuiList
   * Clear Order which is stored for the GUI
   */

  void clearGuiList();

  /**
   * @brief
   *
   */
  void OrderQueueTextSlot();


//------------------------------------------------------------------------------
//---------VALUES--------------------------------------------------------------

public:
  /**
   * @brief
   *
   */
  struct productChoosen{
      int _s_id; /**< TODO: describe */
      int _s_quantity; /**< TODO: describe */
  };
  productChoosen _Product; /**< TODO: describe */

  QHash<int,productChoosen> *ClientProductHash; /**< TODO: describe */

  /* Products (Mapping of product id to object) */
  QHash<int, rotable::Product*> _products;


  rotable::ProductContainer &_productcontainer; /**< TODO: describe */
  //rotable::ProductContainer *_newproductordercontainer;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

private:



  /* Unique category ID */
  int _productId;
  int _quantity;
  int _orderID;
  int _clientID; /**< TODO: describe */
  double _toPay; /**< TODO: describe */
  bool _acceptOrder; /**< TODO: describe */
  QString _s_acceptOrder; /**< TODO: describe */
}; // class ProductOrder

//------------------------------------------------------------------------------

#endif // ROTABLE_PRODUCTORDER_H
