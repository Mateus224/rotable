#ifndef ROTABLE_MESSAGECONNECTOR_H
#define ROTABLE_MESSAGECONNECTOR_H

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QMAP_H
#include <QMap>
#endif

#include "message.h"

//------------------------------------------------------------------------------

namespace rotable {
    class MessageConnector;
    class Connector;
}

//------------------------------------------------------------------------------

class rotable::MessageConnector : public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor
     *
     * @param parent                Pointer to parent
     */
    MessageConnector(QObject *parent = 0);

    void addBindMethod(int msgType, void *toBind(Message*), QObject *reciver);
signals:

public slots:
    /**
     * Slot for recive message package
     *
     * @param msgPcg                package
     */
    void reciveMessagePackage(ComPackageMessage *msgPcg);


private:
    QMap<int, rotable::Connector*> _bindMsg;
};

//------------------------------------------------------------------------------

/**
 * @brief The Connector class
 * For create connect with method from other class and package type
 */
class rotable::Connector: public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor
     *
     * @param parent
     */
     Connector(QObject *parent = 0)
        :QObject(parent){}
signals:
    void trigger(rotable::Message *msg);
};

//------------------------------------------------------------------------------

#endif // ROTABLE_MESSAGECONNECTOR_H
