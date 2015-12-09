#ifndef ROTABLE_CALLWAITER_H
#define ROTABLE_CALLWAITER_H

//------------------------------------------------------------------------------

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef ROTABLE_COMPACKAGE_H
#include "compackage.h"
#endif

//------------------------------------------------------------------------------

namespace rotable {
    class CallWaiter;
}

//------------------------------------------------------------------------------

class rotable::CallWaiter: public QObject{
    Q_OBJECT

    Q_PROPERTY(bool waiterNeed READ waiterNeed WRITE setWaiterNeed NOTIFY waiterNeedChanged)
public:

    inline bool waiterNeed() const { return _waiterNeed; }
    inline void setWaiterNeed(bool waiterNeed)
        { _waiterNeed = waiterNeed; emit waiterNeedChanged();}

    CallWaiter(): _waiterNeed(false) { }

    Q_INVOKABLE void preparePackageToSend();

signals:
    void waiterNeedChanged();
    void sendCallWaiter(rotable::ComPackage*);  

private:
    bool _waiterNeed;
};

#endif // ROTABLE_CALLWAITER_H

