#ifndef ROTABLE_CONFIGCLIENT_H
#define ROTABLE_CONFIGCLIENT_H

//------------------------------------------------------------------------------

#ifndef QSTRING_H
#include <QString>
#endif

#include "configbase.h"

//------------------------------------------------------------------------------

namespace rotable {
  class ConfigClient;
}

//------------------------------------------------------------------------------

class rotable::ConfigClient : public ConfigBase
{
  Q_OBJECT

  Q_PROPERTY(int port READ port NOTIFY portChanged)
  Q_PROPERTY(QString serverAddress READ serverAddress NOTIFY serverAddressChanged)
  Q_PROPERTY(QString clientName READ clientName NOTIFY clientNameChanged)

public:
  /**
   * Default constructor
   *
   * @param parent    parent element
   */
  ConfigClient(QObject* parent = 0);

  /**
   * Constructor.
   *
   * @param path      path to config file
   *                  (see error() for errors)
   * @param parent    parent element
   */
  ConfigClient(const QString& path, QObject* parent = 0);

  // Getters
  inline const QString& serverAddress() const { return _serverAddress; }
  inline int port() const { return _port; }
  inline const QString& clientName() const { return _clientName; }

signals:
  void portChanged();
  void serverAddressChanged();
  void clientNameChanged();

private:
  /**
   * Configuration has been loaded
   */
  virtual void loaded();

  int _port;
  QString _serverAddress;
  QString _clientName;
}; // class ConfigClient

//------------------------------------------------------------------------------

#endif // ROTABLE_CONFIGCLIENT_H
