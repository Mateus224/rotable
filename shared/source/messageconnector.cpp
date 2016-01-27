#include "messageconnector.h"

using namespace rotable;

//------------------------------------------------------------------------------

MessageConnector::MessageConnector(QObject *parent) : QObject(parent)
{

}

//------------------------------------------------------------------------------

void MessageConnector::addBindMethod(int msgType, void *toBind(Message *), QObject *reciver)
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

//------------------------------------------------------------------------------

void MessageConnector::reciveMessagePackage(ComPackageMessage *msgPcg)
{
    if(_bindMsg.contains(msgPcg->msgType()))
        _bindMsg[msgPcg->msgType()]->trigger(rotable::Message::parser(msgPcg));
}

//------------------------------------------------------------------------------
