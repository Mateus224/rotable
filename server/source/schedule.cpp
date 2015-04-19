#include "schedule.h"

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

inline  Schedule::Schedule()
{
    _timer.setInterval(1000);

    // Connect timer with checkSchedule
    connect(&_timer, SIGNAL(timeout()), &_scheduleWorker, SLOT(checkSchedule()));
    // Connect scheduleWorker with Schedule(there's no need work schedule when no option, etc.)
    connect(&_scheduleWorker, SLOT(startSchedule()), this, SLOT(start()));
    connect(&_scheduleWorker, SLOT(stopSchedule()), this, SLOT(quit()));
}

//------------------------------------------------------------------------------

void Schedule::ScheduleWorker::checkSchedule()
{
    //TODO
}

//------------------------------------------------------------------------------
