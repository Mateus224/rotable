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

  /**
   * Send given QByteArray to the server.
   *
   * @param p           package to send
   * @return            true on success
   */
  bool send(const QByteArray d);

  /**
   * @brief sendInPart
   * @param p package to send
   * @param IDprogressBar for identifier thedesitination progressBar
   * this method devides a package in 100 parts
   */
  void sendInPart(const rotable::ComPackage &p, int progressBar);

signals:
  /**
   * @brief
   *send signal to executor
   */
  void connected();
  /**
   * @brief
   *
   */
  void disconnected();
  /**
   * @brief
   *
   * @param package
   */
  void packageReceived(rotable::ComPackage* package);
  /**
   * @brief
   *
   * @param socketError
   */
  void error(QAbstractSocket::SocketError socketError);

  void progressBar(int count,int IDprogressBar);
private slots:
  /**
   * @brief
   *
   */
  void readPackage();

private:
  // Socket
  QTcpSocket _client; /**< TODO: describe */

  // Admin name
  QString _name; /**< TODO: describe */

  // Read buffer
  QByteArray _buffer; /**< TODO: describe */

  QByteArray _packageStart; /**< TODO: describe */
}; // class TcpClient

//------------------------------------------------------------------------------

#endif // TCPCLIENT_H
