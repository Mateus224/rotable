#ifndef ROTABLE_SCHEDULE_H
#define ROTABLE_SCHEDULE_H

//------------------------------------------------------------------------------

#ifndef QTHREAD_H
#include <QThread>
#endif

//------------------------------------------------------------------------------

namespace rotable {
  class Schedule;
}

//------------------------------------------------------------------------------

class rotable::Schedule : public QThread
{
    Q_OBJECT

public:
    inline Schedule();

    inline void setRefreshTime(int ms){ _timer.setInterval(ms); }
    inline int refresh_time(){return _timer.interval();}

private:
   void stop();
   QTimer _timer;
   void run();
};


#endif // SCHEDULE

