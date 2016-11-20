#ifndef WIFIINFO_H
#define WIFIINFO_H

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifdef Q_OS_WIN

#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>

#include <stdio.h>
#include <stdlib.h>

#else
//Linux libraries will go here if needed
#endif

namespace rotable {
class WifiInfo;
}

class rotable::WifiInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int wifiStatus READ getWifiStatus NOTIFY wifiStatusChanged)

public:
    WifiInfo();
    int getWifiStatus();

signals:
    void wifiStatusChanged();
};

#endif // WIFIINFO_H
