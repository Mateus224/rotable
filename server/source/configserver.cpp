#include "private/precomp.h"

#include "configserver.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ConfigServer::ConfigServer(const QString& path, QObject* parent)
 : ConfigBase(path, parent), _port(-1)
{
  // If config is empyt
  if(value("Database/host", "") == "")
      initData();
  loaded();
}

//------------------------------------------------------------------------------

void ConfigServer::loaded()
{
  bool ok;
  _port = value("Network/port").toInt(&ok);
  if (!ok) {
    qWarning() << tr("Error reading Network/port! Using default value of 5000.");
    _port = 5000;
  }

  _db_host = value("Database/host").toString();
  _db_name = value("Database/name").toString();
  _db_user = value("Database/user").toString();
  _db_pass = value("Database/pass").toString();
  _db_prefix = value("Database/prefix").toString();

  foreach (const QString& key, allKeys()) {
    if (key.startsWith("Images/")) {
      Image i;
      i.name = key.mid(7);
      i.path = value(key).toString();
      _images << i;
    }
  }

  emit portChanged();
  emit dbSettingsChanged();
}

//------------------------------------------------------------------------------

void ConfigServer::initData()
{
    setValue("Network/port", 5000);
    setValue("Database/host", "localhost");
    setValue("Database/name", "rotable");
    setValue("Database/user", "rotable");
    setValue("Database/pass", "rotable");
    setValue("Database/prefix", "rotable_");
}

//------------------------------------------------------------------------------
