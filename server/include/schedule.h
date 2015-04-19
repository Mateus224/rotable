#ifndef ROTABLE_SCHEDULE_H
#define ROTABLE_SCHEDULE_H

//------------------------------------------------------------------------------

#ifndef QTHREAD_H
#include <QThread>
#endif

#ifndef QTIMER_H
#include <QTimer>
#endif

#include <QObject>

//------------------------------------------------------------------------------

namespace rotable {
  class Schedule;
  class ScheduleWorker;
  class ScheduleOperation;
}

//------------------------------------------------------------------------------

class rotable::ScheduleOperation : public QObject
{
    Q_OBJECT
public:
    inline ScheduleOperation(){}
    inline void setName(QString name) {_name = name; }
    inline QString name() { return _name; }

private:
    QString _name;
};//class ScheduleOption

//------------------------------------------------------------------------------

class rotable::ScheduleWorker : public QObject
{
    Q_OBJECT
public:
    void addScheduleOperation(rotable::ScheduleOperation *operation);
    void removeOperation(QString name);
public slots:
    // Slot for check ScheduleOption
    void checkSchedule();
signals:
    void startSchedule();
    void stopSchedule();

private:
    QMap<QString,rotable::ScheduleOperation*> _scheduleOption;

    bool hasOperation(ScheduleOperation *operation);
    bool hasOperation(QString name);
};//class ScheduleWorker

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
     * @param ms    time in ms
     */
    inline void setRefreshTime(int ms){ _timer.setInterval(ms); }

    /**
     * Get interval beetween refresh
     * @return
     */
    inline int refresh_time(){ return _timer.interval(); }

    /**
     * Method to add/modify operation to/from schedule
     * @param operation operation
     */
    inline void addOperiationToSchedule(rotable::ScheduleOperation *operation) { _scheduleWorker.addScheduleOperation(operation); }
    inline void removeOperiationFromSchedule(QString name) { _scheduleWorker.removeOperation(name); }

private:

   void stop();
   void run();
   QTimer _timer;
   rotable::ScheduleWorker _scheduleWorker;

};//class Schedule

//------------------------------------------------------------------------------


#endif // SCHEDULE

