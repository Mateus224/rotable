#include "io_writeinmonthwithnewdata.h"
#define umsatz "umsatz.daten"

IO_WriteInMonthData::IO_WriteInMonthData()
{
}


/////////////////////////////////////////////////////////////////////////////////
/// In dieser Funktion wird ihr ein double übergeben. Dieser wird dann am Ende der
/// der Datei mit dem heutigem Datum angehängt, wenn das Datum noch nicht in der
/// Datei vorhanden ist.
/////////////////////////////////////////////////////////////////////////////////

void IO_WriteInMonthData::schreibeInUmsatz(double heuteigerUmsatz)
{
    QFile Umsatz(umsatz);
    if(!Umsatz.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Append ))
    {
        //qDebug()<<"schreibeInUmsatz";
        return;
    }
    QTextStream out(&Umsatz);
    QList <double> vergleicheTag;
    int ivergleicheTag;

    vergleicheTag=leseUmsatzUndSpeichereRueckwertsInListe(1,1,umsatz);
    if(!vergleicheTag.isEmpty())
    {
        ivergleicheTag=vergleicheTag.last();
        if (ivergleicheTag!=dat.date.dayOfYear())
            out<<heuteigerUmsatz<<","<<dat.date.dayOfYear()<<"\n";

    }
    Umsatz.close();
}
