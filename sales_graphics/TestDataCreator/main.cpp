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

    int Tag=356;

    int iUmsatz;
    int iSecret[Tag];
    int Tage[Tag];
    for (int i=0;i<4;i++)
    {
        for(int i=0;i<Tag;i++)
        {
            iSecret[i]= (rand() % 4000 + 1)+2000;
            Tage[i]=i;
            qDebug()<<iSecret[i];
            in<<iSecret[i]<<","<<Tage[i]<<"\n";
        }
    }
    return 0;
}
