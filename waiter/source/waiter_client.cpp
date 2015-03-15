#include "include/waiter_client.h"



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

    //####pro

    connect(&_tcp, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(&_tcp, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    connect(&_tcp, SIGNAL(packageReceived(ComPackage*)),
            this, SLOT(packageReceived(ComPackage*)));
    connect(&_reconnectTimer, SIGNAL(timeout()),
            this, SLOT(reconnect()));

}

Waiter_Client::~Waiter_Client()
{
   // _stopping=true;
}


//------------------------------------------------------------------------------

bool Waiter_Client::startup()
{
  reconnect();
  return true;
}


//------------------------------------------------------------------------------

void Waiter_Client::reconnect()
{
  _tcp.startConnection(_config.serverAddress(), _config.port());
}

//------------------------------------------------------------------------------

void Waiter_Client::connected()
{
  qDebug() << tr("Connection established");

  ComPackageConnectionRequest request;
  request.setClientName(_config.clientName());
  if (!_tcp.send(request)) {
    qCritical() << tr("FATAL: Could not send connection request package!");
    exit(EXIT_FAILURE);
  }
}

//------------------------------------------------------------------------------

void Waiter_Client::disconnected()
{
  setState("DISCONNECTED");

  if (!_stopping) {
    // Todo: do not reconnect if we want to close the app
    qDebug() << tr("Connection lost... trying to reconnect");

    _reconnectTimer.setSingleShot(true);
    _reconnectTimer.setInterval(500);
    _reconnectTimer.start();
  }
}

//------------------------------------------------------------------------------

void Waiter_Client::packageReceived(ComPackage *package)
{
  if (package) {
    switch (package->type()) {
    case ComPackage::ConnectionRequest:
    {
      qCritical() << tr("ERROR: Received ConnectionRequest package!");
    } break;

    case ComPackage::ConnectionAccept:
    {
      qDebug() << tr("Client accepted by server.");
      _accepted = true;
      setState("SCREENSAVER");
      //requestCategoryIds();
    } break;

    case ComPackage::DataRequest:
    {
      qCritical() << tr("ERROR: Received DataRequest package!");
    } break;

    case ComPackage::DataReturn:
    {
      //dataReturned(static_cast<ComPackageDataReturn*>(package));
    } break;

    case ComPackage::DataChanged:
    {
      //dataChanged(static_cast<ComPackageDataChanged*>(package));
    } break;

    case ComPackage::DataSet:
    {
      qCritical() << tr("ERROR: Received DataSet package!");
    } break;

    case ComPackage::Reject:
    {
      qDebug() << tr("WARNING: Package has been rejected!");
      //rejected(static_cast<ComPackageReject*>(package));
    } break;

    default:
    {
      qDebug() << tr("WARNING: Received unknown package!");
    } break;
    }
  }
}

//------------------------------------------------------------------------------

void Waiter_Client::rejected(ComPackageReject *rej)
{
  if (_dataRequest.contains(rej->originId())) {
    _dataRequest.remove(rej->originId());
  }
}

//------------------------------------------------------------------------------

void Waiter_Client::setState(const QString &state)
{
  _state = state;
  //emit stateChanged();
}

//------------------------------------------------------------------------------




