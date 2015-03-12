#include "include/waiter_client.h"
#include "private/precomp.h"
#include "compackage.h"
#include "utils.h"


//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------




Waiter_Client::Waiter_Client(const QString &configFilePath, QObject *parent)
  : QObject(parent),
    _accepted(false), _state("DISCONNECTED"), _stopping(false)
{
    ConfigError error = _config.load(configFilePath);

    switch (error) {
    case FileNotLoaded:
      qCritical() << tr("FATAL: Could not load %1").arg(configFilePath);
      exit(EXIT_FAILURE);
      break;
    case FileNotFound:
      qCritical() << tr("FATAL: File not found: %1").arg(configFilePath);
      exit(EXIT_FAILURE);
      break;
    case FileNoReadAccess:
      qCritical() << tr("FATAL: No read access on %1").arg(configFilePath);
      exit(EXIT_FAILURE);
      break;
    case FileNoWriteAccess:
      qCritical() << tr("FATAL: No write access on %1").arg(configFilePath);
      exit(EXIT_FAILURE);
      break;
    case FileParseError:
      qCritical() << tr("FATAL: Error parsing %1").arg(configFilePath);
      exit(EXIT_FAILURE);
      break;
    default:
      // everything is fine :)
      break;
    }
}

Waiter_Client::~Waiter_Client()
{
   // _stopping=true;
}

