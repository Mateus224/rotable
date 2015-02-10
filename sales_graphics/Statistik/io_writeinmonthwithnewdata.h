#ifndef IO_WRITEINMONTHDATA_H
#define IO_WRITEINMONTHDATA_H
#include <iodevicefordata.h>


class IO_WriteInMonthData: public IODeviceForData
{

public:
    IO_WriteInMonthData();
    void schreibeInUmsatz(double, int,QString);

};


#endif // IO_WRITEINMONTHDATA_H
