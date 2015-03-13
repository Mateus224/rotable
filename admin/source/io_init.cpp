#include "io_init.h"
#include "io_writeinmonthwithnewdata.h"
#define umsatz "umsatz.data"



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
    QList <double> vergleicheTag;
    int ivergleicheTag;
    int dayOfYear= dat.date.dayOfYear();
    vergleicheTag=leseUmsatzUndSpeichereRueckwertsInListe(1,1,umsatz);
    if(!vergleicheTag.isEmpty())
    {
        ivergleicheTag=vergleicheTag.last();

        if(ivergleicheTag==dayOfYear)
        {
            return;
        }
        else
        {
            int differenz;
            differenz=dayOfYear-ivergleicheTag;
            if(differenz<0)
            {
                for(int i=0; i<dayOfYear-1;i++)
                {
                    IO_WriteInMonthData newYear;
                    newYear.schreibeInUmsatz(0,i+1,umsatz);
                }
            }
            else
            {
                for(int i=0; i < differenz-1; i++)
                {
                    IO_WriteInMonthData diff;
                    diff.schreibeInUmsatz(0,ivergleicheTag+1+i,umsatz);
                }
            }

        }
    }
    else //if Qlist is Empty or the file umsatz.data not exists
    {
        if(dayOfYear==1) //the first day of the Year no gaps to fill
        {
            return;
        }
        else
        {
            int differenz;
            differenz=dayOfYear;
            for(int i=0; i< differenz-1;i++)
            {
                IO_WriteInMonthData first_initialisation;
                first_initialisation.schreibeInUmsatz(0,i+1,umsatz);
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
    //eintrag übereinstimmt wenn ja return da jeder Tag nur einmal in der Datei
    //gespeichert werden soll
    QString SletzterTag;
    QList<double> letzterTag=leseUmsatzUndSpeichereRueckwertsInListe(1,1,umsatz);
    if(!letzterTag.isEmpty())
    {
        SletzterTag=letzterTag.last();
        if (dat.date.dayOfYear()==SletzterTag.toInt())
        {
            return;
        }
    }
    double SummeDerUmsaetzeDesMonats=0;
    int dayOfYear=dat.date.dayOfYear();

    //Hier erhalten wir eine Liste mit den täglichen Umsatzen bis zum Jahresbegin
    QList<double> ListeMitUmsaetzenRueckwertsDiesesJahres;
    QList<double> ListeMitUmsaetzenDiesesJahres;
    ListeMitUmsaetzenRueckwertsDiesesJahres=leseUmsatzUndSpeichereRueckwertsInListe(dayOfYear,0,umsatz);
    //we have to change the order of the List:

    for(int i=0;i<dayOfYear;i++)
    {

        double new_last;
        new_last=ListeMitUmsaetzenRueckwertsDiesesJahres.takeLast();
        ListeMitUmsaetzenDiesesJahres.append(new_last);

    }
    //Öffne zum Schreiben in die Datei umsatz
    QString ThisJahr= umsatz;
    ThisJahr.prepend("_");
    ThisJahr.prepend(QString::number(dat.date.year()));
    QFile SchreibeInMonatsUmsatz(ThisJahr);
    QTextStream MonthOutput(&SchreibeInMonatsUmsatz);
    if(!SchreibeInMonatsUmsatz.open(QIODevice::ReadWrite | QIODevice::Text ))
    {
        return;
    }

     //der Pointer "TageProMonatBisHeute" zeigt auf eine array das mit der Anzahl der vergangenen Tage im Monat speichert
    int* TageProMonatBisHeute;
    TageProMonatBisHeute=dat.DaysInMonthFrom0101ToNow();

    int vergangene_tage_der_letzten_Monate=0;
    // nun gehen wir die Monate bis zum heutigem Monat durch
    //

    for( int j=0; j<dat.date.month(); j++)
    {
        //vergangene_tage_der_letzten_Monate soll den die Tage der letzten monate ausrechenen
        //(ausser den jetzigen (letzten Monat)--> unvollständigen Monat)-->TageProMonatBisHeute[j-1]
        //da wir erst nachdem der erste Monat (Januar vorüber ist die 31 Tage aufaddieren wollen muss j>0 sein
        //Bei jedem Durchlauf der for-Schleife weden die vergangene_tage_der_letzten_Monate aufaddiert.
        if(j>0)
        {
            vergangene_tage_der_letzten_Monate=vergangene_tage_der_letzten_Monate+TageProMonatBisHeute[j-1];
        }
        SummeDerUmsaetzeDesMonats=0; //reseten des Umsatzes für jeden Monat
        int TageImMonat=TageProMonatBisHeute[j];

        for(int i=0; i<TageImMonat; i++)
        {

            if(!ListeMitUmsaetzenDiesesJahres.isEmpty())
            {

                SummeDerUmsaetzeDesMonats=SummeDerUmsaetzeDesMonats+ListeMitUmsaetzenDiesesJahres[vergangene_tage_der_letzten_Monate+i];
            }
        }
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
        if(dat.date.dayOfYear()<iletzterTag)
        {
            IO_WriteInMonthData fill_last_year;
            //FILL last year with turnover "0"
            for(int i=iletzterTag; i<dat.date.daysInYear(); i++)
            {
                fill_last_year.schreibeInUmsatz(0,i+1,umsatz);
            }
            untersucheAufLueckenUndFuelleAuf(); //Last year is filled now fill this year to todays date

            QString newYear=umsatz;
            int iThisYear=dat.date.year()-1;
            QString sLastYear=QString::number(iThisYear);
            sLastYear.append("_");
            newYear.prepend(sLastYear);
            QFile UmsatzLastYear(newYear);

            if(!UmsatzLastYear.open(QIODevice::WriteOnly | QIODevice::Text ))
            {
                qDebug()<<"io_init__ERR";
                return;
            }
            QTextStream in(&UmsatzLastYear);
            QList <double> Umsaetze=leseUmsatzUndSpeichereRueckwertsInListe(732,0,umsatz);
            QDate lastYear;
            lastYear= dat.date.addYears (-1);
            int ilastYear=lastYear.year();
            int SummeMonat;

            //remove in the Qlist the days of this Year-1 because todays turnover is not written
            for(int i=0; i<dat.date.dayOfYear()-1;i++)
            {
                if(!Umsaetze.isEmpty())
                    Umsaetze.takeFirst();
            }
            for(int i=1; i<=12;i++)
            {
                SummeMonat=0;
                QDate QlastYear(ilastYear,i,1);
                int idaysInMonth = QlastYear.daysInMonth();
                for (int i=0;i<idaysInMonth;i++)
                {
                    if(!Umsaetze.isEmpty())
                    {
                        SummeMonat=SummeMonat+Umsaetze.takeLast();
                    }
                }
                in<<SummeMonat<<","<<dat.date.dayOfYear()<<"\n";
            }
            UmsatzLastYear.close();
        }
    }
    return;
}
