#include "filecontainer/advertisingcontainer.h"


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

    /*which information can be changed from the gui*/
    connect(file, SIGNAL(playTimeChanged()), this, SLOT(onFileUpdated()));
    connect(file, SIGNAL(playChanged()), this, SLOT(onFileUpdated()));
    connect(file, SIGNAL(nameChanged()), this, SLOT(onFileUpdated()));

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

void rotable::AdvertisingContainer::onFileUpdated()
{
  rotable::AdvertisingVideo* advertisingVideo = static_cast<rotable::AdvertisingVideo*>(QObject::sender());
  emit advertisingVideoUpdated(advertisingVideo);
}

//------------------------------------------------------------------------------

void rotable::AdvertisingContainer::playTimeNextElement(int id)
{
    int SumOfplayTimes=0, nextId=0,test=0,j=0,size=0;
    bool flag=0;

    QHash<int,AdvertisingVideo*>::const_iterator i = _files->constBegin();
    while (i != _files->constEnd()) {
        tmpFile= i.value();
        test=tmpFile->getA_id();
        SumOfplayTimes+=tmpFile->getPlayTime();
        if(tmpFile->getA_id()==id){
            flag=true;
            size=_files->size();
            if((size-1)==j){
                i= _files->constBegin();
                tmpFile= i.value();
                nextId=tmpFile->getA_id();
                SumOfplayTimes-=tmpFile->getPlayTime();
                nextFile = _files->value(nextId);
            }
        }
        else if(flag==true){
            flag=false;
            nextId=tmpFile->getA_id();
            SumOfplayTimes-=tmpFile->getPlayTime();
            nextFile = _files->value(nextId);
        }
        ++i;
        ++j;
    }
    if(!calculatePercentNextElement_PlayTime(SumOfplayTimes))
        playTimeNextElement(nextId);
}

//------------------------------------------------------------------------------

bool rotable::AdvertisingContainer::calculatePercentNextElement_PlayTime(int SumOfplayTimes)
{
    if(SumOfplayTimes>=100){
        nextFile->setPlayTime(0);
        return false;
    }
    else if(SumOfplayTimes<100){
        SumOfplayTimes=100-SumOfplayTimes;
    }
    nextFile->setPlayTime(SumOfplayTimes);
    return true;
}
