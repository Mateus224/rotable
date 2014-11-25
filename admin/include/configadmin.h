#ifndef ROTABLE_CONFIGADMIN_H
#define ROTABLE_CONFIGADMIN_H

//------------------------------------------------------------------------------

#ifndef QSTRING_H
#include <QString>
#endif

#include "configbase.h"

//------------------------------------------------------------------------------

class ConfigAdmin : public rotable::ConfigBase
{
  Q_OBJECT

public:
  /**
   * Default constructor
   *
   * @param parent    parent element
   */
  ConfigAdmin(QObject* parent = 0);

  /**
   * Constructor.
   *
   * @param path      path to config file
   *                  (see error() for errors)
   * @param parent    parent element
   */
  ConfigAdmin(const QString& path, QObject* parent = 0);

  // Getters
  inline const QString& serverAddress() const { return _serverAddress; }
  inline int serverPort() const { return _serverPort; }
  inline const QString& adminName() const { return _adminName; }

  void setServerAddress(const QString& serverAddress);
  void setServerPort(int serverPort);
  void setServerAdminName(const QString& adminName);

private:
  /**
   * Configuration has been loaded
   */
  virtual void loaded();

  int _serverPort;
  QString _serverAddress;
  QString _adminName;
}; // class ConfigClient

//------------------------------------------------------------------------------

#endif // ROTABLE_CONFIGADMIN_H
