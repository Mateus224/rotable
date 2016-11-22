#include "files/filecontainer.h"


rotable::FileContainer::FileContainer(QObject *parent) : QObject(parent),_test()
{
    _files=new QHash<int, File *>;
    connect(this, &FileContainer::fileAdded, this, &FileContainer::updateView);
    connect(this, &FileContainer::fileRemoved, this, &FileContainer::updateView);
    connect(this, &FileContainer::fileUpdated, this, &FileContainer::updateView);
}

rotable::FileContainer::~FileContainer()
{
    clear();
}


//------------------------------------------------------------------------------

void rotable::FileContainer::addFile(rotable::File *file)
{

    if(!file)
        return;

    int id=file->getId();
    if(_files->contains(id))
    {
        _files->values()[file->getId()]->updateData(file);
        emit fileUpdated();
    }
    else
    {
        _files->insert(id,file);
        //connect(file, &File::fileChanged, this, &FileContainer::fileUpdated);
        emit fileAdded(file);
    }
}

//------------------------------------------------------------------------------

QList<int> rotable::FileContainer::fileIds() const
{
    return _files->keys();
}

//------------------------------------------------------------------------------

int rotable::FileContainer::count() const
{
    return _files->count();
}

//------------------------------------------------------------------------------

rotable::File *rotable::FileContainer::file(int idx) const
{
    return _files->value(idx);
}

//------------------------------------------------------------------------------

void rotable::FileContainer::clear()
{
    qDeleteAll(_files->begin(), _files->end());
    _files->clear();
    emit updateView();
}

//------------------------------------------------------------------------------

void rotable::FileContainer::setSelectedFile(int idx)
{
  selectedFile = _files->values()[idx];
}

//------------------------------------------------------------------------------

rotable::File* rotable::FileContainer::getSelectedFile() const
{
    return selectedFile;
}

//------------------------------------------------------------------------------

void rotable::FileContainer::setSelectedFile(File *value)
{
    selectedFile = value;
}

//------------------------------------------------------------------------------
