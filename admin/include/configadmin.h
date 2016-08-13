#ifndef ROTABLE_CONFIGADMIN_H
#define ROTABLE_CONFIGADMIN_H

//------------------------------------------------------------------------------

#ifndef QSTRING_H
#include <QString>
#endif

#include "configbase.h"

//------------------------------------------------------------------------------

/**
 * @brief
 *
 */
class ConfigAdmin : public rotable::ConfigBase
{
  Q_OBJECT

public:
  /**
   * Constructor.
   *
   * @param path      path to config file
   *                  (see error() for errors)
   * @param parent    parent element
   */
  ConfigAdmin(const QString& path, QObject* parent = 0);

  // Getters
  /**
   * @brief
   *
   * @return const QString
   */
  inline const QString& serverAddress() const { return _serverAddress; }
  /**
   * @brief
   *
   * @return int
   */
  inline int serverPort() const { return _serverPort; }
  /**
   * @brief
   *
   * @return const QString
   */
  inline const QString& adminName() const { return _adminName; }

  /**
   * @brief
   *
   * @param serverAddress
   */
  void setServerAddress(const QString& serverAddress);
  /**
   * @brief
   *
   * @param serverPort
   */
  void setServerPort(int serverPort);
  /**
   * @brief
   *
   * @param adminName
   */
  void setServerAdminName(const QString& adminName);

private:
  /**
   * Configuration has been loaded
   */
  virtual void loaded();

  void initData();

  int _serverPort; /**< TODO: describe */
  QString _serverAddress; /**< TODO: describe */
  QString _adminName; /**< TODO: describe */
}; // class ConfigClient

//------------------------------------------------------------------------------

#endif // ROTABLE_CONFIGADMIN_H
