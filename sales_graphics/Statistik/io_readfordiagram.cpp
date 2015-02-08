#include "io_readfordiagram.h"

IO_ReadForDiagram::IO_ReadForDiagram()
{
}

///////////////////////////////////////////////////////////////////////
///Diese Funktion liest die Umsätze der letzten Monate ein.
////////////////////////////////////////////////////////////////////////


double* IO_ReadForDiagram::leseAusUmsatzDiesesJahr()
{

    double* iaUmsatz= new double [12];
    int heutigerMonat=dat.date.month();
    QList<double> iListeMonatsumsaetze;
    QString ThisJahr= MonatsUmsatz;
    ThisJahr.prepend("_");
    ThisJahr.prepend(QString::number(dat.date.year()));
    iListeMonatsumsaetze=leseUmsatzUndSpeichereRueckwertsInListe(heutigerMonat,0,ThisJahr);
    if(!iListeMonatsumsaetze.isEmpty())
    {
        for (int i=0;i<heutigerMonat;i++)
            iaUmsatz[i]=iListeMonatsumsaetze.takeLast();
        for(int i=heutigerMonat; i<12;i++)
            iaUmsatz[i]=0;
    }
    return iaUmsatz;
}



double* IO_ReadForDiagram::leseAusUmsatzVorLetzenJahr()
{
    double* iaUmsatz= new double [12];
    QList<double> iListeMonatsumsaetze;
    QString LetzesJahr= MonatsUmsatz;
    LetzesJahr.prepend("_");
    LetzesJahr.prepend(QString::number(dat.date.year()-1));

    iListeMonatsumsaetze=leseUmsatzUndSpeichereRueckwertsInListe(12,0,LetzesJahr);
    if(!iListeMonatsumsaetze.isEmpty())
    {
        for (int i=0;i<12;i++)
        {
            iaUmsatz[i]=iListeMonatsumsaetze.takeLast();
        }
    }
    return iaUmsatz;
}



double* IO_ReadForDiagram::leseAusUmsatzVorVorLetzenJahr()
{
    double* iaUmsatz= new double [12];
    QList<double> iListeMonatsumsaetze;
    QString VorletzesJahr= MonatsUmsatz;
    VorletzesJahr.prepend("_");
    VorletzesJahr.prepend(QString::number(dat.date.year()-2));

    iListeMonatsumsaetze=leseUmsatzUndSpeichereRueckwertsInListe(12,0,VorletzesJahr);
    if(!iListeMonatsumsaetze.isEmpty())
    {
        for (int i=0;i<12;i++)
        {
            iaUmsatz[i]=iListeMonatsumsaetze.takeLast();
        }
    }
    return iaUmsatz;
}
