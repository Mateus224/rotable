#ifndef ROTABLE_TCPCLIENT_H
#define ROTABLE_TCPCLIENT_H

//------------------------------------------------------------------------------

#ifndef QTCPSOCKET_H
#include <QTcpSocket>
#endif

#ifndef QLIST_H
#include <QList>
#endif

#include "productcategory.h"
#include "configclient.h"

//------------------------------------------------------------------------------

namespace rotable {
  class TcpClient;
  class ComPackage;
}

//------------------------------------------------------------------------------

/**
 * TcpClient does all of the communication stuff.
 */
class rotable::TcpClient : public QObject
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param parent          parent object
   */
  TcpClient(QObject *parent = 0);

  /**
   * Destructor
   */
  ~TcpClient();

  /**
   * Connect to server.
   *
   * @param hostname        hostname or ip of server
   * @param port            server port
   */
  void startConnection(const QString& hostname, int port);

  /**
   * Send given package to the server.
   *
   * @param p           package to send
   * @return            true on success
   */
  bool send(const ComPackage& p);

  /**
   * Get last socket error.
   *
   * @return            last socket error
   */
  QTcpSocket::SocketError last_error() const;

signals:
  void connected();
  void disconnected();
  void packageReceived(ComPackage* package);

private slots:
  void readPackage();
  void error(QAbstractSocket::SocketError socketError);

private:
  // Socket
  QTcpSocket _client;

  // Table name
  QString _name;

  // Read buffer
  QByteArray _buffer;
  QByteArray _packageStart;
}; // class TcpClient

//------------------------------------------------------------------------------

#endif // ROTABLE_TCPCLIENT_H
