#include "private/precomp.h"

#include "tcpclient.h"
#include "utils.h"

//windows specific socket libraries
#ifdef Q_OS_WIN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#else
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#endif

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

TcpClient::TcpClient(QObject* parent) :
  QObject(parent)
{
  _packageStart.append((char)113);
  _packageStart.append((char)98);
  _packageStart.append((char)106);
  _packageStart.append((char)115);
  _packageStart.append((char)1);
  _packageStart.append((char)0);
  _packageStart.append((char)0);
  _packageStart.append((char)0);

  connect(&_client, SIGNAL(connected()),
          this, SIGNAL(connected()));
  connect(&_client, SIGNAL(readyRead()),
          this, SLOT(readPackage()));
  connect(&_client, SIGNAL(disconnected()),
          this, SIGNAL(disconnected()));
  connect(&_client, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SIGNAL(error(QAbstractSocket::SocketError)));
}

//------------------------------------------------------------------------------

TcpClient::~TcpClient()
{
  _client.close();
}

//------------------------------------------------------------------------------

void TcpClient::startConnection(const QString &hostname, int port)
{
  QHostAddress addr(hostname);
  _client.connectToHost(addr, port);

  int enableKeepAlive = 1;
  int fd = _client.socketDescriptor();

  #ifdef Q_OS_WIN
  setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char*)&enableKeepAlive, sizeof(enableKeepAlive));

  tcp_keepalive info;           //structure holding keepalive data
  info.keepaliveinterval = 2000;//if there is no resposne, how often next keepalive pakcets are sent in miliseconds
  info.keepalivetime = 10000;   //how often in miliseconds tcp sends keepalive probe
  info.onoff = 1;               //on

  WSAIoctl(fd,SIO_KEEPALIVE_VALS,&info,sizeof(info),NULL,0,NULL,NULL,NULL);
  #else
  setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &enableKeepAlive, sizeof(enableKeepAlive));

  int maxIdle = 10; /* seconds */
  setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &maxIdle, sizeof(maxIdle));

  int count = 3;  // send up to 3 keepalive packets out, then disconnect if no response
  setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &count, sizeof(count));

  int interval = 2;   // send a keepalive packet out every 2 seconds (after the 5 second idle period)
  setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));

  #endif
}

//------------------------------------------------------------------------------

void TcpClient::closeConnection()
{
  _client.close();
}

//------------------------------------------------------------------------------

bool TcpClient::send(const ComPackage &p)
{
  if (!_client.isWritable()) {
    qCritical() << tr("Socket is not writable!");
    return false;
  }

  QByteArray data = p.toByteArray();
  qint64 bytesSent = _client.write(data);
  if (bytesSent != static_cast<qint64>(data.length())) {
    qCritical() << tr("Could not send package!");
    return false;
  } else {
    return true;
  }
}

//------------------------------------------------------------------------------

void TcpClient::readPackage()
{
  _buffer += _client.readAll();

  bool doContinue = true;
  do {
    QJsonDocument jdoc = QJsonDocument::fromBinaryData(_buffer);
    if (jdoc.isNull()) {
      // we probably did not receive the full package yet
      doContinue = false;
    } else {
      ComPackage* package = ComPackage::fromJson(jdoc);

      int endOfPackage = _buffer.indexOf(_packageStart, _packageStart.length());
      if (endOfPackage != -1) {
        _buffer.remove(0, endOfPackage);
      } else {
        _buffer.clear();
        doContinue = false;
      }

      if (0 == package) {
        qCritical() << tr("Invalid package received!");
      } else {
        emit packageReceived(package);
      }
    }
  } while  (doContinue);
}
