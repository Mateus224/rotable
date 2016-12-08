#include "files/advertisingcontainer.h"


rotable::AdvertisingContainer::AdvertisingContainer(QObject *parent) : QObject(parent)
{
    _files=new QHash<int, AdvertisingVideo *>;
    connect(this, &AdvertisingContainer::fileAdded, this, &AdvertisingContainer::updateView);
    connect(this, &AdvertisingContainer::fileRemoved, this, &AdvertisingContainer::updateView);
    connect(this, &AdvertisingContainer::fileUpdated, this, &AdvertisingContainer::updateView);
}

rotable::AdvertisingContainer::~AdvertisingContainer()
{
    clear();
    delete _files;
}


//------------------------------------------------------------------------------

void rotable::AdvertisingContainer::addFile(rotable::AdvertisingVideo *file)
{

    if(!file)
        return;

    int id=file->getId();
    if(_files->contains(id))
    {
        _files->value(file->getId())->updateData(file);
        emit fileUpdated();
    }
    else
    {
        _files->insert(id,file);
        //connect(file, &File::fileChanged, this, &AdvertisingContainer::fileUpdated);
        emit fileAdded(file);
    }
}

//------------------------------------------------------------------------------

QList<int> rotable::AdvertisingContainer::fileIds() const
{
    return _files->keys();
}

//------------------------------------------------------------------------------

int rotable::AdvertisingContainer::count() const
{
    return _files->count();
}

//------------------------------------------------------------------------------

rotable::AdvertisingVideo *rotable::AdvertisingContainer::file(int idx) const
{
    return _files->value(idx);
}

//------------------------------------------------------------------------------

void rotable::AdvertisingContainer::clear()
{
    qDeleteAll(_files->begin(), _files->end());
    _files->clear();
    emit updateView();
}

//------------------------------------------------------------------------------

void rotable::AdvertisingContainer::setSelectedFile(int idx)
{
  selectedFile = _files->value(idx);
}

//------------------------------------------------------------------------------

rotable::AdvertisingVideo* rotable::AdvertisingContainer::getSelectedFile() const
{
    return selectedFile;
}

//------------------------------------------------------------------------------

void rotable::AdvertisingContainer::setSelectedFile(AdvertisingVideo *value)
{
    selectedFile = value;
}

//------------------------------------------------------------------------------
