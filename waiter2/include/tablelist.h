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
#include <QObject>


//-----------------------------------------------------
//Class for store Tables and show list them in qml
class rotable::TableList: public QMap<int,rotable::Table*>{

    Q_PROPERTY(QQmlListProperty<Table> tables READ tables)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

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

Q_DECLARE_METATYPE(rotable::TableList)

#endif // ROTABLE_TABLELIST_H

