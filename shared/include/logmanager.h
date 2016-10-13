#ifndef ROTABLE_LOGMANAGER_H
#define ROTABLE_LOGMANAGER_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QAbstractSocket>
#include <QIODevice>
#include <QList>
#include <QTcpServer>

//------------------------------------------------------------------------------

namespace rotable {
  class LogManager;
  class ComPackage;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::LogManager allows an application to store and send
 * log messages.
 *
 * It also allows remote applications to connect to it and read all log
 * messages.
 *
 * This class is threadsafe (hopefully ;)
 */
class rotable::LogManager : public QObject
{
  Q_OBJECT

public:
  /**
   * Enumeration of different log message types (levels).
   */
  enum LogLevels {
    info = 0,
    error,
    warning,
    qt,
    json
  };

  /**
   * @brief The LogMessage class defines a log message.
   */
  class LogMessage {
  public:
    /**
     * Default constructor
     */
    inline LogMessage() {}

    /**
     * Constructor.
     *
     * @param message           log message
     * @param level             log level
     */
    inline LogMessage(const QString& message, int level)
      : _message(message), _level(level) {}

    /**
     * Get log message.
     *
     * @return                  log message
     */
    inline const QString& message() const { return _message; }

    /**
     * Get log level.
     *
     * @return                  log level
     */
    inline LogLevels level() const { return static_cast<LogLevels>(_level); }

  private:
    /* Log message */
    QString _message;

    /* Log level */
    int _level;
  }; // class LogMessage

  /**
   * @brief The LogListener class defines a log listener.
   */
  class LogListener {
  public:
    /**
     * Constructor.
     *
     * @param flags         flags (log levels to receive)
     */
    inline LogListener(int flags) : _acceptFlags(flags) {}

    /**
     * Add a log level this listener wants to receive.
     *
     * @param level         log level to receive
     */
    inline void addLogLevel(LogLevels level) {
      _acceptFlags |= 1 << level;
    }

    /**
     * Check whether this device accepts given log level.
     *
     * @param level         log level
     * @return              true if device wants this log level
     */
    inline bool acceptsLevel(int level) const {
      int levelFlag = (int)1 << level;
      int flags = _acceptFlags;
      int res = flags & levelFlag;
      return res != 0;
    }

    /**
     * The log method has to be implemented in order to act on receiving log
     * messages.
     *
     * @param message       log message
     */
    virtual void log(const LogMessage& message) = 0;

    /**
     * Get IO device of listener. (if any)
     *
     * @return              IO listener
     */
    virtual const QIODevice* getIoDevice() const = 0;

  protected:
    /* Receiving log levels */
    int _acceptFlags;
  }; // class LogListener

  /**
   * Get static instance.
   *
   * @return                  singleton instance
   */
  static LogManager* getInstance();

  /**
   * Log an error message.
   *
   * @param text              message
   */
  void logError(QString text);

  /**
   * Log a warning message.
   *
   * @param text              message
   */
  void logWarning(QString text);

  /**
   * Log an info message.
   *
   * @param text              message
   */
  void logInfo(QString text);

  /**
   * Log a JSON document.
   *
   * @param jdoc              document
   */
  void logJSON(QJsonDocument jdoc);

  /**
   * Log a new message.
   *
   * @param message       log message
   * @param level         log level
   */
  void log(QString message, LogLevels level);

  /**
   * Add a new listener for logging.
   *
   * @param listener          listener
   */
  void addListener(LogListener* listener);

  /**
   * Remove a logging listener.
   *
   * @param listener          listener
   */
  void removeListener(LogListener* listener);

  /**
   * Redirect Qt warnings to this class.
   */
  void registerQtWarnings();

  /**
   * Start waiting for incoming connections.
   *
   * @param port              port to wait on
   * @return                  true on success
   */
  bool startServer(int port);

signals:
  /* A new log message has been added */
  void logMessageAdded(QString text, int level);

  /* A new log message is about to be added */
  void logMessageAdd(QString text, int level);

private slots:
  /**
   * A new log message has to be added.
   *
   * @param text          log message
   * @param level         log level
   */
  void onLogMessageAdd(QString text, int level);

  /**
   * A new connection request received.
   */
  void onAcceptConnection();

  /**
   * Socket error.
   *
   * @param error         error
   */
  void onSocketError(QAbstractSocket::SocketError error);

  void onGimmeLogHistory(int flags);
  /**
   * @brief
   *
   */
  void onRemoteClientDisconnected();

private:
  /**
   * Default constructor (made private because class is a singleton).
   */
  LogManager(int historySize = 64);

  /* Log message listeners */
  QList<LogListener*> _listeners;

  /* Log message send server */
  QTcpServer _server;

  /* Log message history */
  QList<LogMessage> _history;

  /* Size of history */
  int _historySize;
}; // class LogManager

//------------------------------------------------------------------------------

#endif // ROTABLE_LOGMANAGER_H
