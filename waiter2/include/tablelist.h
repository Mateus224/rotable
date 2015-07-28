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

public:
    TableList();
private:
}; // TableList

#endif // ROTABLE_TABLELIST_H

