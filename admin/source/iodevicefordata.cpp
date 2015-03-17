#include "iodevicefordata.h"

IODeviceForData::IODeviceForData()
{
}


///////////////////////////////////////////////////////////////////////
/// \brief Umsatz::leseUmsatzUndSpeichereRueckwertsInListe
/// \param Tage
/// \param argument
/// Diese Funktion öffnet die Datei umsatz.daten als nächstes löscht sie
/// die Liste mit den lines und füllt sie erneut mit den Daten der in Umsatz.daten
/// gespeicherten Inhalte. Als Argument übergeben wir wieviele Tage eingelesen
/// werden sollen und ob der erste Inhalt (der Umsatz) oder der zweit (der tag)
/// in einer Liste zurückgegeben werden sollen
///
//////////////////////////////////////////////////////////////////////////

QList<double> IODeviceForData::leseUmsatzUndSpeichereRueckwertsInListe(int Tage, int argument, QString Dateipfad)
{
    QFile leseAusUmsatz(Dateipfad);


    if (!leseAusUmsatz.open(QIODevice::ReadWrite| QIODevice::Text))
    {

        qDebug()<<"leseUmsatzUndSpeichereRueckwertsInListe";
        exit;
    }

    QTextStream in(&leseAusUmsatz);

    QString line = in.readLine();

    lines.clear();

    while (!line.isNull()) {
        lines << line;
        line = in.readLine();
    }
    QList <double> ListeMitUmsaetzenDiesesJahres;
    QStringList list;
    for (int i=0; i<Tage;i++)
    {

        if(!lines.isEmpty())
        {
            QString sUmsatzEintrag=lines.takeLast();
            list = sUmsatzEintrag.split(",");
            if(argument==0)
            {
                sUmsatzEintrag=list.first();
                double iUmsatzEintrag=sUmsatzEintrag.toDouble();
                ListeMitUmsaetzenDiesesJahres<<iUmsatzEintrag;
            }
            else if(argument==1)
            {
                sUmsatzEintrag=list.at(1);
                double iUmsatzEintrag=sUmsatzEintrag.toDouble();
                ListeMitUmsaetzenDiesesJahres<<iUmsatzEintrag;
            }
            else if(argument==2)
            {
                sUmsatzEintrag=list.last();
                double iUmsatzEintrag=sUmsatzEintrag.toDouble();
                ListeMitUmsaetzenDiesesJahres<<iUmsatzEintrag;
            }
        }
    }
    leseAusUmsatz.close();
    return ListeMitUmsaetzenDiesesJahres;
}
