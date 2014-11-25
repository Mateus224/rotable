#ifndef ROTABLE_LOGLISTENERREMOTE_H
#define ROTABLE_LOGLISTENERREMOTE_H

//------------------------------------------------------------------------------

#include "logmanager.h"

//------------------------------------------------------------------------------

namespace rotable {
  class LogListenerRemote;
}

//------------------------------------------------------------------------------
/**
 * @brief The LogListenerRemote class implements a remote log listener.
 */
class rotable::LogListenerRemote : public QObject, public LogManager::LogListener
{
  Q_OBJECT

public:
  /**
   * Constructor.
   *
   * @param socket        socket
   */
  LogListenerRemote(QAbstractSocket* socket)
    : QObject(0), LogListener(0), _socket(socket)
  {
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
  }

  /**
   * The log method has to be implemented in order to act on receiving log
   * messages.
   *
   * @param message       log message
   */
  void log(const LogManager::LogMessage& message) {
    Q_ASSERT(acceptsLevel(message.level()));
    Q_ASSERT(_socket);
    Q_ASSERT(_socket->isWritable());

    if (_socket && _socket->isWritable()) {
      union {
        int i;
        char c[sizeof(int)];
      } convert;

      QByteArray ba = message.message().toUtf8();

      convert.i = ba.size();
      ba.prepend(convert.c, sizeof(int));

      convert.i = message.level();
      ba.prepend(convert.c, sizeof(int));

      _socket->write(ba);
    }
  }

  /**
   * Get IO device of listener. (if any)
   *
   * @return              IO listener
   */
  const QIODevice* getIoDevice() const {
    return _socket;
  }

signals:
  void gimmeLogHistory(int level);

private slots:
  /**
   * Socket disconnected
   */
  void onDisconnected() {
    qDebug() << tr("Remote log listener disconnected.");
  }

  /**
   * Data received from remote listener.
   */
  void onReadyRead() {
    int flags;
    if (sizeof(int) == _socket->read((char*)&flags, sizeof(int))) {
      _acceptFlags = flags;

      emit gimmeLogHistory(flags);
    }
  }

private:
  QAbstractSocket* _socket;
}; // class LogListenerRemote

//------------------------------------------------------------------------------

#endif // ROTABLE_LOGLISTENERREMOTE_H
