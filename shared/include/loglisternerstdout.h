#ifndef ROTABLE_LOGLISTENERSTDOUT_H
#define ROTABLE_LOGLISTENERSTDOUT_H

//------------------------------------------------------------------------------

#include "logmanager.h"

#include <iostream>

//------------------------------------------------------------------------------

namespace rotable {
  class LogListenerStdOut;
}

//------------------------------------------------------------------------------
/**
 * @brief The LogListenerStdOut class implements a log listener that prints to
 * stdout and stderr.
 */
class rotable::LogListenerStdOut : public QObject, public LogManager::LogListener
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param flags         log levels to receive (default is all)
   * @param parent        parent object
   */
  LogListenerStdOut(int flags = -1, QObject* parent = 0)
    : QObject(parent), LogListener(flags)
  {
  }

  /**
   * The log method has to be implemented in order to act on receiving log
   * messages.
   *
   * @param message       log message
   */
  void log(const LogManager::LogMessage& message) {
    Q_ASSERT(acceptsLevel(message.level()));

    switch (message.level())
    {
    case LogManager::info:
    {
      std::cout << qPrintable(message.message()) << std::endl;
    } break;
    case LogManager::warning:
    {
      std::cout << qPrintable("Warning: " + message.message()) << std::endl;
    } break;
    case LogManager::error:
    {
      std::cerr << qPrintable("Error: " + message.message()) << std::endl;
    } break;
    case LogManager::qt:
    {
      std::cout << qPrintable("QT: " + message.message()) << std::endl;
    } break;
    case LogManager::json:
    {
      std::cout << qPrintable(message.message()) << std::endl;
    } break;
    default:
    {

    } break;
    }
  }

  /**
   * Get IO device of listener. (if any)
   *
   * @return              IO listener
   */
  const QIODevice* getIoDevice() const {
    return 0;
  }
}; // class LogListenerRemote

//------------------------------------------------------------------------------

#endif // ROTABLE_LOGLISTENERSTDOUT_H
