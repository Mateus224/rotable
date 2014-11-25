#ifndef TCPCLIENT_H
#define TCPCLIENT_H

//------------------------------------------------------------------------------

#include <QTcpSocket>
#include <QList>

#include "productcategory.h"
#include "compackage.h"

//------------------------------------------------------------------------------

/**
 * TCP Client
 */
class TcpClient : public QObject
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param parent      parent object
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
   * Close connection
   */
  void closeConnection();

  /**
   * Send given package to the server.
   *
   * @param p           package to send
   * @return            true on success
   */
  bool send(const rotable::ComPackage& p);

signals:
  void connected();
  void disconnected();
  void packageReceived(rotable::ComPackage* package);
  void error(QAbstractSocket::SocketError socketError);

private slots:
  void readPackage();

private:
  // Socket
  QTcpSocket _client;

  // Admin name
  QString _name;

  // Read buffer
  QByteArray _buffer;

  QByteArray _packageStart;
}; // class TcpClient

//------------------------------------------------------------------------------

#endif // TCPCLIENT_H
