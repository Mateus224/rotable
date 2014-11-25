#include "private/precomp.h"

#include "configserver.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ConfigServer::ConfigServer(QObject* parent)
  : ConfigBase(parent), _port(-1)
{

}

//------------------------------------------------------------------------------

ConfigServer::ConfigServer(const QString& path, QObject* parent)
 : ConfigBase(parent), _port(-1)
{
  load(path);
}

//------------------------------------------------------------------------------

void ConfigServer::loaded()
{
  bool ok;
  _port = _values["Network/port"].toInt(&ok);
  if (!ok) {
    qWarning() << tr("Error reading Network/port! Using default value of 5000.");
    _port = 5000;
  }

  _db_host = _values["Database/host"].toString();
  _db_name = _values["Database/name"].toString();
  _db_user = _values["Database/user"].toString();
  _db_pass = _values["Database/pass"].toString();
  _db_prefix = _values["Database/prefix"].toString();

  foreach (const QString& key, _values.keys()) {
    if (key.startsWith("Images/")) {
      Image i;
      i.name = key.mid(7);
      i.path = _values[key].toString();
      _images << i;
    }
  }

  emit portChanged();
  emit dbSettingsChanged();
}
