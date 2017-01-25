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

    /** This Method is called from the QML-Files
     *  Every OnClicked calls this funktion
     *  This funkton takes the current time and add 45 seconds
     *  (later we will compare if the last touch was more or less than 45 seconds ago)
     * */
    Q_INVOKABLE void newTouchEvent();

    inline QTime* getLastTouch(){ return _secondsFromLastTouchPlus;}

     QTime* _secondsFromLastTouchPlus;


};

#endif // TOUCHEVENT_H
