#include "include/touchevent.h"

using namespace rotable;

TouchEvent::TouchEvent():QObject()
{
    _secondsFromLastTouch=new QTime();
}


void TouchEvent::newTouchEvent()
{
    QTime* time= new QTime;
    *time=QTime::currentTime();
    qDebug()<<*time;
    *time=time->addSecs(45);
    qDebug()<<"new time"<<*time;
   *_secondsFromLastTouch=QTime::currentTime();
    int seconds=_secondsFromLastTouch->secsTo(*time);
    qDebug()<<"time:"<<seconds;
}


