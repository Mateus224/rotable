#include "private/precomp.h"

#include "tcpserver.h"
#include "utils.h"
#include "logmanager.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

TcpServer::TcpServer(QObject *parent) :
  QObject(parent), _clientCount(0)
{
  _packageStart.append((char)113);
  _packageStart.append((char)98);
  _packageStart.append((char)106);
  _packageStart.append((char)115);
  _packageStart.append((char)1);
  _packageStart.append((char)0);
  _packageStart.append((char)0);
  _packageStart.append((char)0);

  connect(&_server, SIGNAL(newConnection()),
          this, SLOT(acceptConnection()));
  connect(&_server, SIGNAL(acceptError(QAbstractSocket::SocketError)),
          this, SLOT(acceptError(QAbstractSocket::SocketError)));

  for (int i = 0; i < ROTABLE_MAX_CLIENTS; ++i) {
    _clients[i].socket = 0;
  }
}

//------------------------------------------------------------------------------

TcpServer::~TcpServer()
{
  _server.close();
}

//------------------------------------------------------------------------------

bool TcpServer::start(int port)
{
  return _server.listen(QHostAddress::Any, port);
}

//------------------------------------------------------------------------------

bool TcpServer::send(client_t client, const ComPackage& p)
{
  if (client >= 0 && client < ROTABLE_MAX_CLIENTS && _clients[client].socket != 0) {
    Client& c = _clients[client];
    QByteArray data = p.toByteArray();
    qint64 bytesSent = c.socket->write(data);
    if (bytesSent != static_cast<qint64>(data.length())) {
      qCritical() << tr("Could not send package!");
      return false;
    }
    return true;
  } else if (client == -1) {
    for (int i = 0; i < _clientCount; ++i) {
      if (!send(i, p)) {
        return false;
      }
    }
    return true;
  } else {
    qCritical() << tr("Invalid client: %1").arg(client);
    return false;
  }
}

//------------------------------------------------------------------------------

QTcpSocket *TcpServer::clientSocket(client_t client)
{
  if (client >= 0 && client < ROTABLE_MAX_CLIENTS && _clients[client].socket != 0) {
    return _clients[client].socket;
  } else {
    qCritical() << tr("Invalid client: %1").arg(client);
    return 0;
  }
}

//------------------------------------------------------------------------------

void TcpServer::setClientName(client_t client, const QString &name)
{
  if (client >= 0 && client < ROTABLE_MAX_CLIENTS && _clients[client].socket != 0) {
     _clients[client].name = name;
  } else {
    qCritical() << tr("Invalid client: %1").arg(client);
  }
}

//------------------------------------------------------------------------------

bool TcpServer::isClientAccepted(client_t client) const
{
  if (client >= 0 && client < ROTABLE_MAX_CLIENTS && _clients[client].socket != 0) {
    return _clients[client].isAccepted();
  } else {
    qCritical() << tr("Invalid client: %1").arg(client);
    return false;
  }
}

//------------------------------------------------------------------------------

QString TcpServer::clientName(client_t client) const
{
  if (client >= 0 && client < ROTABLE_MAX_CLIENTS && _clients[client].socket != 0) {
    return _clients[client].name;
  } else {
    qCritical() << tr("Invalid client: %1").arg(client);
    return QString();
  }
}

//------------------------------------------------------------------------------

void TcpServer::acceptConnection()
{
  QTcpSocket* client = _server.nextPendingConnection();

  if (client) {
    connect(client, SIGNAL(readyRead()),
            this, SLOT(socketStartRead()));
    connect(client, SIGNAL(disconnected()),
            this, SLOT(socketDisconnect()));
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));

    // find first free socket
    client_t id = -1;
    for (int i = 0; i < ROTABLE_MAX_CLIENTS; ++i) {
      if (_clients[i].socket == 0) {
        id = i;
        break;
      }
    }

    if (id == -1) {
      qCritical() << tr("No free client entry found!");
      return;
    }

    _clients[id].id = id;
    _clients[id].socket = client;
    _clients[id].name.clear();
    _socket2clients[client] = id;

    emit clientConnected(id);

    _clientCount++;
  }
}

//------------------------------------------------------------------------------

void TcpServer::socketStartRead()
{
  QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
  if (!_socket2clients.contains(socket)) {
    qCritical() << tr("ERROR: socket not in map!");
    return;
  }

  QByteArray& buffer = _clients[_socket2clients[socket]].buffer;

  buffer += socket->readAll();

  bool doContinue = true;
  do {
    QJsonDocument jdoc = QJsonDocument::fromBinaryData(buffer);
    if (jdoc.isNull()) {
      // we probably did not receive the full package yet
      doContinue = false;
    } else {

      //qDebug() << tr("============ NEW PACKAGE =============");
      //qDebug() << QString(jdoc.toJson(QJsonDocument::Indented));

      LogManager::getInstance()->logJSON(jdoc);

      ComPackage* package = ComPackage::fromJson(jdoc);

      int endOfPackage = buffer.indexOf(_packageStart, _packageStart.length());
      if (endOfPackage != -1) {
        buffer.remove(0, endOfPackage);
      } else {
        buffer.clear();
        doContinue = false;
      }

      if (0 == package) {
        qCritical() << tr("Invalid package received!");
        return;
      }

      client_t id = _socket2clients[socket];
      emit packageReceived(id, package);
    }
  } while (doContinue);
}

//------------------------------------------------------------------------------

void TcpServer::socketDisconnect()
{
  QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
  if (!_socket2clients.contains(socket)) {
    qCritical() << tr("ERROR: socket not in map!");
    return;
  }

  client_t id = _socket2clients[socket];
  QString clientName = _clients[id].name;

  _socket2clients.remove(socket);
  _clientCount--;

  _clients[id].id = -1;
  _clients[id].name.clear();
  _clients[id].socket = 0;

  emit clientDisconnected(id, clientName);
}

//------------------------------------------------------------------------------

void TcpServer::acceptError(QAbstractSocket::SocketError socketError)
{
  qCritical() << "acceptError: " + SocketErrorToString(socketError);
}

//------------------------------------------------------------------------------

void TcpServer::socketError(QAbstractSocket::SocketError socketError)
{
  qCritical() << "socketError: " + SocketErrorToString(socketError);
}
