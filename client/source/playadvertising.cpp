#include "include/playadvertising.h"

using namespace rotable;

PlayAdvertising::PlayAdvertising(AdvertisingVideo & advertisingVideo,QObject *parent)
    : QObject(parent)
{
    _time=new QTimer();
    _timeAfterShot=new QTime();
    _advertisingVideo= new AdvertisingVideo();
    _advertisingVideo=&advertisingVideo;
    //connect(timer, SIGNAL(timerStart()), this, SLOT(timerEnd(video_name)));
}

void PlayAdvertising::startPlayAdvertising()
{
    QMap<QString, AdvertisingVideo::advertisingInfo >::const_iterator i = _advertisingVideo->advertisingContainer.begin();
    _time->currentTime();
    while (i != _advertisingVideo->advertisingContainer.constEnd()) {
        QString video_name = i.key();
        int frequencyMinutes=i.value()._frequency*1000;
         QTimer::singleShot(frequencyMinutes, [=]() { timerEnd(video_name); } );
         //i.value()._frequency
        ++i;
    }
}


void PlayAdvertising::timerEnd(QString name)
{
    if(_time)
    qDebug()<<name;

}
