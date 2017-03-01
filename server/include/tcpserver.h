#ifndef ROTABLE_TCPSERVER_H
#define ROTABLE_TCPSERVER_H

//------------------------------------------------------------------------------

#include "configserver.h"
#include "compackage.h"
#include "settings.h"

#include <QTcpServer>
#include <QMap>
#include <QByteArray>

//------------------------------------------------------------------------------

namespace rotable {
  class TcpServer;
}

//------------------------------------------------------------------------------

/**
 * TcpServer does all of the communication stuff.
 */
class rotable::TcpServer : public QObject
{
  Q_OBJECT

public:
  /**
   * Constructor.
   *
   * @param parent        parent object
   */
  TcpServer(QObject *parent = 0);

  /**
   * Destructor.
   */
  ~TcpServer();

  /**
   * Start listening on given port.
   *
   * @param port        port
   * @return            true on success
   */
  bool start(int port);

  /**
   * Stop server
   * @return
   */
  void stop();

  /**
   * Send given package to client.
   *
   * @param client      client to send to (-1 for all clients)
   * @param p           package to send
   * @return            true on success
   */
  bool send(client_t client, const ComPackage& p);

  /**
   * Get socket of given client.
   *
   * @param client      client id
   * @return            socket (or null if client id is invalid)
   */
  QTcpSocket* clientSocket(client_t client);

  /**
   * Set client name.
   *
   * @param client      client id
   * @param name        new name of client
   */
  void setClientName(client_t client, const QString& name);

  /**
   * Get whether given client has been accepted by the server.
   *
   * @param client      client id
   * @return            true if client has been accepted
   */
  bool isClientAccepted(client_t client) const;

  /**
   * Get name of given client.
   *
   * @param client      client id
   * @return            client name
   */
  QString clientName(client_t client) const;

  void close();

signals:
  /**
   * A client has been connected.
   *
   * @param client      client id
   */
  void clientConnected(client_t client);

  /**
   * A package from a client has been received.
   * Will be to the server class emitted
   *
   * @param client      client id
   * @param package     package
   */
  void packageReceived(client_t client, ComPackage* package);

  /**
   * A client has been disconnected.
   * (The client id is now invalid!)
   *
   * @param client      client id (now invalid)
   * @param clientName  client name
   */
  void clientDisconnected(client_t client, const QString& clientName);

private slots:
  void acceptConnection();
  void socketStartRead();
  void socketDisconnect();
  void acceptError(QAbstractSocket::SocketError socketError);
  void socketError(QAbstractSocket::SocketError socketError);

private:
  /**
   * Client informations.
   */
  struct Client {
    /* Socket */
    QTcpSocket* socket;

    /* Client name */
    QString name;

    /* Client id */
    client_t id;

    /* Temporary read buffer */
    QByteArray buffer;

    /**
     * Get whether this client has been accepted.
     *
     * @return          true if client has been accepted by the server
     */
    inline bool isAccepted() const {
      return !name.isEmpty();
    }
  };

  /* TCP-Server-Object */
  QTcpServer _server;

  /* Connected clients (Objects will be deleted when, _server.close() is called. */
  Client _clients[ROTABLE_MAX_CLIENTS];

  /* Number of connected clients */
  int _clientCount;

  /* Mapping of sockets to clients. */
 QMap<QTcpSocket*, client_t> _socket2clients;

 QByteArray _packageStart;
 int packageCounter;
}; // class TcpServer

//------------------------------------------------------------------------------

#endif // ROTABLE_TCPSERVER_H
