#include "messageconnector.h"

using namespace rotable;

//------------------------------------------------------------------------------

MessageConnector::MessageConnector(QObject *parent) : QObject(parent)
{

}

//------------------------------------------------------------------------------

void MessageConnector::reciveMessagePackage(ComPackageMessage *msgPcg)
{
    if(_bindMsg.contains(msgPcg->msgType()))
        _bindMsg[msgPcg->msgType()]->trigger(rotable::Message::parser(msgPcg));
}

//------------------------------------------------------------------------------
