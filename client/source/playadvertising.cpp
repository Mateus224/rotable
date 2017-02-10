#include "include/playadvertising.h"
#include "touchevent.h"

#define minBreak            53
#define calculateToMin      60000
#define calculateToSec      1000
#define minSettedFrequenc   1 //in sec

using namespace rotable;

PlayAdvertising::PlayAdvertising(QList<AdvertisingVideo*> & advertisingVideo, TouchEvent &touch, QObject *parent)
    : QObject(parent)
{
    l_advertisingVideo=advertisingVideo;
    _touch=&touch;
}

//----------------------------------------------------------

void PlayAdvertising::startPlayAdvertising()
{
    int j=0;
    calculateDelay();
    for(AdvertisingVideo* video: l_advertisingVideo){
        if(video->_advertisingInfo._play==true)
        {
            if(video->_advertisingInfo._frequency >=minSettedFrequenc)
            {
                st_timer=new AdvertisingTimers();
                st_timer->_lastPlay=new QTime();
                st_timer->_startDelay=_delay*(j+1); //_delay=denominator (j+1)=counter
                st_timer->_videoName=&video->_fileInfo._name;
                st_timer->_id=video->_advertisingInfo._id;
                st_timer->_frequency=video->_advertisingInfo._frequency;//*calculateToMin;
                L_timers.append(st_timer);
                int test=video->_advertisingInfo._frequency;
                _frequncy.append(test);
                    QTimer::singleShot(st_timer->_startDelay, [=]() { timerEnd(L_timers.at(j)); } );
                j++; //counter for list
            }
        }
    }
    calculatePlayListLength();
    creatAdvertisingPlayList();
}

//----------------------------------------------------------

bool PlayAdvertising::creatAdvertisingPlayList()
{
    AdvertisingTimers* test=new AdvertisingTimers();
    for(int i=0; i<_playListLenth; i++){
        int tmp=0, k=0;
        for(int j=0; j<L_timers.length();j++){
            if(tmp>_frequncy.at(j)||tmp==0){
               tmp=_frequncy.at(j);
               k=j;
            }
        }
        int h=L_timers.at(k)->_frequency + _frequncy.at(k);
        _frequncy.replace(k,h);
        test=L_timers.at(k);
        qDebug()<<test->_frequency;
        L_timerQueue.append(test);
    }
}

//----------------------------------------------------------

void PlayAdvertising::calculatePlayListLength()
{
    int a;
    for(int i=0;i<L_timers.length();i++){
        if(i==0)
            a=L_timers.at(i)->_frequency;
        else
            a=kgV(a,L_timers.at(i)->_frequency);
    }
    _playListLenth=PlayListLength(a);
    qDebug()<<"kgV: "<<a;
    qDebug()<<"lenth: "<<_playListLenth;
}

//----------------------------------------------------------

int PlayAdvertising::ggT(int a, int b)
{
    if(b == 0)
        return a;
    else return ggT(b, a % b);

}

int PlayAdvertising::kgV(int a, int b){
    return (a * b) / ggT(a, b);
}

//----------------------------------------------------------

int PlayAdvertising::PlayListLength(int kgV)
{
    int length=0;
    for(int i=0;i<L_timers.length();i++){
        length=(kgV/L_timers.at(i)->_frequency)+length;
    }
    return length;
}

//----------------------------------------------------------

void PlayAdvertising::timerEnd(AdvertisingTimers* video)
{
    qDebug()<<_touch->_secondsFromLastTouchPlus->secsTo(QTime::currentTime());
    if(_touch->_secondsFromLastTouchPlus->secsTo(QTime::currentTime())>=0)//true if Touchscreen wasn't touched in the last 45 sec
    {
        if(MinBreakTime()){
            if(_playing==false){
                _playing=true;
                if(!L_timerQueue.empty())
                    L_timerQueue.takeFirst();
                emit play(video->_videoName);
                return;
            }
        }
    }
        advertisingTimerQueue(video,tryLaterAgain); //else
}

//----------------------------------------------------------

void PlayAdvertising::timer(int sec, QTime& timer)
{
    timer=QTime::currentTime();
    timer=timer.addSecs(sec);
}

//----------------------------------------------------------

bool PlayAdvertising::MinBreakTime()
{
    int max_time=0;
        for(AdvertisingTimers* advertising: L_timers) {
            if(!advertising->_lastPlay->isValid()){
                timer(-minBreak, *advertising->_lastPlay);
            }
            QTime tmpLastPlay;
            tmpLastPlay=advertising->_lastPlay->addSecs(minBreak); // bevor playing new Video you have to wait 59 sec
            int time=tmpLastPlay.secsTo(QTime::currentTime());
            qDebug()<<"time:"<<time;
            if(max_time>time)
                max_time=time;
        }
        if(max_time>=0)
            return true;
        return false;
}

//----------------------------------------------------------

void PlayAdvertising::advertisingTimerQueue(AdvertisingTimers* video, source info)
{
if(!alreadyInQueue(video->_id)){
    L_timerQueue.append(video);
}
if(info==tryLaterAgain)
    QTimer::singleShot(L_timerQueue.first()->_frequency, [=]() { timerEnd(L_timerQueue.first());});
}

//----------------------------------------------------------

void PlayAdvertising::advertisingVideoEnded(QString name){
    int i=0;
    for(AdvertisingTimers* namesOfTimer: L_timers) {
        if(namesOfTimer->_videoName==name){
            _playing=false;
            *L_timers.at(i)->_lastPlay=QTime::currentTime();
            int QueueTime=minBreak*calculateToSec+1;
            QTimer::singleShot((QueueTime), [=]() { playVideoInQueue(namesOfTimer);});
            return;
        }
        i++;
    }
}

//----------------------------------------------------------

void PlayAdvertising::calculateDelay(){
    int NumerOfVideos=l_advertisingVideo.length();
    int max_frequency=0;
    for(AdvertisingVideo* video: l_advertisingVideo){
        if(max_frequency<video->_advertisingInfo._frequency)
            max_frequency=video->_advertisingInfo._frequency;
    }
    _delay=(max_frequency*calculateToMin)/NumerOfVideos;
}

//----------------------------------------------------------

bool PlayAdvertising::alreadyInQueue(int id)
{
    int i=0;
    bool AlreadyInQueue=false;
    for(AdvertisingTimers* which: L_timerQueue){
        if(which->_id==id){
            i++;
            if(i==4)
                AlreadyInQueue=true;
        }
    }
    if(AlreadyInQueue)
      return true;
    return false;
}

//----------------------------------------------------------

void PlayAdvertising::playVideoInQueue(AdvertisingTimers* video)
{
    if(!L_timerQueue.empty())
    {
        QTimer::singleShot(0, [=]() { timerEnd(L_timerQueue.first());});
        advertisingTimerQueue(video,putOnlyInQueue);
    }
    else
    {
        int time=video->_frequency-(minBreak*calculateToSec);
        QTimer::singleShot(time, [=]() { timerEnd(video);});
    }
}
//----------------------------------------------------------

/*void PlayAdvertising::tryLater(int id)
{

}*/
