#ifndef IODEVICEFORDATA_H
#define IODEVICEFORDATA_H
#include <QList>
#include <date.h>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QStringList>



class IODeviceForData
{
public:
    IODeviceForData();
    QList<double> leseUmsatzUndSpeichereRueckwertsInListe(int, int , QString );
    Date dat;
    QList<QString> lines;
};

#endif // IODEVICEFORDATA_H
