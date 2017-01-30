#include "include/playadvertising.h"
#include "touchevent.h"

using namespace rotable;

PlayAdvertising::PlayAdvertising(AdvertisingVideo & advertisingVideo, TouchEvent &touch, QObject *parent)
    : QObject(parent)
{
    //L_timers=new QList<AdvertisingTimers*>;
    //L_timerQueue=new QList<AdvertisingTimers*>;
    //_advertisingVideo= new AdvertisingVideo();
    _advertisingVideo=&advertisingVideo;
    _touch=&touch;
}

void PlayAdvertising::startPlayAdvertising()
{
    int j=0;
    QMap<QString*, AdvertisingVideo::advertisingInfo >::const_iterator i = _advertisingVideo->advertisingContainer.begin();
    while (i != _advertisingVideo->advertisingContainer.constEnd()) {
        st_timer=new AdvertisingTimers();
        st_timer->_timer=new QTime();
        //st_timer->_lastPlay=new QTime();
        //st_timer->_videoName= new QString();
        st_timer->_videoName=i.key();
        st_timer->_id=i.value()._id;
        st_timer->_frequency=i.value()._frequency*1000;
        L_timers.append(st_timer);
        timer(90,*st_timer->_timer);
        QTimer::singleShot(st_timer->_frequency, [=]() { timerEnd(L_timers.at(j)->_id); } );
        ++i; //iterator
        j++; //normal int for list
    }
}


void PlayAdvertising::timerEnd(int& id)
{
    int nextPlay;
    if(_touch->_secondsFromLastTouchPlus->secsTo(QTime::currentTime())<0)//true if Touchscreen wasn't touched in the last 45 sec
    {
        nextPlay=MinBreakTime();
        if(nextPlay<=0){
            if(L_timerQueue.empty()){
                if(_playing==false){
                    _playing=true;
                    for(AdvertisingTimers* namesOfTimer: L_timers) {
                        if(namesOfTimer->_id==id){
                            emit play(namesOfTimer->_videoName);
                        }
                    }
                }
                else
                    advertisingTimerQueue(id);
            }
            else
                advertisingTimerQueue(id);
        }
        else
            advertisingTimerQueue(id);
    }
    else
        advertisingTimerQueue(id);
}


void PlayAdvertising::timer(int sec, QTime& timer)
{
    timer=QTime::currentTime();
    timer=timer.addSecs(sec);
}

int PlayAdvertising::MinBreakTime()
{
    int max_time=0;
        for(AdvertisingTimers* advertising: L_timers) {
            if(!advertising->_lastPlay){
                QTime now=QTime::currentTime();
                advertising->_lastPlay=&now;
            }
            advertising->_lastPlay->addSecs(59); // bevor playing new Video you have to wait 59 sec
            int time=advertising->_lastPlay->secsTo(QTime::currentTime());
            if (time>0){  // if advertising was played in the last minute return
                if(time>max_time)
                    max_time=time;
            }
        }
    return max_time;
}

void PlayAdvertising::advertisingTimerQueue(const int &id)
{
    foreach (AdvertisingTimers* advertisngTimer, L_timers) {
        if(advertisngTimer->_id==id)
            L_timerQueue.append(advertisngTimer);
    }
    AdvertisingTimers* nextAdvertising=L_timerQueue.takeFirst();
    QTimer::singleShot(nextAdvertising->_frequency, [=]() {timerEnd(nextAdvertising->_id);});
}

void PlayAdvertising::advertisingVideoEnded(QString name){
    for(AdvertisingTimers* namesOfTimer: L_timers) {
        QTime temp=QTime::currentTime();
        namesOfTimer->_lastPlay=&temp;
        QTimer::singleShot(namesOfTimer->_frequency, [=]() {timerEnd(namesOfTimer->_id);});
        _playing=true;
    }
}

