#ifndef BATTERYINFO_H
#define BATTERYINFO_H

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifdef Q_OS_WIN
#include "windows.h"
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

public:
    BatteryInfo();
    int getBatteryStatus();

signals:
    void batteryStatusChanged();
};

#endif // BATTERYINFO_H
