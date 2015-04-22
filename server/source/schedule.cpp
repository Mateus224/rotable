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

    // Check if operation already exist in list
    if (hasOperation(operation))
    {
        // delete old value
        delete _scheduleOption[operation->name()];
        //set new value
        _scheduleOption[operation->name()]= operation;
        return ;
    }

    // Check if schedule is run( if list is empty => no run)
    bool run = _scheduleOption.isEmpty();
    // Add oprion to list
    _scheduleOption.insert(operation->name(), operation);
    if(run)     // Emit signal to start schedule
        emit startSchedule();
}

//------------------------------------------------------------------------------

void ScheduleWorker::removeOperation(QString name)
{
    // Operation don't exist?
    if(!hasOperation(name))
    {
        // Yes. so we send message about that
        qCritical() << tr("Option %1 don't exist, skipping..").arg(name);
        return ;
    }

    //  Remove position from list
    delete _scheduleOption[name];
    if(_scheduleOption.isEmpty())   // If list is empty
        emit stopSchedule();        // Stop schedule
}

//------------------------------------------------------------------------------

void ScheduleWorker::checkSchedule()
{
    // Object with current time and date
    QDateTime time = QDateTime::currentDateTime();
    // Foreach element in list
    foreach (ScheduleOperation *operation, _scheduleOption) {
        // Chech if actual time > time when we should do something
        if(time > operation->next())
        {
            // Do "something"
            operation->operation();
            // Calc when we need do something next time
            operation->calcNext();
        }
    }
}

//------------------------------------------------------------------------------

bool ScheduleWorker::hasOperation(rotable::ScheduleOperation *operation)
{
    // if map contains element with key, key is name of operation
    if(_scheduleOption.contains(operation->name()))
        return true;
    return false;

}

//------------------------------------------------------------------------------

bool ScheduleWorker::hasOperation(QString name)
{
    // if map contains element with key, key is name of operation
    if(_scheduleOption.contains(name))
        return true;
    return false;
}

//------------------------------------------------------------------------------
