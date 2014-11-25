#include "private/precomp.h"

#include "io_init.h"
#include "io_writeinmonthwithnewdata.h"
#define MonatsUmsatz "umsatz.daten"
#define umsatz "umsatz.daten"


IO_init::IO_init()
{
}



///////////////////////////////////////////////////////////////////////
///untersucheAufLueckenUndFuelleAuf()
///die umsatz.daten Datei wird ReadOnly geöffnet und die Daten werden in eine
///Liste <String> abgespeichert. Der letzte Eintrag wird dann untersucht dabei
///wird der Umsatz vom Datum gesplittet und mit dem letzten Eintrag wird geprüft
///wannn wieviele tage er her ist. Ist dies mehr als 2 Tage her, wird die Funktion
///schreibeInUmsatz(0) aufgerufen dabei wird als Argument die 0 übergeben.
////////////////////////////////////////////////////////////////////////


void IO_init::untersucheAufLueckenUndFuelleAuf()
{
    IO_WriteInMonthData test2;
    QList <double> vergleicheTag;
    int ivergleicheTag;
    //oeffneUmsatz();
    vergleicheTag=leseUmsatzUndSpeichereRueckwertsInListe(1,1,umsatz);
    qDebug()<<vergleicheTag<<"  empty??";
    if(!vergleicheTag.isEmpty())
    {
        ivergleicheTag=vergleicheTag.last();
        qDebug()<<ivergleicheTag<<"  DIFFERENZ";
        int dayOfYear= dat.date.dayOfYear();
        if(ivergleicheTag==dayOfYear)
        {

        }
        else
        {
            int differenz;
            differenz=dayOfYear-ivergleicheTag;
            qDebug()<<differenz<<"  DIFFERENZ";
            for( int i=0; i < differenz-1; i++)
            {
                qDebug()<<differenz<<"  DIFFERENZ";
                test2.schreibeInUmsatz(20,1);
            }
        }

    }
}






///////////////////////////////////////////////////////////////////////
///schreibeMonatsUmsatz();
///Diese Funktion schreibt in die Datei MonatsUmsatz.daten die Umsätze
///der letzten Monate.
////////////////////////////////////////////////////////////////////////


void IO_init::schreibeMonatsUmsatz()
{

    //hier wird erst read ausgeführt und geschaut ob der heutige Tag mit dem letzten
    //eintrag übereinstimmt wenn ja, return, da jeder Tag nur einmal in der Datei
    //gespeichert werden soll
    QString SletzterTag;
    QList<double> letzterTag=leseUmsatzUndSpeichereRueckwertsInListe(1,1,MonatsUmsatz);
    if(!letzterTag.isEmpty())
    {
        SletzterTag=letzterTag.last();
        if (dat.date.dayOfYear()==SletzterTag.toInt())
        {
            return;
        }
    }
    int heutigerMonat=dat.date.month();
    double SummeDerUmsaetzeDesMonats=0;
    int DaysInMonth= dat.date.daysInMonth();
    int dayOfYear=dat.date.dayOfYear();

    //Hier erhalten wir eine Liste mit den täglichen Umsatzen bis zum Jahresbegin
    QList<double> ListeMitUmsaetzenDiesesJahres;
    ListeMitUmsaetzenDiesesJahres=leseUmsatzUndSpeichereRueckwertsInListe(dayOfYear,0,umsatz);


    //Öffne zum Schreiben in die Datei MonatsUmsatz
    QString ThisJahr= MonatsUmsatz;
    ThisJahr.prepend("_");
    ThisJahr.prepend(QString::number(dat.date.year()));
    QFile SchreibeInMonatsUmsatz(ThisJahr);
    QTextStream MonthOutput(&SchreibeInMonatsUmsatz);
    if(!SchreibeInMonatsUmsatz.open(QIODevice::ReadWrite | QIODevice::Text ))
    {
        return;
    }

    int* TageProMonatBisHeute;
    TageProMonatBisHeute=dat.DaysInMonthFrom0101ToNow();
    qDebug()<<TageProMonatBisHeute[0]<<TageProMonatBisHeute[1]<<TageProMonatBisHeute[2]<<TageProMonatBisHeute[3]<<TageProMonatBisHeute[4]<<"hier";
    //der Pointer "TageProMonatBisHeute" zeigt auf eine array das mit der Anzahl der vergangenen Tage im Monat speichert
    // nun gehen wir die Monate bis zum heutigem Monat durch
    int k=0;
    for( int j=0; j<dat.date.month(); j++)
    {
        SummeDerUmsaetzeDesMonats=0; //reseten des ints
        int TageImMonat=TageProMonatBisHeute[j];

        for(int i=0; i<TageImMonat; i++)
        {
            if(!ListeMitUmsaetzenDiesesJahres.isEmpty())
            {
                SummeDerUmsaetzeDesMonats=SummeDerUmsaetzeDesMonats+ListeMitUmsaetzenDiesesJahres[k];
                //qDebug()<<SummeDerUmsaetzeDesMonats;
                k++;
            }
        }
        //qDebug()<<SummeDerUmsaetzeDesMonats;
        MonthOutput<<SummeDerUmsaetzeDesMonats<<","<<dat.date.dayOfYear()<<"\n";
    }

    SchreibeInMonatsUmsatz.close();
}




