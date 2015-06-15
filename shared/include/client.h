#ifndef ROTABLE_CLIENT_H
#define ROTABLE_CLIENT_H

//------------------------------------------------------------------------------

#ifndef QJSONOBJECT_H
#include <QJsonObject>
#endif

#ifndef QOBJECT_H
#include <QObject>
#endif

//------------------------------------------------------------------------------

namespace rotable {
    class Client;
    class User;
    class Waiter;
    class Admin;
    class Table;
}

//------------------------------------------------------------------------------


/**
 * @brief The rotable::Waiter class defines an ordered item.
 */
class rotable::Client : public QObject
{
public:
  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; }

  inline QString name() const { return _name; }
  inline void setName(const QString  name) { _name = name; }

//  QJsonValue toJSON() const;
//  static Client *fromJSON(const QJsonValue &jval);

  inline virtual int accountType() = 0;
signals:

private:
  int _id;
  QString _name;

}; // class Client

//------------------------------------------------------------------------------

class rotable::User : public Client{
public:
    inline QString nick() const { return _nick; }
    inline void setNick(const QString  nick) { _nick = nick; }

    inline QString hashPassword() const { return _passwd; }
    inline void setHashPassword(const QString  passwd) { _passwd = passwd; }
    static QString generateHashPassword(const QString &password);
    void setPassword(const QString &password);
private:
    QString _nick;
    /**
      @_passwd - store hash password (for secure) sha 512
    */
    QString _passwd;
};  // class User

//------------------------------------------------------------------------------

class rotable::Waiter : public User{
public:
    inline virtual int accountType(){ return 0; }
private:

};  // class Waiter

//------------------------------------------------------------------------------

class rotable::Admin : public User{
public:
    inline virtual int accountType(){ return 2; }
private:

};  // class Admin

//------------------------------------------------------------------------------

class rotable::Table :public Client{
public:
    inline virtual int accountType(){ return 1; }
};  // class Table

//------------------------------------------------------------------------------


#endif // ROTABLE_CLIENT_H
