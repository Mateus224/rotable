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

void IO_WriteInMonthData::schreibeInUmsatz(double heuteigerUmsatz, int date)
{
    QFile Umsatz(umsatz);
    if(!Umsatz.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Append ))
    {
        qDebug()<<"schreibeNichtInUmsatz";
        return;
    }
    QTextStream out(&Umsatz);
    QList <double> vergleicheTag;
    int ivergleicheTag;
    //qDebug()<<"hierbin ich";
    vergleicheTag=leseUmsatzUndSpeichereRueckwertsInListe(1,1,umsatz);
    qDebug()<<"hierbin ich";
    if(!vergleicheTag.isEmpty())
    {
        qDebug()<<"hierbin ich auch";
        ivergleicheTag=vergleicheTag.last();
        if (ivergleicheTag!=dat.date.dayOfYear())
            out<<heuteigerUmsatz<<","<<date<<"\n";
    }
    else
    {
        out<<heuteigerUmsatz<<","<<date<<"\n";
    }
    Umsatz.close();
}
