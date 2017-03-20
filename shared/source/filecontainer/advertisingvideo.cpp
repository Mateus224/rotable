#include "filecontainer/advertisingvideo.h"


using namespace rotable;

//------------------------------------------------------------------------------

AdvertisingVideo::AdvertisingVideo(QObject *parent):File(parent), _advertisingInfo()
{

}

AdvertisingVideo::~AdvertisingVideo(){}
//------------------------------------------------------------------------------

void AdvertisingVideo::setA_id(const int& id)
{
  if (_fileInfo._id != id) {
    _fileInfo._id = id;
    emit idChanged();
  }
}

void AdvertisingVideo::setPlayTime(const int& playTime)
{
  if (_advertisingInfo._playTime != playTime) {
    _advertisingInfo._playTime = playTime;
    emit playTimeChanged();
  }
}

void AdvertisingVideo::setMedia_id(const int& mediaId)
{
  if (_advertisingInfo._mediaId != mediaId) {
    _advertisingInfo._mediaId = mediaId;
    emit mediaIdChanged();
  }
}

void AdvertisingVideo::setPlay(const bool& play)
{
  if (_advertisingInfo._play != play) {
    _advertisingInfo._play = play;
    emit playChanged();
  }
}

void AdvertisingVideo::setPlayed(const int& played)
{
  if (_advertisingInfo._played != played) {
    _advertisingInfo._played = played;
    emit playedChanged();
  }
}

void AdvertisingVideo::setDuration(const int& duration)
{
  if (_advertisingInfo._duration!= duration) {
    _advertisingInfo._duration = duration;
    emit durationChanged();
  }
}

//------------------------------------------------------------------------------

void AdvertisingVideo::addAdditionalData(QJsonObject &o) const
{
    o["a_id"]=_advertisingInfo._id;
    o["playTime"]=_advertisingInfo._playTime;
    o["media_id"]=_advertisingInfo._mediaId;
    o["play"]=_advertisingInfo._play;
    o["played"]=_advertisingInfo._played;
    o["duration"]=_advertisingInfo._duration;
}

void AdvertisingVideo::setAdditionalData(QJsonObject &o)
{
    if(  o.contains("media_id")
       &&o.contains("playTime")
       &&o.contains("play")
       &&o.contains("played")
       &&o.contains("duration"))
    {
        _advertisingInfo._id=o["a_id"].toInt();
        _advertisingInfo._playTime=o["playTime"].toInt();
        _advertisingInfo._mediaId=o["media_id"].toInt();
        _advertisingInfo._play=o["play"].toBool();
        _advertisingInfo._played=o["played"].toInt();
        _advertisingInfo._duration=o["duration"].toInt();
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
    _advertisingInfo._playTime=file->_advertisingInfo._playTime;
    _advertisingInfo._id=file->_advertisingInfo._id;
    _advertisingInfo._mediaId=_advertisingInfo._mediaId;
    _advertisingInfo._play=_advertisingInfo._play;
    _advertisingInfo._played=_advertisingInfo._played;
    _advertisingInfo._duration=_advertisingInfo._duration;
}

