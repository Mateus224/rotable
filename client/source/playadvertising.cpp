#include "include/playadvertising.h"
#include "touchevent.h"
#include <QtAlgorithms>

// https://forum.qt.io/topic/4752/how-to-stop-a-qtimer-singleshot/7

#define calculateToMin 60000

using namespace rotable;

PlayAdvertising::PlayAdvertising(QList<AdvertisingVideo *>*advertisingVideo,
                                 TouchEvent &touch, int frequnce,
                                 QObject *parent)
    : QObject(parent) {
  l_advertisingVideo = advertisingVideo;
  _touch = &touch;
  _frequency = frequnce* calculateToMin;
  connect(&_timer, &QTimer::timeout, this, &PlayAdvertising::timerEnd);
}

//----------------------------------------------------------

PlayAdvertising::~PlayAdvertising() {
  _timer.stop();
  qDeleteAll(L_timers.begin(), L_timers.end());
  L_timers.clear();
}

//----------------------------------------------------------

void PlayAdvertising::startPlayAdvertising() {
  _timer.stop();
  _playing=false;
  qDeleteAll(L_timers.begin(), L_timers.end());
  L_timers.clear();
  L_timerQueue.clear();
  l_playTimeList.clear();
  for (AdvertisingVideo *video : *l_advertisingVideo) {
    if (video->_advertisingInfo._play) {
      if (video->_advertisingInfo._playTime > 0) {
        st_timer = new AdvertisingTimers();         st_timer->_videoName = &video->_fileInfo._name;
        st_timer->_id = video->_advertisingInfo._id;
        st_timer->_playTime=((1/((float)video->_advertisingInfo._playTime)));
        L_timers.append(st_timer);
        l_playTimeList.append(st_timer->_playTime);
      }
    }
  }
  if (!L_timers.empty()) {
    // calculatePlayListLength();
    creatAdvertisingPlayList();
    setTimer();
  }
}

//----------------------------------------------------------

bool PlayAdvertising::creatAdvertisingPlayList() {
  int m = 0, n = 0, o = 0, k = 0;
  for (int i = 0; i < 100; i++) {
    float tmp = 0;
    for (int j = 0; j < L_timers.length(); j++) {
      if (tmp > l_playTimeList.at(j) || tmp == 0) {
        tmp = l_playTimeList.at(j);
        k = j;
      }
    }
    float h = L_timers.at(k)->_playTime + l_playTimeList.at(k);
    l_playTimeList.replace(k, h);
    L_timerQueue.append(L_timers.at(k));
    qDebug() << "i: " << i << "Queue: " << L_timers.at(k)->_id;
    switch (L_timers.at(k)->_id) {
      /*        case 1:
                  m++;
                  break;
              case 2:
                  n++;
                  break;
              case 3:
                  o++;
                  break;
              default:
                  qDebug()<<"err;";*/
    }
  }

  // qDebug()<<"m:"<<m<<" n: "<<n<<" o :"<<o;
}

//----------------------------------------------------------

void PlayAdvertising::calculatePlayListLength() {
  int a;
  for (int i = 0; i < L_timers.length(); i++) {
    if (i == 0)
      a = L_timers.at(i)->_playTime;
    else
      a = kgV(a, L_timers.at(i)->_playTime);
  }
  _playListLenth = PlayListLength(a);
  qDebug() << "kgV: " << a;
  qDebug() << "lenth: " << _playListLenth;
}

//----------------------------------------------------------

int PlayAdvertising::ggT(int a, int b) {
  if (b == 0)
    return a;
  else
    return ggT(b, a % b);
}

int PlayAdvertising::kgV(int a, int b) { return (a * b) / ggT(a, b); }

//----------------------------------------------------------

int PlayAdvertising::PlayListLength(int kgV) {
  int length = 0;
  for (int i = 0; i < L_timers.length(); i++) {
    length = (kgV / L_timers.at(i)->_playTime) + length;
  }
  return length;
}

//----------------------------------------------------------

void PlayAdvertising::setTimer(int oldTime) {
    if(!_timer.isActive()){
        _timer.setInterval(_frequency);
    }
  //int time = _frequency - oldTime + _timer.remainingTime();
  if(_frequency>0)
    _timer.start(_frequency);
}

//----------------------------------------------------------

void PlayAdvertising::timerEnd() {
  _timer.stop();
  AdvertisingTimers *video;
  int timeToAllowingNextPlayAfterTouch =
      _touch->_secondsFromLastTouchPlus->secsTo(QTime::currentTime());
  if (timeToAllowingNextPlayAfterTouch >=
      0) // true if Touchscreen wasn't touched in the last 45 sec
  {
    if (_playing == false) {
      if (!L_timerQueue.empty()) {
        _playing = true;
        video = L_timerQueue.takeFirst();
        emit play(video->_videoName);
        return;
      }
    }
  }
  int calculatedABS = timeToAllowingNextPlayAfterTouch *
                      ((timeToAllowingNextPlayAfterTouch > 0) -
                       (timeToAllowingNextPlayAfterTouch < 0));
  _timer.start(calculatedABS);
}

//----------------------------------------------------------

void PlayAdvertising::advertisingVideoEnded(QString name) {
  for (AdvertisingTimers *namesOfTimer : L_timers) {
    if (namesOfTimer->_videoName == name) {
      _playing = false;
      L_timerQueue.append(namesOfTimer);
      setTimer();
      //_timer.start();
      return;
    }
  }
}

//----------------------------------------------------------

void PlayAdvertising::setNewFrequency(int frequency)
{
    _timer.stop();
    int old = _frequency;
    _frequency = frequency* calculateToMin;
    setTimer(old);
}

//----------------------------------------------------------
