#include "private/precomp.h"

#include "configbase.h"

//------------------------------------------------------------------------------

using namespace rotable;

////------------------------------------------------------------------------------

//ConfigBase::ConfigBase(QObject* parent) : QObject(parent),
//  _error(FileNotLoaded)
//{

//}

////------------------------------------------------------------------------------

//ConfigBase::ConfigBase(const QString& path, QObject* parent)
//  : QObject(parent)
//{
//  load(path);
//}

////------------------------------------------------------------------------------

//ConfigBase::~ConfigBase()
//{

//}

////------------------------------------------------------------------------------

//ConfigError ConfigBase::load(const QString& path)
//{
//  _path = path;

//  if (!QFileInfo::exists(_path))
//    return setError(FileNotFound);

//  QSettings settings(path, QSettings::IniFormat);

//  if (settings.status() == QSettings::AccessError)
//    return setError(FileNoReadAccess);
//  else if (settings.status() == QSettings::FormatError)
//    return setError(FileParseError);

//  QStringList keys = settings.allKeys();
//  foreach (QString key, keys)
//    _values[key] = settings.value(key);

//  _error = NoError;
//  loaded();
//  return _error;
//}

////------------------------------------------------------------------------------

//ConfigError ConfigBase::save(const QString& path)
//{
//  QString dest;
//  if (path.isEmpty())
//    dest = _path;
//  else
//    dest = path;

//  QSettings settings(dest, QSettings::IniFormat);

//  // QMap<QString, int>::const_iterator i = map.constBegin();
//  QMap<QString, QVariant>::const_iterator i = _values.constBegin();
//  for (; i != _values.constEnd(); ++i)
//    settings.setValue(i.key(), i.value());

//  settings.sync();
//  if (settings.status() == QSettings::AccessError)
//    return setError(FileNoWriteAccess);

//  return setError(NoError);
//}

////------------------------------------------------------------------------------

//QString ConfigBase::errorStr() const
//{
//  switch (_error) {
//  case NoError:
//    return tr("No error");
//  case FileNotFound:
//    return tr("Config file %1 could not be found!").arg(_path);
//  case FileNoReadAccess:
//    return tr("Could not read from config file %1. No access!").arg(_path);
//  case FileNoWriteAccess:
//    return tr("Could not write to config file %1. No access!").arg(_path);
//  case FileParseError:
//    return tr("Could not correctly parse config file %1! Not an ini file?").arg(_path);
//  default:
//    qDebug() << tr("Unknown error message in switch!");
//    return QString();
//  }
//}

////------------------------------------------------------------------------------

//ConfigError ConfigBase::setError(ConfigError error)
//{
//  _error = error;
//  emit errorChanged();
//  return _error;
//}

//------------------------------------------------------------------------------

ConfigBase::ConfigBase(const QString &path):
    QSettings(path, QSettings::IniFormat)
{

}

//------------------------------------------------------------------------------
