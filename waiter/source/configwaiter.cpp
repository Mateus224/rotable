#include "private/precomp.h"

#include "configwaiter.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ConfigWaiter::ConfigWaiter(QObject* parent)
  : ConfigBase(parent), _port(-1)
{

}

//------------------------------------------------------------------------------

ConfigWaiter::ConfigWaiter(const QString& path, QObject* parent)
 : ConfigBase(parent), _port(-1)
{
  load(path);
}

//------------------------------------------------------------------------------

void ConfigWaiter::loaded()
{
  bool ok;
  _port = _values["Network/port"].toInt(&ok);
  if (!ok) {
    qDebug() << tr("Error reading Network/port! Using default value of 5000.");
    _port = 5000;
  }

  _serverAddress = _values["Network/address"].toString();
  _clientName = _values["Network/name"].toString();

  emit portChanged();
  emit serverAddressChanged();
  emit clientNameChanged();
}
