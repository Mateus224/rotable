#ifndef WAITER_CLIENT_H
#define WAITER_CLIENT_H

//------------------------------------------------------------------------------


#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QSTRING_H
#include <QString>
#endif

#ifndef QTIMER_H
#include <QTimer>
#endif

#include "configwaiter.h"
#include "tcpclient.h"
#include "private/precomp.h"
#include "compackage.h"
#include "utils.h"
#include "table.h"
#include "tablemodel.h"
#include "orderboard.h"
#include "productlist.h"
#include "neededboard.h"

//------------------------------------------------------------------------------


namespace rotable {
  class Waiter_Client;
  class ComPackage;
  class ComPackageDataReturn;
  class ComPackageReject;
  class ComPackageDataRequest;
  class ComPackageDataChanged;
  class ProductContainer;
  class ProductOrder;

}

class QAbstractListModel;

class rotable::Waiter_Client : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString loginViewState READ loginViewState WRITE setLoginViewState NOTIFY loginViewStateChanged)
public:
    Waiter_Client(const QString& configFilePath = QString("config.ini"),
                  QObject *parent = 0);
    ~Waiter_Client();

    /**
     * Startup client (connect to server).
     *
     * @return                false on critical error
     */
    bool startup();

    void setApplicationEngine(QQmlApplicationEngine *engine);

    /**
     * Function to be called when user try log in
     */
    Q_INVOKABLE void logIn();

    /**
     * Function invoke from qml to log off
     */
    Q_INVOKABLE void logOff();


    QString login() const { return _login; }
    void setLogin(const QString &login) { _login = login; emit loginChanged(); }

    QString password() const { return _password; }
    void setPassword(const QString &pass) { _password = pass; emit passwordChanged(); }

    QString loginViewState() const { return _loginViewState; }
    void setLoginViewState(const QString &state) { _loginViewState = state; emit loginViewStateChanged(); }

signals:
    void stateChanged();

private slots:
  /**
   * Start reconnection with rotable-server.
   */
  void reconnect();

  /**
   * Slot to be called when connection to server is established.
   */
  void connected();

  /**
   * Slot to be called when connection to server has been lost.
   */
  void disconnected();

  /**
   * A package from the server has been received.
   *
   * @param package     package
   */
  void packageReceived(ComPackage* package);

  /**
   * A package has been rejected.
   *
   * @param rej        reject package
   */
  void rejected(ComPackageReject* rej);

  /**
   * Get actual state
   * @return          state
   */
  QString state() const;

  /**
   * Set current GUI state.
   *
   * @param state       new GUI state
   */
  void setState(const QString& state);

  /**
   * Request server for table list
   */
  void requestTableList();

  /**
   * Signal for send order
   */
  void sendOrders();

  /**
   * Signal for send information about waiter need changed
   *
   * @param id          table id
   */
  void tableNeedWaiterChanged(int id);

signals:
  void changeTableList();
  void loginChanged();
  void passwordChanged();
  void loginViewStateChanged();

public:
  /* Products */
  rotable::ProductContainer* _products;
  rotable::ProductList _productsList;

  /* Table map with table id */
  rotable::TableModel _tables;

  /* Board with orders */
  rotable::OrderBoard _board;

  /* Board with table with need waiter */
  rotable::NeedBoard _needBoard;

//------------------------------------------------------------------------------
private:

  /**
   * Request category information.
   * (result received in dataReturned())
   *
   * @param categoryId      category id
   */
  void requestCategory(int categoryId);

  /**
   * Request product information.
   * (result received in dataReturned())
   *
   * @param productId       product id
   */
  void requestProduct(int productId);

  /**
   * Request all category ids.
   */
  void requestCategoryIds();

  /**
   * Request product ids of given category.
   * (result received in dataReturned())
   *
   * @param categoryId      id of category to request product ids from
   */
  void requestProductIds(int categoryId);

  /**
   * Request order base on table
   *
   * @param tableId         id
   */
  void requestOrderOnTable(int tableId);

  /**
   * Request order form database
   *
   * @param orderId         order id
   */
  void requestOrder(int orderId);

  /**
   * Request last income from server
   */
  void requestLastIncome();

    /**
     * Handle data received from the server.
     *
     * @param ret         received data package
     */
    void dataReturned(ComPackageDataReturn* ret);


    /**
     * Handle data changed information from the server.
     *
     * @param package     received package
     */
    void dataChanged(rotable::ComPackageDataChanged* package);

    /**
     * Request table from database
     *
     * @param tableId       table id
     */
    void requestTable(int tableId);


    //------------------------------------------------------------------------------

    /* Whether this client has been accepted by the server */
    bool _accepted;

    /* Program state */
    QString _state;

    /* Whether the program is currently shutting */
    bool _stopping;

    /* Configuration file access */
    ConfigWaiter _config;

    /* TCP-Socket object */
    TcpClient _tcp;

    /* Timer for waiting before reconnect */
    QTimer _reconnectTimer;

    /* Currently pending data requests */
    QMap<QString, ComPackageDataRequest*> _dataRequest;

    QQmlApplicationEngine *_engine;

    QString _login;
    QString _password;

    bool _tryLogin;
    QString _loginViewState;

    //----------------------------------------------------------------------------
};

#endif // WAITER_CLIENT_H
