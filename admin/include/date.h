#ifndef DATE_H
#define DATE_H
#include <QDate>
#include <QTime>

class Date:public QDate, public QTime
{
public:
    Date();
    int* day_month_date();
    int* DaysInMonthFrom0101ToNow();


     QDate date;
     QTime time;
};

#endif // DATE_H
