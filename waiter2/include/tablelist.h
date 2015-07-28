#ifndef ROTABLE_TABLELIST_H
#define ROTABLE_TABLELIST_H

//-----------------------------------------------------

namespace rotable{
    class TableList;
}

//-----------------------------------------------------

#ifndef QMAP_H
#include <QMap>
#endif

#include "table.h"


//-----------------------------------------------------
//Class for store Tables and show list them in qml
class rotable::TableList: public QMap<int,rotable::Table*>{

    Q_PROPERTY(QQmlListProperty<Table> tables READ tables)

public:
    //-----------------------------------------------------
    // Constructor and Destructor
    //-----------------------------------------------------

    /**
     * Default constructor
     */
    TableList();

    /**
     * Default destructor
     */
    ~TableList();

    //-----------------------------------------------------
    // For QML
    //-----------------------------------------------------
    QQmlListProperty<Table> tables();

private:
}; // TableList

#endif // ROTABLE_TABLELIST_H

