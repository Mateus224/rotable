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

//------------------------------------------------------------------------------

namespace rotable {
  class Waiter_Client;
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
  //void rejected(ComPackageReject* rej);

  /**
   * Set current GUI state.
   *
   * @param state       new GUI state
   */
  void setState(const QString& state);


//------------------------------------------------------------------------------
private:
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

};

#endif // WAITER_CLIENT_H
