#include "batteryinfo.h"

using namespace rotable;

BatteryInfo::BatteryInfo()
{
};

int BatteryInfo::getBatteryStatus()
{
    #ifdef Q_OS_WIN
        SYSTEM_POWER_STATUS status;
        GetSystemPowerStatus(&status);
        return status.BatteryLifePercent;
    #else
        return -1;
    #endif
}

bool BatteryInfo::getIsCharging()
{
#ifdef Q_OS_WIN
    SYSTEM_POWER_STATUS status;
    GetSystemPowerStatus(&status);
    bool charging = (status.BatteryFlag & 8);//battery charging
    return charging;
#else
    return false;
#endif
}
