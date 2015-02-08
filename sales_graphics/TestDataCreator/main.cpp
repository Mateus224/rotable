#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <stdlib.h>

#define umsatz "umsatz.daten"

int main(int argc, char *argv[])
{
    QFile dummyDaten (umsatz);
    if(!dummyDaten.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        qDebug()<<"konnte nicht geöffnet werden";
        return 0;
    }
    QTextStream in(&dummyDaten);

    int Tag=365;

    int iUmsatz;
    int iSecret[Tag];
    int Tage[Tag];
    for (int j=0;j<1;j++)
    {
        for(int i=1;i<=Tag;i++)
        {
            iSecret[i]= i+(j*365);//(rand() % 40 + 1)+10;
            Tage[i]=i;
            qDebug()<<iSecret[i];
            in<<iSecret[i]<<","<<Tage[i]<<"\n";
        }
    }
    return 0;
}
