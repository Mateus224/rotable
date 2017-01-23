#include "include/touchevent.h"

using namespace rotable;

TouchEvent::TouchEvent():QObject()
{
    _secondsFromLastTouchPlus=new QTime();
}


void TouchEvent::newTouchEvent()
{
    *_secondsFromLastTouchPlus=QTime::currentTime();
    *_secondsFromLastTouchPlus=_secondsFromLastTouchPlus->addSecs(45);
}


