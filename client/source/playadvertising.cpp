#include "include/playadvertising.h"

using namespace rotable;

PlayAdvertising::PlayAdvertising(AdvertisingVideo & advertisingVideo,QObject *parent)
    : QObject(parent)
{
    _advertisingVideo= new AdvertisingVideo();
    _advertisingVideo=&advertisingVideo;
    //connect(timer, SIGNAL(timerStart()), this, SLOT(timerEnd(video_name)));
}

void PlayAdvertising::startPlayAdvertising()
{
    QMap<QString, AdvertisingVideo::advertisingInfo >::const_iterator i = _advertisingVideo->advertisingContainer.begin();
    while (i != _advertisingVideo->advertisingContainer.constEnd()) {
        QString video_name = i.key();
         QTimer::singleShot(10000, [=]() { timerEnd(video_name); } );
         //i.value()._frequency
        ++i;
    }
}


void PlayAdvertising::timerEnd(QString name)
{
    qDebug()<<"halle";
}
