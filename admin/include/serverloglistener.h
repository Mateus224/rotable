#ifndef SERVERLOGLISTENER_H
#define SERVERLOGLISTENER_H

//------------------------------------------------------------------------------

#include "logmanager.h"

#include <QObject>
#include <QTcpSocket>

//------------------------------------------------------------------------------

/**
 * This class listenes for log messages of the server.
 */
class ServerLogListener : public QObject
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param parent            object
   */
  explicit ServerLogListener(QObject *parent = 0);

  ~ServerLogListener();

  void startConnection(const QString& hostname, int port);
  void stopConnection();

signals:
  void log(rotable::LogManager::LogMessage message);
  void disconnected();
  void connectionEstablished();

protected slots:
  void onConnectionEstablished();
  void onReadyRead();
  void onDisconnected();
  void onError(QAbstractSocket::SocketError error);

private:
  /* socket */
  QTcpSocket _client;

  /* Read buffer */
  QByteArray _buffer;
}; // class ServerLogListener

//------------------------------------------------------------------------------

#endif // SERVERLOGLISTENER_H
