#include "include/playadvertising.h"

using namespace rotable;

PlayAdvertising::PlayAdvertising(AdvertisingVideo & advertisingVideo,QObject *parent)
    : QObject(parent)
{
    L_timers=new QList<Timers*>;
    _advertisingVideo= new AdvertisingVideo();
    _advertisingVideo=&advertisingVideo;
    //connect(timer, SIGNAL(timerStart()), this, SLOT(timerEnd(video_name)));
}

void PlayAdvertising::startPlayAdvertising()
{
    int j=0;
    QMap<QString*, AdvertisingVideo::advertisingInfo >::const_iterator i = _advertisingVideo->advertisingContainer.begin();
    while (i != _advertisingVideo->advertisingContainer.constEnd()) {
        st_timer=new Timers();
        st_timer->_timer=new QTime();
        st_timer->_videoName= new QString();
        st_timer->_videoName=i.key();
        L_timers->append(st_timer);
        timer(90,*st_timer->_timer);
        int frequencyMinutes=i.value()._frequency*1000;
        QTimer::singleShot(frequencyMinutes, [=]() { timerEnd(*L_timers->at(j)->_videoName); } );
        ++i; //iterator
        j++; //normal int for list
    }
}


void PlayAdvertising::timerEnd(QString& name)
{
    int i=0;
    foreach(Timers* namesOfTimer, *L_timers)
    {
        if(namesOfTimer->_videoName==name)
        {
            if(0<namesOfTimer->_timer->secsTo(QTime::currentTime()));
            qDebug()<<QTime::currentTime().secsTo(*namesOfTimer->_timer);

            qDebug()<<"name"<<name<<"zeit:"<<*namesOfTimer->_timer<<"jetzt ist:"<<QTime::currentTime();
        }
        i++;
    }
    //play();
    //timer(90,*st_timer->_timer);
}


void PlayAdvertising::timer(int sec, QTime& timer)
{
    timer=timer.currentTime();
    timer=timer.addSecs(sec);
}
