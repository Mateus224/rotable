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
  class ScheduleOption;
}

//------------------------------------------------------------------------------

class rotable::Schedule : public QThread
{
    Q_OBJECT

public:
    /**
     * Default constructor
     *
     * Init _timer interval, connect slots, etc.
     */
    inline Schedule();

    /**
     * Set interval beetween refresh
     * @param ms
     */
    inline void setRefreshTime(int ms){ _timer.setInterval(ms); }

    /**
     * Get interval beetween refresh
     * @return
     */
    inline int refresh_time(){ return _timer.interval(); }

    void addOperiationToSchedule();
    void removeOperiationFromSchedule();

private:

   void stop();
   QTimer _timer;
   void run();
   class ScheduleWorker _scheduleWorker;

};//class Schedule

//------------------------------------------------------------------------------

class rotable::Schedule::ScheduleWorker
{
    Q_OBJECT
public:
    void checkSchedule();
};//class ScheduleWorker

//------------------------------------------------------------------------------

class rotable::ScheduleOption
{
    Q_OBJECT
public:
    inline ScheduleOption(){}

};//class ScheduleOption

//------------------------------------------------------------------------------

#endif // SCHEDULE

