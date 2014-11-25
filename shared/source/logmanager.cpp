#include "private/precomp.h"

#include <QTcpSocket>
#include <QAbstractSocket>

#include "logmanager.h"
#include "compackage.h"
#include "utils.h"
#include "loglistenerremote.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

static LogManager *S_instance = 0;

//------------------------------------------------------------------------------

void rotableQtMessageOutput(QtMsgType type,
                            const QMessageLogContext &context,
                            const QString &msg)
{
  if (type) {
    QByteArray localMsg = msg.toLocal8Bit();
    QString message = QString("%1 (%2:%3, %4)")
                      .arg(localMsg.constData())
                      .arg(context.file)
                      .arg(context.line)
                      .arg(context.function);

    switch (type) {
    case QtDebugMsg:
    {
      LogManager::getInstance()->log(message, LogManager::qt);
    } break;
    case QtWarningMsg:
    {
      LogManager::getInstance()->log(message, LogManager::warning);
    } break;
    case QtCriticalMsg:
    case QtFatalMsg:
    {
      LogManager::getInstance()->log(message, LogManager::error);
    } break;
    }
  }
}

//------------------------------------------------------------------------------

LogManager*LogManager::getInstance()
{
  if (0 == S_instance) {
    S_instance = new LogManager();
  }
  return S_instance;
}

//------------------------------------------------------------------------------

void LogManager::logError(QString text)
{
  emit logMessageAdd(text, error);
}

//------------------------------------------------------------------------------

void LogManager::logWarning(QString text)
{
  emit logMessageAdd(text, warning);
}

//------------------------------------------------------------------------------

void LogManager::logInfo(QString text)
{
  emit logMessageAdd(text, info);
}

//------------------------------------------------------------------------------

void LogManager::logJSON(QJsonDocument jdoc)
{
  emit logMessageAdd(jdoc.toJson(QJsonDocument::Indented), json);
}

//------------------------------------------------------------------------------

void LogManager::log(QString message, LogManager::LogLevels level)
{
  emit logMessageAdd(message, level);
}

//------------------------------------------------------------------------------

void LogManager::addListener(LogListener* listener)
{
  _listeners.append(listener);
}

//------------------------------------------------------------------------------

void LogManager::removeListener(LogListener* listener)
{
  _listeners.removeAll(listener);
}

//------------------------------------------------------------------------------

void LogManager::registerQtWarnings()
{
  qInstallMessageHandler(rotableQtMessageOutput);
}

//------------------------------------------------------------------------------

bool LogManager::startServer(int port)
{
  if (_server.isListening()) {
    Q_ASSERT(false);
    _server.close();
  } else {
    connect(&_server, SIGNAL(newConnection()),
            this, SLOT(onAcceptConnection()));
    connect(&_server, SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)));
  }

  bool success = _server.listen(QHostAddress::Any, port);
  Q_ASSERT(success);
  return success;
}

//------------------------------------------------------------------------------

void LogManager::onLogMessageAdd(QString text, int level)
{
  LogMessage message(text, level);

  foreach (LogListener* listener, _listeners) {
    if (listener->acceptsLevel(level)) {
      listener->log(message);
    }
  }

  _history << message;
  if (_history.size() > _historySize) {
    _history.removeFirst();
  }

  emit logMessageAdded(text, level);
}

//------------------------------------------------------------------------------

void LogManager::onAcceptConnection()
{
  QTcpSocket* client = _server.nextPendingConnection();

  if (client) {
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(client, SIGNAL(disconnected()),
            this, SLOT(onRemoteClientDisconnected()));

    LogListenerRemote* remoteListener = new LogListenerRemote(client);

    connect(remoteListener, SIGNAL(gimmeLogHistory(int)),
            this, SLOT(onGimmeLogHistory(int)));

    addListener(remoteListener);
  }
}

//------------------------------------------------------------------------------

void LogManager::onSocketError(QAbstractSocket::SocketError error)
{
  logError(QString("Socket error in LogManager: %1")
           .arg(SocketErrorToString(error)));
}

//------------------------------------------------------------------------------

void LogManager::onGimmeLogHistory(int flags)
{
  LogListener* listener = reinterpret_cast<LogListener*>(sender());
  if (listener) {
    foreach (const LogMessage& message, _history) {
      if (0 != (flags & (1 << message.level()))) {
      //if (listener->acceptsLevel(message.level())) {
        listener->log(message);
      }
    }
  }
}

//------------------------------------------------------------------------------

void LogManager::onRemoteClientDisconnected()
{
  QTcpSocket* client = static_cast<QTcpSocket*>(sender());
  if (client) {
    for (int i = 0; i < _listeners.size(); ++i) {
      if (_listeners.at(i)->getIoDevice() == client) {
        _listeners.removeAt(i);
        break;
      }
    }
  }
}

//------------------------------------------------------------------------------

LogManager::LogManager(int historySize) : _historySize(historySize)
{
  connect(this, SIGNAL(logMessageAdd(QString,int)),
          this, SLOT(onLogMessageAdd(QString,int)),
          Qt::QueuedConnection);
}
