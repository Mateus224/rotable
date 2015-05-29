#include "date.h"
#include <QDebug>
#include <QDateTime>


Date::Date()
{
    date=date.currentDate();
    time=time.currentTime();
    //qDebug()<<date<<"   "<<time;
}


int* Date::day_month_date()
{
    int iday_month_date [2];
    iday_month_date[0]= date.day();
    iday_month_date[1]=date.month();
    return iday_month_date;
}


/////////////////////////////////////////////////////////////
/// \brief Date::DaysInAllMonth
/// Diese Funktion geht von jetzigem Monat rückwerts bis zum
/// beginn des Ersten Monats durch die Schleife und füllt diese
/// mit der Anzahl der Tage der Monate bis zu jetzigen Zeitpunkt.
/// die Monate durch und speichert die Tage der Monate in einem Array
/// bis zu jetzigem Tag.
//////////////////////////////////////////////////////////////

int* Date::DaysInMonthFrom0101ToNow()
{
    Date Date;
    Date.currentDate();
    QDate qaDaysInMonth[12];
    int* iaDaysInMonth=new int [12];
    int Monat=Date.date.month();
    for(int i=Monat-1;i>=0;i--)
    {
        qaDaysInMonth[i]=Date.date.addMonths(i-Monat+1);
        if(i==Monat-1)
        {
            iaDaysInMonth[i]=qaDaysInMonth[i].day();
        }
        else
        {
            iaDaysInMonth[i]=qaDaysInMonth[i].daysInMonth();
         }
    }
    for(int i=Monat;i<12;i++)
    {
        iaDaysInMonth[i]=0;
    }
    return iaDaysInMonth;
}


