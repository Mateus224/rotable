#include "callwaiter.h"

using rotable::CallWaiter;

//------------------------------------------------------------------------------

void CallWaiter::setPropertyState()
{
    if(_waiterNeed)
        setCallWaiterState("CALLWAITER");
    else
        setCallWaiterState("DEFAULT");
}

//------------------------------------------------------------------------------

void rotable::CallWaiter::preparePackageToSend()
{
    // Prepare package
    rotable::ComPackageWaiterNeed* package = new ComPackageWaiterNeed();
    package->setNeed(waiterNeed());        //Set state
    package->setTableId(-1);        //Server set id for us

    setCallWaiterState("TRYCALLWAITER");

    emit sendCallWaiter(package);
}

//------------------------------------------------------------------------------

