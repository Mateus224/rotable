#include "callwaiter.h"

using rotable::CallWaiter;


void rotable::CallWaiter::preparePackageToSend()
{
    // Prepare package
    rotable::ComPackageWaiterNeed* package = new ComPackageWaiterNeed();
    package->setNeed(waiterNeed());        //Set state
    package->setTableId(-1);        //Server set id for us

    emit sendCallWaiter(package);
}
