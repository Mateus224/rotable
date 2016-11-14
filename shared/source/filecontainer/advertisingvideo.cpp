#include "filecontainer/advertisingvideo.h"

AdvertisingVideo::AdvertisingVideo(QObject *parent)
{

}

AdvertisingVideo::~AdvertisingVideo(){}

void AdvertisingVideo::addAdvertisingVideo()
{
}

QJsonValue AdvertisingVideo::toJSON()
{
    QJsonObject o;

    o["id"]=_advertisingInfo._id;
    o["frequency"]=_advertisingInfo._frequency;
    o["media_id"]=_advertisingInfo._mediaId;
    o["play"]=_advertisingInfo._play;
    o["played"]=_advertisingInfo._played;
    o["date"]=_fileInfo._date;
    o["name"]=_fileInfo._name;
    o["removed"]=_fileInfo._removed;
    o["size"]=_fileInfo._size;

    return QJsonValue(o);
}

AdvertisingVideo* AdvertisingVideo::fromJSON(const QJsonValue &jval)
{
    QJsonObject o=jval.toObject();

    if(o.contains("id")
        &&o.contains("name")
        &&o.contains("date")
        &&o.contains("size")
        &&o.contains("media_id")
        &&o.contains("frequency")
        &&o.contains("play")
        &&o.contains("played")
        &&o.contains("removed")
        )
    {
        AdvertisingVideo* a =new AdvertisingVideo();
        a->_advertisingInfo._id=o["id"];
        a->_advertisingInfo._frequency=o["frequency"];
        a->_advertisingInfo._mediaId=o["media_id"];
        a->_advertisingInfo._play=o["play"];
        a->_advertisingInfo._played=o["played"];
        a->_fileInfo._date=o["date"];
        a->_fileInfo._name=o["name"];
        a->_fileInfo._removed=o["removed"];
        a->_fileInfo._size=o["size"];
        return a;
    }
    return 0;
}
