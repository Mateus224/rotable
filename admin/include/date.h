#ifndef DATE_H
#define DATE_H
#include <QDate>

class Date:public QDate
{
public:
    Date();
    int* DaysInMonthFrom0101ToNow();


     QDate date;
};

#endif // DATE_H
