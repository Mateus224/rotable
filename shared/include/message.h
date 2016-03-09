#ifndef ROTABLE_MESSAGE_H
#define ROTABLE_MESSAGE_H

#ifndef QOBJECT_H
#include <QObject>
#endif

#include "compackage.h"

#ifndef QMAP_H
#include <QMap>
#endif

//------------------------------------------------------------------------------

namespace rotable {
    class Message;
    class OrderMessage;
    class QueueMessage;
}

//------------------------------------------------------------------------------

class rotable::Message : public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor
     * @param parent        pointer to inherit object
     */
    explicit Message(QObject *parent = 0);

    //--------------------------------------------------------------------------
    // Virtual method
    //--------------------------------------------------------------------------

    /**
     * Parse package to message
     *
     * @param message       package with message
     * @return              message obj
     */
    static Message *parser(ComPackageMessage *message);

    /**
     * Type of message
     *
     * @return              message object type
     */
    virtual int messageType() const = 0;

    /**
     * Convert message to package
     *
     * @return              ComPackageMessage
     */
    virtual ComPackageMessage *toPackage() const = 0;
signals:

public slots:

protected:
    enum MessageType{
        OrderMessageType,
        QueueMessageType
    };
};

//------------------------------------------------------------------------------

class rotable::OrderMessage : public rotable::Message
{

public:

    /**
     * Default constructor
     */
    OrderMessage(QObject *parent = 0);

    OrderMessage(int status, QObject *parent = 0);

    /**
     * Constructor for OrderMessage
     * @param message       message package
     */
    OrderMessage(ComPackageMessage *message, QObject *parent = 0);

    int messageType() const Q_DECL_OVERRIDE;

    ComPackageMessage *toPackage() const Q_DECL_OVERRIDE;

 private:
    int _errorType;
};

//------------------------------------------------------------------------------

class rotable::QueueMessage : public rotable::Message
{

public:

    /**
     * Default constructor
     */
    QueueMessage(QObject *parent = 0);

    /**
     * Constructor for QueueMessage
     * @param message       message package
     */
    QueueMessage(ComPackageMessage *message, QObject *parent = 0);

    int messageType() const Q_DECL_OVERRIDE;

    ComPackageMessage *toPackage() const Q_DECL_OVERRIDE;

private:

    QMap<int, int> _orderQueue;
};

//------------------------------------------------------------------------------

#endif // ROTABLE_MESSAGE_H
