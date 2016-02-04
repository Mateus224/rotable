#include "message.h"

using namespace rotable;

#ifndef QLIST_H
#include <QList>
#endif

#ifndef QSTRINGLIST_H
#include  <QStringList>
#endif

//------------------------------------------------------------------------------

rotable::Message::Message(QObject *parent) : QObject(parent)
{

}

//------------------------------------------------------------------------------

rotable::Message *Message::parser(ComPackageMessage *message)
{
    Message *msg;

    switch(message->msgType()){
    case OrderMessageType:
        msg = new OrderMessage(message);
        break;
    case QueueMessageType:
        msg = new QueueMessage(message);
        break;
    }

    return msg;
}

//------------------------------------------------------------------------------

OrderMessage::OrderMessage(QObject *parent) : Message(parent)
{

}

//------------------------------------------------------------------------------

OrderMessage::OrderMessage(ComPackageMessage *message, QObject *parent): OrderMessage(parent)
{
    QList<QString> list = message->message().split(";");
    _errorType = list.at(0).toInt();
}

//------------------------------------------------------------------------------

int rotable::OrderMessage::messageType() const
{
    return OrderMessageType;
}

//------------------------------------------------------------------------------

ComPackageMessage *OrderMessage::toPackage() const
{
    QString message;
    message  = QString(_errorType).append(";");
    ComPackageMessage *msg = new ComPackageMessage();
    msg->setMsgType(messageType());
    msg->setMessage(message);

    return msg;
}

//------------------------------------------------------------------------------

QueueMessage::QueueMessage(QObject *parent) : Message(parent)
{

}

//------------------------------------------------------------------------------

QueueMessage::QueueMessage(ComPackageMessage *message, QObject *parent): QueueMessage(parent)
{
    QList<QString> list = message->message().split(";;");
    if(list.count() != 2)       // Something is wrong
        return;
    QList<QString> ids = list.at(0).split(";"), queue = list.at(1).split(";");
    if(ids.count() != queue.count())
        return;                  // Something is wrong

    for(int i  =  0; i< ids.count(); ++i)
        _orderQueue.insert(ids[i].toInt(), queue[i].toInt());
}

//------------------------------------------------------------------------------

int QueueMessage::messageType() const
{
    return QueueMessageType;
}

//------------------------------------------------------------------------------

ComPackageMessage *QueueMessage::toPackage() const
{
    QStringList keys, values;
    QString out;
    for(QMap<int, int>::const_iterator it = _orderQueue.begin(); it != _orderQueue.end(); ++it)
    {
        keys.append(QString(it.key()));
        values.append(QString(it.value()));
    }
    out = keys.join(";") + ";;" + values.join(";");

    ComPackageMessage *messagePcg = new ComPackageMessage();

    messagePcg->setMsgType(QueueMessage::QueueMessageType);
    messagePcg->setMessage(out);

    return messagePcg;
}

//------------------------------------------------------------------------------
