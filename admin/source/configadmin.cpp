#include "private/precomp.h"

#include "configadmin.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ConfigAdmin::ConfigAdmin(const QString& path, QObject* parent)
 : ConfigBase(path, parent), _serverPort(-1)
{
    // If config is empyt
    if(value("Admin/username", "") == "")
        initData();
    loaded();
}

//------------------------------------------------------------------------------

void ConfigAdmin::setServerAddress(const QString &serverAddress)
{
  if (serverAddress != _serverAddress) {
    _serverAddress = serverAddress;
    setValue("Network/address", serverAddress);
  }
}

//------------------------------------------------------------------------------

void ConfigAdmin::setServerPort(int serverPort)
{
  if (serverPort != _serverPort) {
    _serverPort = serverPort;
    setValue("Network/port", serverPort);
  }
}

//------------------------------------------------------------------------------

void ConfigAdmin::setServerAdminName(const QString &adminName)
{
  if (adminName != _adminName) {
    _adminName = adminName;
    setValue("Admin/username", adminName);
  }
}

//------------------------------------------------------------------------------

void ConfigAdmin::loaded()
{
  bool ok;
  _serverPort = value("Network/port").toInt(&ok);
  if (!ok) {
    qDebug() << tr("Error reading Network/port! Using default value of 5000.");
    _serverPort = 5000;
  }

  _serverAddress = value("Network/address").toString();
  _adminName = value("Admin/username").toString();
}

//------------------------------------------------------------------------------

void ConfigAdmin::init()
{
    setValue("Admin/username", "debugAdmin");
    if(value("Network/address", "") == "")
        setValue("Network/address", "127.0.0.1");
    if(value("Network/port", 0) == 0)
        setValue("Network/port", 5000);
}

//------------------------------------------------------------------------------
