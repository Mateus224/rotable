#include "filecontainer/advertisingvideo.h"


using namespace rotable;

//------------------------------------------------------------------------------

AdvertisingVideo::AdvertisingVideo(QObject *parent)
{

}

AdvertisingVideo::~AdvertisingVideo(){}

void AdvertisingVideo::addAdvertisingVideo()
{
}



//------------------------------------------------------------------------------

void AdvertisingVideo::addAdditionalData(QJsonObject &o) const
{
    o["id"]=_advertisingInfo._id;
    o["frequency"]=_advertisingInfo._frequency;
    o["media_id"]=_advertisingInfo._mediaId;
    o["play"]=_advertisingInfo._play;
    o["played"]=_advertisingInfo._played;
}

void AdvertisingVideo::setAdditionalData(QJsonObject &o)
{
    if(o.contains("id")
       &&o.contains("media_id")
       &&o.contains("frequency")
       &&o.contains("play")
       &&o.contains("played"))
    {
        _advertisingInfo._id=o["id"].toInt();
        _advertisingInfo._frequency=o["frequency"].toInt();
        _advertisingInfo._mediaId=o["media_id"].toInt();
        _advertisingInfo._play=o["play"].toBool();
        _advertisingInfo._played=o["played"].toInt();
    }
}
