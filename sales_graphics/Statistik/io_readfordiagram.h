#ifndef IO_READFORDIAGRAM_H
#define IO_READFORDIAGRAM_H
#include <iodevicefordata.h>
#define MonatsUmsatz "umsatz.daten"

class IO_ReadForDiagram: public IODeviceForData
{
public:
    IO_ReadForDiagram();
    double* leseAusUmsatzDiesesJahr();
    double* leseAusUmsatzVorLetzenJahr();
    double* leseAusUmsatzVorVorLetzenJahr();
};

#endif // IO_READFORDIAGRAM_H
