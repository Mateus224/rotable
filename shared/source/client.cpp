#include "client.h"

using namespace rotable;

//------------------------------------------------------------------------------

#include <QCryptographicHash>

//------------------------------------------------------------------------------

User::User(QObject *parent): Client(parent)
{

}

//------------------------------------------------------------------------------

QString User::generateHashPassword(const QString& password)
{
    // Create cryptograpy hash generator, initialized with hash type
    QCryptographicHash hash(QCryptographicHash::Sha512);    // I'm paranoid and I know it
    hash.addData(password.toUtf8().constData());            // add password
    QByteArray result = hash.result();                      // get hash from password
    QString s_result(result);
    return s_result;                                 // return paswword hash
}

//------------------------------------------------------------------------------

void User::setPassword(const QString& password)
{
    _passwd = generateHashPassword(password);                              // set _passwd with hash
    emit hashPasswordChanged();
}

//------------------------------------------------------------------------------

//QJsonValue Client::toJSON() const
//{
//    QJsonObject o;
//    o["nick"] = _nick;
//    o["name"] = _name;
//    o["passwd"] = _passwd;

//    return QJsonValue(o);
//}

//Client *Client::fromJSON(const QJsonValue &jval)
//{
//  QJsonObject o = jval.toObject();

//  if (o.contains("nick")
//      && o.contains("name")
//      && o.contains("passwd"))
//  {
//    Client* c = new Client();
//    c->_nick = o["nick"].toString();
//    c->_name = o["name"].toString();
//    c->_passwd = o["passwd"].toString();

//    return c;
//  }

//  return 0;
//}

//------------------------------------------------------------------------------

Client::Client(QObject *parent): QObject(parent)
{

}

//------------------------------------------------------------------------------

Client::~Client()
{

}

//------------------------------------------------------------------------------

Waiter::Waiter(QObject *parent): User(parent)
{

}

//------------------------------------------------------------------------------

Admin::Admin(QObject *parent): User(parent)
{

}
