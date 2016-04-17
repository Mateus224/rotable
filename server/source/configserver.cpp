#include "private/precomp.h"

#include "configserver.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ConfigServer::ConfigServer(const QString& path, QObject* parent)
 : ConfigBase(path, parent)
{
  // If config is empyt
  if(value("Database/host", "") == "")
      initData();
  loaded();
}

//------------------------------------------------------------------------------

void ConfigServer::loaded()
{

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
    setValue("Licence/path", "licence/");
}

//------------------------------------------------------------------------------
