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
