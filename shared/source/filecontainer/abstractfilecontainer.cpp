#include "include/filecontainer/abstractfilecontainer.h"

AbstractFileContainer::AbstractFileContainer(QObject *parent) : QObject(parent)
{
    QString path="/opt/rotable";
    _fileDir = new QDir(path);
    if(!_fileDir->exists())
    {
        _fileDir->mkpath(path);
    }


}
