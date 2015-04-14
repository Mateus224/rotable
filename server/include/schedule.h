#ifndef ROTABLE_SCHEDULE_H
#define ROTABLE_SCHEDULE_H

//------------------------------------------------------------------------------

#ifndef QTHREAD_H
#include <QThread>
#endif

#ifndef QTIMER_H
#include <QTimer>
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
    inline Schedule(): _refresh_time(1000) {}

    inline void setRefreshTime(int ms){ _refresh_time = ms; }
    inline int refresh_time(){return _refresh_time;}

private:
   int _refresh_time;  // Time beetween check
   void run();

};
#endif // SCHEDULE

