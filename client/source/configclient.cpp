#include "private/precomp.h"

#include "configclient.h"

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
