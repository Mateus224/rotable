#ifndef IO_INIT_DAY_H
#define IO_INIT_DAY_H
#include <date.h>
#include <QDebug>
#include "iodevicefordata.h"

class io_init_day:public IODeviceForData
{

public:

    io_init_day();
    void init(double);
    Date ti;


};

#endif // IO_INIT_DAY_H
