#include "message.h"

using namespace rotable;

//------------------------------------------------------------------------------

rotable::Message::Message(QObject *parent) : QObject(parent)
{

}

//------------------------------------------------------------------------------

rotable::Message *Message::parser(ComPackageMessage *message)
{
    Message *message;

    switch(message->msgType()){
    case OrderMessageType:
        message = new OrderMessage();
        break;
    }

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
