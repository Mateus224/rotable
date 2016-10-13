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
    /**
     * @brief
     *
     * @param msg
     */
    void trigger(rotable::Message *msg);
};

//------------------------------------------------------------------------------


/**
 * @brief
 *
 */
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

    template<typename Func2>
    /**
     * @brief
     *
     * @param msgType
     * @param toBind
     * @param reciver
     */
    inline void addBindMethod(int msgType, Func2 toBind, const typename QtPrivate::FunctionPointer<Func2>::Object* reciver)
    {
        Connector *connector;
        if(_bindMsg.contains(msgType))
            connector = _bindMsg[msgType];
        else
        {
            connector = new Connector();
            _bindMsg.insert(msgType, connector);
        }

        connect(connector, &Connector::trigger, reciver, toBind);
    }

signals:

public slots:
    /**
     * Slot for recive message package
     *
     * @param msgPcg                package
     */
    void reciveMessagePackage(ComPackageMessage *msgPcg);

private:
    QMap<int, rotable::Connector*> _bindMsg; /**< TODO: describe */
};

//------------------------------------------------------------------------------

#endif // ROTABLE_MESSAGECONNECTOR_H
