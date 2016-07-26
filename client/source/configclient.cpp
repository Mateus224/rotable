#include "private/precomp.h"

#include "configclient.h"
#include <QtNetwork/QNetworkInterface>

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ConfigClient::ConfigClient(const QString& path, QObject* parent)
 : ConfigBase(path, parent)
{
    if(value("Client/name", "") == "")
        initData();
}

//------------------------------------------------------------------------------

QString ConfigClient::macAdress() {
    QString mac("");
    // If we don't have save mac adress
    if ((mac = value("Network/mac", "").toString()) == "")
    {
        // Try find  active connection
        foreach(QNetworkInterface inter, QNetworkInterface::allInterfaces())
        {
            // Check if interface is up
            if(inter.flags() & QNetworkInterface::IsUp)
            {
                mac = inter.hardwareAddress();
                if (mac!="") break;
            }
        }

        // If we don't find active connection
        if(mac == "")
            // Set mac of first interface
            mac = QNetworkInterface::allInterfaces().first().hardwareAddress();
        setValue("Network/mac", mac);   // Set value to config
    }

    return mac;

}

//------------------------------------------------------------------------------

void ConfigClient::initData()
{
    if(value("Client/name", "") == "")
        setClientName("debug_table");
    if(value("Network/port", 0) == 0)
        setPort(5000);
    if(value("Network/address", "") == "")
        setServerAddress("localhost");
}

//------------------------------------------------------------------------------
