#include "private/precomp.h"

#include "configadmin.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ConfigAdmin::ConfigAdmin(QObject* parent)
  : ConfigBase(parent), _serverPort(5000)
{

}

//------------------------------------------------------------------------------

ConfigAdmin::ConfigAdmin(const QString& path, QObject* parent)
 : ConfigBase(parent), _serverPort(-1)
{
  load(path);
}

//------------------------------------------------------------------------------

void ConfigAdmin::setServerAddress(const QString &serverAddress)
{
  if (serverAddress != _serverAddress) {
    _serverAddress = serverAddress;
    _values["Server/address"] = serverAddress;
    save(path());
  }
}

//------------------------------------------------------------------------------

void ConfigAdmin::setServerPort(int serverPort)
{
  if (serverPort != _serverPort) {
    _serverPort = serverPort;
    _values["Server/port"] = serverPort;
    save(path());
  }
}

//------------------------------------------------------------------------------

void ConfigAdmin::setServerAdminName(const QString &adminName)
{
  if (adminName != _adminName) {
    _adminName = adminName;
    _values["Server/username"] = adminName;
    save(path());
  }
}

//------------------------------------------------------------------------------

void ConfigAdmin::loaded()
{
  bool ok;
  _serverPort = _values["Server/port"].toInt(&ok);
  if (!ok) {
    qDebug() << tr("Error reading Network/port! Using default value of 5000.");
    _serverPort = 5000;
  }

  _serverAddress = _values["Server/address"].toString();
  _adminName = _values["Server/username"].toString();
}
