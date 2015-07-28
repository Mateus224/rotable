#include "tablelist.h"
#include <QList>

//-----------------------------------------------------

using rotable::TableList;
using rotable::Table;

//-----------------------------------------------------

TableList::~TableList(){
    //Clear memory
    qDeleteAll(begin(), end());
    clear();     //Clear list
}

//-----------------------------------------------------

QQmlListProperty<Table> TableList::tables()
{
    //We need QList with value of QMap
    QList<Table *> listOfValues(this->values());
    //Our class inherit from QMap, QMap inherit from QObject,
    //so we can cast our class to QObject
    return QQmlListProperty<Table>((QObject*)this, listOfValues);
}

//-----------------------------------------------------

TableList::TableList(): QMap(){

}

//-----------------------------------------------------
