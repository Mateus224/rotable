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
   * Constructor.
   *
   * @param path      path to config file
   *                  (see error() for errors)
   * @param parent    parent element
   */
  ConfigClient(const QString& path, QObject* parent = 0);

  // Getters
  inline const QString serverAddress() const { return value("Network/address").toString();}
  inline int port() const { return value("Network/port").toInt(); }
  inline const QString clientName() const {return value("Client/name").toString();}

  QString macAdress();

  // Setter
  inline void setServerAddress(const QString& address) { setValue("Network/address", address);
                                                         emit serverAddressChanged();}
  inline void setPort(const int &port){ setValue("Network/port", port); emit portChanged();}
  inline void setClientName(const QString &name){ setValue("Client/name", name);
                                                  emit clientNameChanged();}


signals:
  void portChanged();
  void serverAddressChanged();
  void clientNameChanged();

private:
  void initData();

}; // class ConfigClient

//------------------------------------------------------------------------------

#endif // ROTABLE_CONFIGCLIENT_H
