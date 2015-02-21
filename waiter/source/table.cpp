#include <QDebug>
#include "../include/table.h"
#include <QObject>

table::table(QObject *parent) : QObject(parent)
{
}

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


//------------------------------------------------------------
void table::add_orderinformation()
{
    L_orderinformation.append(new OrderInformation("Table 1", "red", 3, "Sambuca", 2.5, true, true));
}

void table::cancellation_orderinformation(int position)
{
    OrderInformation* cancellationInformation;
    cancellationInformation=L_orderinformation.takeAt(position);
    cancellationInformation->setcancellation(true);
    L_orderinformation.insert(position,cancellationInformation);
}

void table::ready_orderinformation(int position)
{
    OrderInformation* readyInformation;
    readyInformation=L_orderinformation.takeAt(position);
    readyInformation->setready(true);
    L_orderinformation.insert(position,readyInformation);
}

