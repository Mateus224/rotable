#include "include/filecontainer/abstractfilecontainer.h"

AbstractFileContainer::AbstractFileContainer(QObject *parent) : QObject(parent)
{
    _fileDir= new QDir("/opt/rotable");

}
