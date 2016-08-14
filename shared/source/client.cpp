#include "client.h"
#include "table.h"

using namespace rotable;

//------------------------------------------------------------------------------

#include <QCryptographicHash>

//------------------------------------------------------------------------------

User::User(QObject *parent) : Client(parent) {
  connect(this, &User::nickChanged, this, &User::userChanged);
  connect(this, &User::hashPasswordChanged, this, &User::userChanged);
}

//------------------------------------------------------------------------------

QString User::generateHashPassword(const QString &password) {
  // Create cryptograpy hash generator, initialized with hash type
  QCryptographicHash hash(
      QCryptographicHash::Sha512);             // I'm paranoid and I know it
  hash.addData(password.toUtf8().constData()); // add password
  QByteArray result = hash.result();           // get hash from password
  QString s_result(result);
  return s_result; // return paswword hash
}

//------------------------------------------------------------------------------

void User::setPassword(const QString &password) {
  _passwd = generateHashPassword(password); // set _passwd with hash
  emit hashPasswordChanged();
}

//------------------------------------------------------------------------------

void User::updateData(rotable::User *user) {
  _passwd = user->_passwd;
  _name = user->_name;
  _nick = user->_nick;
}

//------------------------------------------------------------------------------

void User::addAdditionalData(QJsonObject &obj) const {
  // obj["nick"] = _nick;
}

//------------------------------------------------------------------------------

void User::setAdditionalData(QJsonObject &obj) {
  //  _nick = obj["nick"].toString();
}

//------------------------------------------------------------------------------

QJsonValue Client::toJSON() const {
  QJsonObject o;
  o["name"] = name();
  o["type"] = accountType();
  o["cid"] = id();
  addAdditionalData(o);
  return QJsonValue(o);
}

//------------------------------------------------------------------------------

Client *Client::fromJSON(const QJsonValue &jval) {
  QJsonObject o = jval.toObject();

  if (o.contains("name") && o.contains("type")) {
    Client *c;

    switch (o["type"].toInt()) {
    case 0: {
      c = new Waiter();
    } break;
    case 1: {
      c = new Table();
    } break;
    case 2: {
      c = new Admin();
    } break;
    }
    c->setAdditionalData(o);
    c->_name = o["name"].toString();
    c->_id = o["cid"].toInt();

    return c;
  }

  return 0;
}

//------------------------------------------------------------------------------

Client::Client(QObject *parent) : QObject(parent) {}

//------------------------------------------------------------------------------

Client::~Client() {}

//------------------------------------------------------------------------------

Waiter::Waiter(QObject *parent) : User(parent) {}

//------------------------------------------------------------------------------

void Waiter::addAdditionalData(QJsonObject &obj) const {
  User::addAdditionalData(obj);
}

//------------------------------------------------------------------------------

void Waiter::setAdditionalData(QJsonObject &obj) {
  User::setAdditionalData(obj);
}

//------------------------------------------------------------------------------

Admin::Admin(QObject *parent) : User(parent) {}

//------------------------------------------------------------------------------

void Admin::addAdditionalData(QJsonObject &obj) const {
  User::addAdditionalData(obj);
}

//------------------------------------------------------------------------------

void Admin::setAdditionalData(QJsonObject &obj) {
  User::setAdditionalData(obj);
}

//------------------------------------------------------------------------------
