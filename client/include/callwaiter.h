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
    Q_PROPERTY(QString callWaiterState READ callWaiterState WRITE setCallWaiterState NOTIFY callWaiterStateChanged)
public:

    CallWaiter(): _waiterNeed(false), _callWaiterState("DEFAULT") { }

    inline bool waiterNeed() const { return _waiterNeed; }
    inline void setWaiterNeed(bool waiterNeed)
        { _waiterNeed = waiterNeed; emit waiterNeedChanged();}
    inline void changeWaiterNeed()
        { _waiterNeed = !_waiterNeed; emit waiterNeedChanged();}

    inline QString callWaiterState() const { return _callWaiterState; }
    inline void setCallWaiterState(const QString &callWaiterState )
        { _callWaiterState = callWaiterState; emit callWaiterStateChanged(); }

    void setPropertyState();

    Q_INVOKABLE void preparePackageToSend();

signals:
    void waiterNeedChanged();
    void callWaiterStateChanged();
    void sendCallWaiter(rotable::ComPackage*);  

private:
    bool _waiterNeed;
    QString _callWaiterState;
};

#endif // ROTABLE_CALLWAITER_H

