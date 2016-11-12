#include "filecontainer/advertisingvideo.h"

AdvertisingVideo::AdvertisingVideo(QObject *parent) : QObject(parent)
{
    _mediaId=0;
    _frequency=30;
    _play=false;
    _played=0;

}
