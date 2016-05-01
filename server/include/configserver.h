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
//  Q_PROPERTY(QString licence_path READ licence_path WRITE setLicence_path NOTIFY licencePathChange)

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
  inline int port() const { return value("Network/port").toInt(); }
  inline const QString db_host() const { return value("Database/host").toString();}
  inline const QString db_name() const { return value("Database/name").toString(); }
  inline const QString db_user() const { return value("Database/user").toString(); }
  inline const QString db_pass() const { return value("Database/pass").toString(); }
  inline const QString db_prefix() const { return value("Database/prefix").toString(); }
  inline const QString licecne_path() const { return value("Licence/path").toString(); }

  inline void selLicence_path(const QString &path){setValue("Licence/path", path); emit licencePathChange();}

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
  void licencePathChange();

private:
  /**
   * Configuration has been loaded
   */
  void loaded();

  /**
   * @brief initData
   * Initialized config file
   */
  void initData();

  QList<Image> _images;
}; // class ConfigServer

//------------------------------------------------------------------------------

#endif // ROTABLE_CONFIGSERVER_H
