#include "include/systemupdate.h"

using namespace rotable;

SystemUpdate::SystemUpdate( QObject *parent) : QObject(parent)
{

}

//------------------------------------------------------------------------------

QJsonValue SystemUpdate::toJSON() const {
  QJsonObject o;
  o["id"]=_id;
  o["currentVersion"]=_currentVersion;
  o["availableVersion"]=_availableVersion;
  o["dateCurrentVersion"]=_dateCurrentVersion;
  o["dateAvailableVersion"]=_dateAvailableVersion;
  return QJsonValue(o);
}

//------------------------------------------------------------------------------

SystemUpdate *SystemUpdate::fromJSON(const QJsonValue &jval)
{
  QJsonObject o = jval.toObject();

  if (o.contains("id")
          &&o.contains("currentVersion")
          &&o.contains("availableVersion")
          &&o.contains("dateCurrentVersion")
          &&o.contains("dateAvailableVersion"))
  {
    SystemUpdate *sy;
    sy->_id=o["id"].toInt();
    sy->_currentVersion=o["currentVersion"].toDouble();
    sy->_availableVersion=o["availableVersion"].toDouble();
    sy->_dateCurrentVersion=o["dateCurrentVersion"].toString();
    sy->_dateAvailableVersion=o["dateAvailableVersion"].toString();

    return sy;
  }
  return NULL;
}
