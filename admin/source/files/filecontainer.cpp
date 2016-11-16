#include "include/files/filecontainer.h"

FileContainer::FileContainer(QObject *parent) : QObject(parent)
{
    connect(this, &FileContainer::fileAdded, this, &FileContainer::updateView);
    connect(this, &FileContainer::fileRemoved, this, &FileContainer::updateView);
    connect(this, &FileContainer::fileUpdated, this, &FileContainer::updateView);
}

FileContainer::~FileContainer()
{
    clear();
}


//------------------------------------------------------------------------------

void FileContainer::addFile(rotable::File *file)
{
    if(!file)
        return;
    if(_files.contains(file->id()))
    {
        _files[file->id()]->updateData(file);
        emit fileUpdated();
    }
    else
    {
        _files[file->id()] = file;
        connect(file, &File::fileChanged, this, &FileContainter::fileUpdated);
        emit fileAdded(file);
    }
}

//------------------------------------------------------------------------------

QList<int> FileContainer::fileIds() const
{
    return _files.keys();
}

//------------------------------------------------------------------------------

int FileContainer::count() const
{
    return _files.count();
}

//------------------------------------------------------------------------------

rotable::File *FileContainer::file(int idx) const
{
    return _files[idx];
}

//------------------------------------------------------------------------------

void FileContainer::clear()
{
    qDeleteAll(_files.begin(), _files.end());
    _files.clear();
    emit updateView();
}

//------------------------------------------------------------------------------

void FileContainer::setSelectedFile(int idx)
{
  selectedFile = _files.values()[idx];
}

//------------------------------------------------------------------------------

rotable::File *FileContainer::getSelectedFile() const
{
    return selectedFile;
}

//------------------------------------------------------------------------------

void FileContainer::setSelectedFile(rotable::File *value)
{
    selectedFile = value;
}

//------------------------------------------------------------------------------
