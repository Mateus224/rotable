#include "include/playadvertising.h"
#include "touchevent.h"

using namespace rotable;

PlayAdvertising::PlayAdvertising(QList<AdvertisingVideo*> & advertisingVideo, TouchEvent &touch, QObject *parent)
    : QObject(parent)
{
    l_advertisingVideo=advertisingVideo;
    _touch=&touch;
}

void PlayAdvertising::startPlayAdvertising()
{
    int j=0;
    foreach(AdvertisingVideo* video, l_advertisingVideo){
        if(video->_advertisingInfo._play==true)
        {
            st_timer=new AdvertisingTimers();
            st_timer->_timer=new QTime();
            st_timer->_lastPlay=new QTime();
            st_timer->_videoName=&video->_fileInfo._name;
            st_timer->_id=video->_advertisingInfo._id;
            st_timer->_frequency=video->_advertisingInfo._frequency*1000;
            L_timers.append(st_timer);
            timer(90,*st_timer->_timer);
            QTimer::singleShot(st_timer->_frequency, [=]() { timerEnd(L_timers.at(j)->_id); } );
            j++; //normal int for list
        }
    }
}


void PlayAdvertising::timerEnd(int& id)
{
    int nextPlay;
    qDebug()<<_touch->_secondsFromLastTouchPlus->secsTo(QTime::currentTime());
    if(_touch->_secondsFromLastTouchPlus->secsTo(QTime::currentTime())>=0)//true if Touchscreen wasn't touched in the last 45 sec
    {
        nextPlay=MinBreakTime();
        qDebug()<<"nextPlay:"<<nextPlay;
        if(nextPlay<=0){
            if(L_timerQueue.empty()){
                qDebug()<<"L=1:";
                if(_playing==false){
                          qDebug()<<"L=2:";
                    _playing=true;
                    for(AdvertisingTimers* namesOfTimer: L_timers) {
                        if(namesOfTimer->_id==id){
                            emit play(namesOfTimer->_videoName);
                            return;
                        }
                    }
                }
            }
        }
    }
        advertisingTimerQueue(id); //else
}


void PlayAdvertising::timer(int sec, QTime& timer)
{
    timer=QTime::currentTime();
    timer=timer.addSecs(sec);
}

int PlayAdvertising::MinBreakTime()
{
    int i=0;
    int max_time=60;
        for(AdvertisingTimers* advertising: L_timers) {
            if(!advertising->_lastPlay->isValid()){
                timer(0, *advertising->_lastPlay);
            }
            *advertising->_lastPlay=advertising->_lastPlay->addSecs(59); // bevor playing new Video you have to wait 59 sec
            int time=advertising->_lastPlay->secsTo(QTime::currentTime());
            qDebug()<<"time:"<<time;
            if (time<max_time){  // looking for the latest played advertising in the list
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
    int i=0;
    for(AdvertisingTimers* namesOfTimer: L_timers) {
        if(namesOfTimer->_videoName==name){
            *L_timers.at(i)->_lastPlay=QTime::currentTime();
            QTimer::singleShot(namesOfTimer->_frequency, [=]() {timerEnd(namesOfTimer->_id);});
            _playing=false;
        }
        i++;
    }
}
