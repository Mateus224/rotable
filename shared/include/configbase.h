#ifndef ROTABLE_CONFIGBASE_H
#define ROTABLE_CONFIGBASE_H

//------------------------------------------------------------------------------

//#ifndef QMAP_H
//#include <QMap>
//#endif

//#ifndef QVARIANT_H
//#include <QVariant>
//#endif

#ifndef QSETTINGS_H
#include <QSettings>
#endif

//------------------------------------------------------------------------------

namespace rotable {
  /**
   * The ConfigError enum contains all possible errors associated with
   * the ConfigBase class.
   */
  enum ConfigError {
    NoError = 0,
    FileNotLoaded,
    FileNotFound,
    FileNoReadAccess,
    FileNoWriteAccess,
    FileParseError
  };

  class ConfigBase;
}

//------------------------------------------------------------------------------

class rotable::ConfigBase: public QSettings
{
public:
    ConfigBase(const QString &path, QObject *parent);
};

//------------------------------------------------------------------------------


////------------------------------------------------------------------------------

///**
// * Base class for configuration loader classes.
// */
//class rotable::ConfigBase : public QObject
//{
//  Q_OBJECT

//  Q_PROPERTY(QString path READ path NOTIFY pathChanged)
//  Q_PROPERTY(QString errorStr READ errorStr NOTIFY errorChanged)

//public:
//  /**
//   * Default constructor
//   *
//   * @param parent    parent element
//   */
//  ConfigBase(QObject* parent = 0);

//  /**
//   * Constructor
//   *
//   * @param path      path to config file
//   *                  (see error() for errors)
//   * @param parent    parent element
//   */
//  ConfigBase(const QString& path, QObject* parent = 0);

//  /**
//    * Destructor
//    */
//  ~ConfigBase();

//  /**
//   * Load configuration file.
//   *
//   * @param path      path to config file
//   * @return          e_config_no_error on success
//   */
//  ConfigError load(const QString& path);

//  /**
//   * Save configuration to file.
//   *
//   * @param path      destination file path (optional, will use input path)
//   * @return          e_config_no_error on success
//   */
//  ConfigError save(const QString& path = QString());

//  /**
//   * Get last error.
//   *
//   * @return          last error
//   */
//  ConfigError error() const { return _error; }

//  /**
//   * Get config file path.
//   *
//   * @return          config file path
//   */
//  inline const QString& path() const { return _path; }

//  /**
//   * Get last error as a string.
//   *
//   * @return          last error string
//   */
//  QString errorStr() const;

//signals:
//  void errorChanged();
//  void pathChanged();

//protected:
//  virtual void loaded() {}

//  /** Key-Value map */
//  QMap<QString, QVariant> _values;

//private:
//  /**
//   * Set current error.
//   *
//   * @param error     new error
//   * @return          new error
//   */
//  ConfigError setError(ConfigError error);

//  /** Path to configuration file */
//  QString _path;

//  /** Last error */
//  ConfigError _error;
//}; // class ConfigBase

////------------------------------------------------------------------------------

#endif // ROTABLE_CONFIGBASE_H
