#ifndef IO_INIT_H
#define IO_INIT_H
#include <iodevicefordata.h>
#include <iostream>




class IO_init:public IODeviceForData
{
public:
    IO_init();
    void untersucheAufLueckenUndFuelleAuf();
    void JahrVollLegeNeueDateiAn();
    void schreibeMonatsUmsatz();
};

#endif // IO_INIT_H
