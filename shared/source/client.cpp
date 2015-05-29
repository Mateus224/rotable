#include "client.h"

using namespace rotable;

//------------------------------------------------------------------------------

#include <QCryptographicHash>

//------------------------------------------------------------------------------

void User::setPassword(QString password)
{
    // Create cryptograpy hash generator, initialized with hash type
    QCryptographicHash hash(QCryptographicHash::Sha512);    // I'm paranoid and I know it
    hash.addData(password.toUtf8().constData());            // add password
    QByteArray result = hash.result();                      // get hash from password
    _passwd = QString(result);                              // set _passwd with hash
}

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
