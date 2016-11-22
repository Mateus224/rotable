#include "filecontainer/advertisingvideo.h"


using namespace rotable;

//------------------------------------------------------------------------------

AdvertisingVideo::AdvertisingVideo(QObject *parent):_advertisingInfo()
{

}

AdvertisingVideo::~AdvertisingVideo(){}

void AdvertisingVideo::addAdvertisingVideo()
{
}



//------------------------------------------------------------------------------

void AdvertisingVideo::addAdditionalData(QJsonObject &o) const
{
    o["a_id"]=_advertisingInfo._id;
    o["frequency"]=_advertisingInfo._frequency;
    o["media_id"]=_advertisingInfo._mediaId;
    o["play"]=_advertisingInfo._play;
    o["played"]=_advertisingInfo._played;
}

void AdvertisingVideo::setAdditionalData(QJsonObject &o)
{
    if(  o.contains("media_id")
       &&o.contains("frequency")
       &&o.contains("play")
       &&o.contains("played"))
    {
        _advertisingInfo._id=o["a_id"].toInt();
        _advertisingInfo._frequency=o["frequency"].toInt();
        _advertisingInfo._mediaId=o["media_id"].toInt();
        _advertisingInfo._play=o["play"].toBool();
        _advertisingInfo._played=o["played"].toInt();
    }
}

void AdvertisingVideo::updateData(AdvertisingVideo* file)
{
    _fileInfo._date=file->_fileInfo._date;
    _fileInfo._id=file->_fileInfo._id;
    _fileInfo._name=file->_fileInfo._name;
    _fileInfo._removed=file->_fileInfo._removed;
    _fileInfo._size=file->_fileInfo._size;
    _fileInfo._type=file->_fileInfo._type;
    _advertisingInfo._frequency=file->_advertisingInfo._frequency;
    _advertisingInfo._id=file->_advertisingInfo._id;
    _advertisingInfo._mediaId=_advertisingInfo._mediaId;
    _advertisingInfo._play=_advertisingInfo._play;
    _advertisingInfo._played=_advertisingInfo._played;
}
