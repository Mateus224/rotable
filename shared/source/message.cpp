#include "message.h"

using namespace rotable;

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

}

//------------------------------------------------------------------------------

int rotable::OrderMessage::messageType() const
{
    return OrderMessageType;
}

//------------------------------------------------------------------------------
