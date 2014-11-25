#include "private/precomp.h"

#include "tcpclient.h"
#include "configclient.h"
#include "utils.h"
#include "compackage.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

TcpClient::TcpClient(QObject *parent) :
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
          this, SLOT(error(QAbstractSocket::SocketError)));
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

QAbstractSocket::SocketError TcpClient::last_error() const
{
  return _client.error();
}

//------------------------------------------------------------------------------

void TcpClient::error(QAbstractSocket::SocketError socketError)
{
  qCritical() << SocketErrorToString(socketError);

  if (_client.state() == QTcpSocket::UnconnectedState) {
    emit disconnected();
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
  } while (doContinue);
}
