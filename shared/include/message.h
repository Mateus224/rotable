#ifndef ROTABLE_MESSAGE_H
#define ROTABLE_MESSAGE_H

#ifndef QOBJECT_H
#include <QObject>
#endif

#include "compackage.h"

//------------------------------------------------------------------------------

namespace rotable {
    class Message;
    class OrderMessage;
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
     * @return              return
     */
    virtual int messageType() const = 0;


signals:

public slots:

protected:
    enum MessageType{
        OrderMessageType,
        QueryMessageType
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

    /**
     * Constructor for OrderMessage
     * @param message       message package
     */
    OrderMessage(ComPackageMessage *message, QObject *parent = 0);

    int messageType() const Q_DECL_OVERRIDE;
};

#endif // ROTABLE_MESSAGE_H
