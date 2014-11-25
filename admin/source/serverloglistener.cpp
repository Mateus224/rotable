#include "private/precomp.h"

#include "serverloglistener.h"
#include "utils.h"

//------------------------------------------------------------------------------

ServerLogListener::ServerLogListener(QObject* parent)
  : QObject(parent)
{
  connect(&_client, SIGNAL(connected()),
          this, SLOT(onConnectionEstablished()));
  connect(&_client, SIGNAL(readyRead()),
          this, SLOT(onReadyRead()));
  connect(&_client, SIGNAL(disconnected()),
          this, SLOT(onDisconnected()));
  connect(&_client, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(onError(QAbstractSocket::SocketError)));
}

//------------------------------------------------------------------------------

ServerLogListener::~ServerLogListener()
{
  _client.close();
}

//------------------------------------------------------------------------------

void ServerLogListener::startConnection(const QString& hostname, int port)
{
  QHostAddress addr(hostname);
  _client.connectToHost(addr, port);
}

//------------------------------------------------------------------------------

void ServerLogListener::stopConnection()
{
  _client.disconnectFromHost();
}

//------------------------------------------------------------------------------

void ServerLogListener::onConnectionEstablished()
{
  int flags = std::numeric_limits<int>::max() >> 1;
  if (sizeof(int) != _client.write((const char*)&flags, sizeof(int))) {
    qCritical() << tr("Could not send server log listener flags: %1")
                   .arg(_client.errorString());
  }
  emit connectionEstablished();
}

//------------------------------------------------------------------------------

void ServerLogListener::onReadyRead()
{
  _buffer += _client.readAll();

  bool doContinue = true;
  while (doContinue && !_buffer.isEmpty()) {
    union {
      int i;
      char c[sizeof(int)];
    } convert;

    memcpy(convert.c, _buffer.mid(0, sizeof(int)).constData(), sizeof(int));
    int level = convert.i;

    memcpy(convert.c, _buffer.mid(sizeof(int), sizeof(int)).constData(), sizeof(int));
    int packageSize = convert.i;

    if (_buffer.size() >= (packageSize + 2*static_cast<int>(sizeof(int)))) {
      int startIdx = 2*sizeof(int);
      QString text(_buffer.mid(startIdx, packageSize - 1));
      rotable::LogManager::LogMessage message(text, level);

      _buffer.remove(0, packageSize + startIdx);

      emit log(message);
    } else {
      doContinue = false;
    }
  }
}

//------------------------------------------------------------------------------

void ServerLogListener::onDisconnected()
{
  emit disconnected();
}

//------------------------------------------------------------------------------

void ServerLogListener::onError(QAbstractSocket::SocketError error)
{
  rotable::LogManager::LogMessage message(SocketErrorToString(error),
                                          rotable::LogManager::error);
  emit log(message);
}

//------------------------------------------------------------------------------
