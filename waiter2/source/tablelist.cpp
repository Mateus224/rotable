#include "tablelist.h"

//-----------------------------------------------------

using rotable::TableList;

//-----------------------------------------------------

TableList::~TableList(){
    //Clear memory
    qDeleteAll(begin(), end());
    clear();     //Clear list
}

//-----------------------------------------------------

TableList::TableList(): QMap(){

}

//-----------------------------------------------------
