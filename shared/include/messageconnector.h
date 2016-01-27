#ifndef ROTABLE_MESSAGECONNECTOR_H
#define ROTABLE_MESSAGECONNECTOR_H

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QMAP_H
#include <QMap>
#endif

#include "message.h"

namespace rotable {
    class MessageConnector;
}


class rotable::MessageConnector : public QObject
{
    Q_OBJECT
public:
    explicit MessageConnector(QObject *parent = 0);

signals:

public slots:
    /**
     * Slot for recive message package
     *
     * @param msgPcg                package
     */
    void reciveMessagePackage(ComPackageMessage *msgPcg);


private:
    //QMap<int, int*(int)> _bindingFunction;
};

#endif // ROTABLE_MESSAGECONNECTOR_H
