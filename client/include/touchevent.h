#ifndef TOUCHEVENT_H
#define TOUCHEVENT_H
#include <QObject>
#include <QTime>

namespace rotable {
class TouchEvent;
}

class rotable::TouchEvent:public QObject
{

    Q_OBJECT
public:
    TouchEvent();
    Q_INVOKABLE void newTouchEvent();

private:
    QTime* _secondsFromLastTouch;


};

#endif // TOUCHEVENT_H
