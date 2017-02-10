#ifndef BATTERYINFO_H
#define BATTERYINFO_H

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifdef Q_OS_WIN
#include <windows.h>
#else
//Linux libraries will go here if needed
#endif

namespace rotable {
class BatteryInfo;
}

class rotable::BatteryInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int batteryStatus READ getBatteryStatus NOTIFY batteryStatusChanged)
    Q_PROPERTY(bool isCharging READ getIsCharging NOTIFY isChargingChanged)

public:
    BatteryInfo();
    int getBatteryStatus();
    bool getIsCharging();

signals:
    void batteryStatusChanged();
    void isChargingChanged();
};

#endif // BATTERYINFO_H
