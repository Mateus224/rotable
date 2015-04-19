#include "schedule.h"

#ifndef QTIMER_H
#include <QMap>
#endif

#ifndef QT_CORE_LIB
#include <QtCore>
#endif

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

void Schedule::run()
{
    _timer.start();
    exec();
}

//------------------------------------------------------------------------------

void Schedule::stop()
{
    _timer.stop();
    quit();
}

//------------------------------------------------------------------------------

inline Schedule::Schedule()
{
    _timer.setInterval(1000);

    // Connect timer with checkSchedule
    connect(&_timer, SIGNAL(timeout()), &_scheduleWorker, SLOT(checkSchedule()));
    // Connect scheduleWorker with Schedule(there's no need work schedule when no option, etc.)
    connect(&_scheduleWorker, SLOT(startSchedule()), this, SLOT(start()));
    connect(&_scheduleWorker, SLOT(stopSchedule()), this, SLOT(quit()));
}

//------------------------------------------------------------------------------

void ScheduleWorker::addScheduleOperation(ScheduleOperation *operation)
{

    if (hasOperation(operation))
    {
        _scheduleOption[operation->name()]= operation;
        return ;
    }

    bool run = _scheduleOption.isEmpty();
    _scheduleOption.insert(operation->name(), operation);
    if(run)
        emit startSchedule();
}

//------------------------------------------------------------------------------

void ScheduleWorker::checkSchedule()
{
    //TODO
}

//------------------------------------------------------------------------------

bool ScheduleWorker::hasOperation(rotable::ScheduleOperation *operation)
{
    if(_scheduleOption.contains(operation->name()))
        return true;
    return false;

}

//------------------------------------------------------------------------------
