#include <QDebug>
#include "../include/table.h"


/*table::table(QObject *parent) : QObject(parent)
{
}*/

table::table(const int &tableNumber, QObject *parent) : QObject(parent), m_tableNumber(tableNumber)
{
}


//------------------------------------------------------------
int table::tableNumber() const
{
    return m_tableNumber;
}

void table::settableNumber(const int &tableNumber)
{
    if (tableNumber != m_tableNumber) {
        m_tableNumber = tableNumber;
        emit tableNumberChanged();
    }
}