//////////////////////////////////////////////////////////////////////
///Diese Datei legt eine neue Datei mit den alten umsätzen des vorherigen
///Jahres an. Zunächst wird überprüft ob der heutige Tag kleiner ist als der
///vorherige--> Jahresbeginn
///wenn ja wird eine Datei angelegt mit den Umsätzen des letzten Monats
//////////////////////////////////////////////////////////////////////

void IO_init::JahrVollLegeNeueDateiAn()
{
    Date lastYear;

    QList<double> letzteerTag=leseUmsatzUndSpeichereRueckwertsInListe(1,1,umsatz);
    if(!letzteerTag.isEmpty())
    {
        int iletzterTag=letzteerTag.last();
        qDebug()<<iletzterTag<<"<"<<dat.date.dayOfYear();
        if(dat.date.dayOfYear()<iletzterTag)
        {
            qDebug()<<"JahrVollLegeNeueDateiAn";
            QString newYear=umsatz;
            int iThisYear=dat.date.year()-1;
            QString sThisYear=QString::number(iThisYear);
            sThisYear.append("_");
            newYear.prepend(sThisYear);
            QFile UmsatzLastYear(newYear);

            if(!UmsatzLastYear.open(QIODevice::WriteOnly | QIODevice::Text ))
            {
                qDebug()<<"JahrVollLegeNeueDateiAn";
                return;
            }

            QTextStream in(&UmsatzLastYear);
            QList <double> Umsaetze=leseUmsatzUndSpeichereRueckwertsInListe(720,0,umsatz);
            QDate lastYear;
            lastYear= dat.date.addYears (-1);
            int ilastYear=lastYear.year();
            QDate QlastYear(ilastYear,12,1);
            int SummeMonat;

            for(int i=0; i<dat.date.dayOfYear();i++)
            {
                if(!Umsaetze.isEmpty())
                    Umsaetze.takeFirst();
            }

            for(int i=12; i>0;i--)
            {
                SummeMonat=0;
                QDate QlastYear(ilastYear,i,1);
                int idaysInMonth = QlastYear.daysInMonth();
                for (int i=0;i<idaysInMonth;i++)
                {
                    if(!Umsaetze.isEmpty())
                    {
                        SummeMonat=SummeMonat+Umsaetze.takeFirst();
                    }

                }
                in<<SummeMonat<<","<<dat.date.dayOfYear()<<"\n";
            }
            UmsatzLastYear.close();
        }
    }

    return;

}
