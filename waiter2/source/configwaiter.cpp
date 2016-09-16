#include "private/precomp.h"

#include "configwaiter.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ConfigWaiter::ConfigWaiter(const QString& path, QObject* parent)
 : ConfigBase(path, parent), _port(-1)
{
    // If config is empyt
    if(value("Waiter/name", "") == "")
        initData();
    loaded();
}

//------------------------------------------------------------------------------

void ConfigWaiter::loaded()
{
  bool ok;
  _port = value("Network/port").toInt(&ok);
  if (!ok) {
    qDebug() << tr("Error reading Network/port! Using default value of 5000.");
    _port = 5000;
  }

  _serverAddress = value("Network/address").toString();
  _clientName = value("Waiter/name").toString();

  emit portChanged();
  emit serverAddressChanged();
  emit clientNameChanged();

}

//------------------------------------------------------------------------------

void ConfigWaiter::initData()
{
    //if(value("Network/address", "") == "")
        setValue("Network/address", "192.168.2.107");
    if(value("Network/port", 0) == 0)
        setValue("Network/port", 5000);
    setValue("Waiter/name", "debug_waiter");
}

//------------------------------------------------------------------------------
