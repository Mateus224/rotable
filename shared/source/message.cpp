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
    case NeedWaiterMessageType:
        msg = new NeedWaiterMessage(message);
        break;
    }

    return msg;
}

//------------------------------------------------------------------------------

OrderMessage::OrderMessage(QObject *parent) : Message(parent)
{

}

//------------------------------------------------------------------------------

OrderMessage::OrderMessage(int status, QObject *parent): OrderMessage(parent)
{
    _errorType = status;
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

QueueMessage::QueueMessage(QMap<int, int> orderQueue, QObject *parent): _orderQueue(orderQueue), Message(parent)
{

}

//------------------------------------------------------------------------------

QMap<int, int> QueueMessage::map()
{
    return _orderQueue;
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
        keys.append(QString::number(it.key()));
        values.append(QString::number(it.value()));
    }
    out = keys.join(";") + ";;" + values.join(";");

    ComPackageMessage *messagePcg = new ComPackageMessage();

    messagePcg->setMsgType(QueueMessage::QueueMessageType);
    messagePcg->setMessage(out);

    return messagePcg;
}

//------------------------------------------------------------------------------

NeedWaiterMessage::NeedWaiterMessage(QObject *parent): Message(parent)
{

}

//------------------------------------------------------------------------------

NeedWaiterMessage::NeedWaiterMessage(ComPackageMessage *message, QObject *parent): Message(parent)
{
    QStringList messageText = message->message().split(";");

    if(messageText.count() !=  2)
        return; //TODO: change it

    _acceptStatusChange =  messageText.at(0).toInt();
    _queuePosition =  messageText.at(1).toInt();
}

//------------------------------------------------------------------------------

int NeedWaiterMessage::messageType() const
{
    return NeedWaiterMessageType;
}

//------------------------------------------------------------------------------

ComPackageMessage *NeedWaiterMessage::toPackage() const
{
    QString message;
    message  = QString::number(_acceptStatusChange).append(";").append(QString::number(_queuePosition));
    ComPackageMessage *msg = new ComPackageMessage();
    msg->setMsgType(messageType());
    msg->setMessage(message);

    return msg;
}

//------------------------------------------------------------------------------

void NeedWaiterMessage::unSuccess()
{
    _acceptStatusChange = false;
    _queuePosition = -1;
}

//------------------------------------------------------------------------------

void NeedWaiterMessage::success(int queuePosition)
{
    _acceptStatusChange = true;
    _queuePosition = queuePosition;
}

//------------------------------------------------------------------------------
