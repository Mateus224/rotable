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

//------------------------------------------------------------------------------


namespace rotable {
  class Waiter_Client;
  class ComPackage;
  class ComPackageDataReturn;
  class ComPackageReject;
  class ComPackageDataRequest;
  class ComPackageDataChanged;
  class ProductContainer;
}

class rotable::Waiter_Client : public QObject
{
    Q_OBJECT
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
   * Set current GUI state.
   *
   * @param state       new GUI state
   */
  void setState(const QString& state);


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


    //------------------------------------------------------------------------------

    /* Products */
    rotable::ProductContainer* _products;
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

    //----------------------------------------------------------------------------
};

#endif // WAITER_CLIENT_H
