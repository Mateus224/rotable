#ifndef ROTABLE_CONFIGSERVER_H
#define ROTABLE_CONFIGSERVER_H

//------------------------------------------------------------------------------

#ifndef STRING_H
#include <QString>
#endif

#ifndef PIXMAP_H
#include <QPixmap>
#endif

#include "configbase.h"

//------------------------------------------------------------------------------

namespace rotable {
  class ConfigServer;
}

//------------------------------------------------------------------------------

/**
 * The ConfigServer class reads the content of the server configuration
 * ini file.
 */
class rotable::ConfigServer : public rotable::ConfigBase
{
  Q_OBJECT

  Q_PROPERTY(int port READ port NOTIFY portChanged)
  Q_PROPERTY(QString db_host READ db_host NOTIFY dbSettingsChanged)
  Q_PROPERTY(QString db_name READ db_name NOTIFY dbSettingsChanged)
  Q_PROPERTY(QString db_user READ db_user NOTIFY dbSettingsChanged)
  Q_PROPERTY(QString db_pass READ db_pass NOTIFY dbSettingsChanged)
  Q_PROPERTY(QString db_prefix READ db_prefix NOTIFY dbSettingsChanged)

public:
  /**
   * Image information
   */
  struct Image {
    /* Image name for access in QML */
    QString name;

    /* Image path on the HDD */
    QString path;
  };

  /**
   * Constructor.
   *
   * @param path      path to config file
   *                  (see error() for errors)
   * @param parent    parent element
   */
  ConfigServer(const QString& path, QObject* parent = 0);

  // Getters
  inline int port() const { return _port; }
  inline const QString& db_host() const { return _db_host; }
  inline const QString& db_name() const { return _db_name; }
  inline const QString& db_user() const { return _db_user; }
  inline const QString& db_pass() const { return _db_pass; }
  inline const QString& db_prefix() const { return _db_prefix; }

  /**
   * Get name/paths of all images.
   *
   * @return          image names and paths
   */
  QList<Image> images() const {
    return _images;
  }

signals:
  void portChanged();
  void dbSettingsChanged();

private:
  /**
   * Configuration has been loaded
   */
  void loaded();

  void initData();

  int _port;
  QString _db_host;
  QString _db_name;
  QString _db_user;
  QString _db_pass;
  QString _db_prefix;
  QList<Image> _images;
}; // class ConfigServer

//------------------------------------------------------------------------------

#endif // ROTABLE_CONFIGSERVER_H
