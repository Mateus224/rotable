#include "io_writeinmonthwithnewdata.h"

#define umsatz "umsatz.data"
#define ThisDay "ThisDay.data"

IO_WriteInMonthData::IO_WriteInMonthData()
{
}


/////////////////////////////////////////////////////////////////////////////////
/// In dieser Funktion wird ihr ein double übergeben. Dieser wird dann am Ende der
/// der Datei mit dem heutigem Datum angehängt, wenn das Datum noch nicht in der
/// Datei vorhanden ist.
/////////////////////////////////////////////////////////////////////////////////

void IO_WriteInMonthData::schreibeInUmsatz(double heuteigerUmsatz, int date,QString Dateipfad )
{
    QFile Umsatz(Dateipfad);
    if(!Umsatz.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Append ))
    {
        qDebug()<<"schreibe nicht in Umsatz";
        return;
    }
    QTextStream out(&Umsatz);
    QList <double> lastElement;
    int ivergleicheTag;
    double addTurnOver;
    if(Dateipfad==umsatz)
    {
        lastElement=leseUmsatzUndSpeichereRueckwertsInListe(1,1,Dateipfad);
        if(!lastElement.isEmpty()) //falls die Liste noch nicht angelegt wurde
        {
            ivergleicheTag=lastElement.last();
            if (ivergleicheTag!=dat.date.dayOfYear())
                out<<heuteigerUmsatz<<","<<date<<"\n";
        }
        else
        {
            out<<heuteigerUmsatz<<","<<date<<"\n";
        }
    }
    else if(Dateipfad==ThisDay)
    {
        lastElement=leseUmsatzUndSpeichereRueckwertsInListe(1,0,Dateipfad);
        if(!lastElement.isEmpty())//falls die Liste noch nicht angelegt wurde
        {

            addTurnOver=lastElement.last();
            heuteigerUmsatz=heuteigerUmsatz+addTurnOver;
            out<<heuteigerUmsatz<<"\n";
        }
        else
        {
            out<<heuteigerUmsatz<<"\n";
        }
    }
    Umsatz.close();
}
