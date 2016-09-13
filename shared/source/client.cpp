#include "client.h"
#include "table.h"

using namespace rotable;

//------------------------------------------------------------------------------

#include <QCryptographicHash>
#include <QJsonArray>

//------------------------------------------------------------------------------

User::User(QObject *parent) : Client(parent) {
  connect(this, &User::nickChanged, this, &User::userChanged);
  connect(this, &User::hashPasswordChanged, this, &User::userChanged);
}

//------------------------------------------------------------------------------

User::~User() {}

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
  obj["hash"] = _passwd;
}

//------------------------------------------------------------------------------

void User::setAdditionalData(QJsonObject &obj) {
  //  _nick = obj["nick"].toString();
  _passwd = obj["hash"].toString();
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
    Client *c = nullptr;

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

Waiter::Waiter(QObject *parent) : User(parent) { _categories = nullptr; }

//------------------------------------------------------------------------------

Waiter::~Waiter() { delete _categories; }

//------------------------------------------------------------------------------

void Waiter::addAdditionalData(QJsonObject &obj) const {
  User::addAdditionalData(obj);
  if(_categories)
  {
    QJsonArray arr;
    for(auto var :*_categories)
      arr.append(var);
    obj["categories"] = arr;
  }
}

//------------------------------------------------------------------------------

void Waiter::setAdditionalData(QJsonObject &obj) {
  User::setAdditionalData(obj);
  QList<int> *list = new QList<int>;
  if(obj.contains("categories"))
  {
    QJsonArray arr = obj["categories"].toArray();
    QList<int> *list = new QList<int>;
    foreach (QJsonValue var, arr)
      list->append(var.toInt());
  }
  setCategories(list);
}

//------------------------------------------------------------------------------

QList<int> *Waiter::categories() const
{
  return _categories;
}

//------------------------------------------------------------------------------

void Waiter::setCategories(QList<int> *categories)
{
  _categories = categories;
}

//------------------------------------------------------------------------------

void Waiter::addWaiterCategory(int id)
{
  _categories->append(id);
  emit addNewCategory(id);
}

//------------------------------------------------------------------------------

void Waiter::removeWaiterCategory(int id)
{
  _categories->removeOne(id);
  emit removeCategory(id);
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
