#include "files/filecontainer.h"


using namespace rotable;

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

void FileContainer::addFile(File *file)
{
    if(!file)
        return;

    int id=file->getId();
    if(_files.empty())
    {
    if(_files.contains(id))
    {
        _files[file->getId()]->updateData(file);
        emit fileUpdated();
    }
    }
    else
    {
        _files[id] = file;
        connect(file, &File::fileChanged, this, &FileContainer::fileUpdated);
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

File *FileContainer::file(int idx) const
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

File *FileContainer::getSelectedFile() const
{
    return selectedFile;
}

//------------------------------------------------------------------------------

void FileContainer::setSelectedFile(File *value)
{
    selectedFile = value;
}

//------------------------------------------------------------------------------
