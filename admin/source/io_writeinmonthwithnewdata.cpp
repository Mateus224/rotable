#include "private/precomp.h"

#include "io_writeinmonthwithnewdata.h"
#define umsatz "umsatz.daten"

IO_WriteInMonthData::IO_WriteInMonthData()
{
}


/////////////////////////////////////////////////////////////////////////////////
/// Das erste Argument übergibt den Umsatz.
/// Das zweite Argument gibt an ob die aufrufende Funktion die berechtigung hat in die
/// umsatz.data Datei zu schreiben auch wenn die Datei als letzten Eintrag das heutige Datum
/// gespeichert hat.
/// Der neue Umsatz wird dann am Ende der
/// der Datei mit dem heutigem bzw. mit dem gestrigen angehängt Datum angehängt.
/////////////////////////////////////////////////////////////////////////////////

void IO_WriteInMonthData::schreibeInUmsatz(double heuteigerUmsatz, int argument)
{
    QFile Umsatz(umsatz);
    if(!Umsatz.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Append ))
    {
        qDebug()<<"schreibeInUmsatz";
        return;
    }
    QTextStream out(&Umsatz);
    QList <double> vergleicheTag;
    int ivergleicheTag;

    vergleicheTag=leseUmsatzUndSpeichereRueckwertsInListe(1,1,umsatz);
    if(!vergleicheTag.isEmpty())
    {
        ivergleicheTag=vergleicheTag.last();
        if (argument==0)
        {
            if (ivergleicheTag!=dat.date.dayOfYear())
                out<<heuteigerUmsatz<<","<<dat.date.dayOfYear()<<"\n";
        }
        else
            {
                out<<heuteigerUmsatz<<","<<dat.date.dayOfYear()-1<<"\n";
            }
    }
    Umsatz.close();
}
