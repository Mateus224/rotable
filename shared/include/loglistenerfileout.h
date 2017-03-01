#ifndef ROTABLE_LOGLISTENERFILEOUT_H
#define ROTABLE_LOGLISTENERFILEOUT_H

//------------------------------------------------------------------------------

#include "logmanager.h"

#include <fstream>
#include <iostream>

//------------------------------------------------------------------------------

namespace rotable {
  class LogListenerFileOut;
}

//------------------------------------------------------------------------------
/**
 * @brief The LogListenerStdOut class implements a log listener that prints to
 * stdout and stderr.
 */
class rotable::LogListenerFileOut : public QObject, public LogManager::LogListener
{
  Q_OBJECT

public:
  /**
   * Constructor, opens file to write logs into
   *
   * @param flags         log levels to receive (default is all)
   * @param parent        parent object
   */
  LogListenerFileOut(const std::string path = "defaultLog.txt", int flags = -1, QObject* parent = 0)
    : QObject(parent), LogListener(flags)
  {
      _logfile.open(path);
      success = _logfile.is_open();
      if (!success)
      {
          std::cout << "Error opening a file" << std::endl;
      }
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
      _logfile << qPrintable(message.message()) << std::endl;
    } break;
    case LogManager::warning:
    {
      _logfile << qPrintable("Warning: " + message.message()) << std::endl;
    } break;
    case LogManager::error:
    {
      _logfile << qPrintable("Error: " + message.message()) << std::endl;
    } break;
    case LogManager::qt:
    {
      _logfile << qUtf8Printable("QT: " + message.message()) << std::endl;
    } break;
    case LogManager::json:
    {
      _logfile << "[ " << qPrintable(QTime::currentTime().toString()) << " ]" << std::endl;
      _logfile << qPrintable(message.message()) << std::endl;
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

private:
  std::ofstream _logfile;
  bool success;

}; // class LogListenerFileOut

//------------------------------------------------------------------------------

#endif // ROTABLE_LOGLISTENERFILEOUT_H
