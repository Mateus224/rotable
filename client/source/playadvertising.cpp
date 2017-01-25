#include "include/playadvertising.h"
#include "touchevent.h"

using namespace rotable;

PlayAdvertising::PlayAdvertising(AdvertisingVideo & advertisingVideo, TouchEvent &touch, QObject *parent)
    : QObject(parent)
{
    L_timers=new QList<Timers*>;
    L_timerQueue=new QList<Timers*>;
    _advertisingVideo= new AdvertisingVideo();
    _advertisingVideo=&advertisingVideo;
    _touch=&touch;
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
    int j=0;
    foreach(Timers* namesOfTimer, *L_timers)
    {
        if(namesOfTimer->_videoName==name)
        {
            int lat_touch=_touch->_secondsFromLastTouchPlus->secsTo(QTime::currentTime());
            int timeInSecTo=namesOfTimer->_timer->secsTo(QTime::currentTime());
            if(0<timeInSecTo);
            {
                QTimer::singleShot(timeInSecTo, [=]() { timerEnd(*L_timers->at(j)->_videoName); } );
            }
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

void PlayAdvertising::advertisingTimerQueue()
{

}
