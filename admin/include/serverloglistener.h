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

  /**
   * @brief
   *
   * @param hostname
   * @param port
   */
  void startConnection(const QString& hostname, int port);
  /**
   * @brief
   *
   */
  void stopConnection();

signals:
  /**
   * @brief
   *
   * @param message
   */
  void log(rotable::LogManager::LogMessage message);
  /**
   * @brief
   *
   */
  void disconnected();
  /**
   * @brief
   *
   */
  void connectionEstablished();

protected slots:
  /**
   * @brief
   *
   */
  void onConnectionEstablished();
  /**
   * @brief
   *
   */
  void onReadyRead();
  /**
   * @brief
   *
   */
  void onDisconnected();
  /**
   * @brief
   *
   * @param error
   */
  void onError(QAbstractSocket::SocketError error);

private:
  /* socket */
  QTcpSocket _client;

  /* Read buffer */
  QByteArray _buffer;
}; // class ServerLogListener

//------------------------------------------------------------------------------

#endif // SERVERLOGLISTENER_H
