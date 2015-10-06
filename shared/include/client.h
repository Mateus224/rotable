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
}

//------------------------------------------------------------------------------


/**
 * @brief The rotable::Waiter class defines an ordered item.
 */
class rotable:: Client : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged )
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
public:

    explicit  Client(QObject *parent = 0);
    ~Client();


    inline int id() const { return _id; }
    inline void setId(int id) { _id = id; emit idChanged();}

    inline QString name() const { return _name; }
    inline void setName(const QString  name) { _name = name; emit nameChanged();}

//  QJsonValue toJSON() const;
//  static Client *fromJSON(const QJsonValue &jval);

    inline virtual int accountType() { return -1; }
signals:
    void idChanged();
    void nameChanged();

private:
  int _id;
  QString _name;

}; // class Client

//------------------------------------------------------------------------------

class rotable::User : public rotable::Client{
    Q_OBJECT

    Q_PROPERTY(QString nick READ nick WRITE setNick NOTIFY nickChanged)
    Q_PROPERTY(QString hashPassword READ hashPassword WRITE setHashPassword NOTIFY hashPasswordChanged)
public:

    explicit User(QObject *parent = 0);

    inline QString nick() const { return _nick; }
    inline void setNick(const QString  nick) { _nick = nick; emit nickChanged(); }

    inline QString hashPassword() const { return _passwd; }
    inline void setHashPassword(const QString  passwd) { _passwd = passwd; emit hashPasswordChanged();}
    static QString generateHashPassword(const QString &password);
    void setPassword(const QString &password);

signals:
    void nickChanged();
    void hashPasswordChanged();

private:
    QString _nick;
    /**
      @_passwd - store hash password (for secure) sha 512
    */
    QString _passwd;
};  // class User

//------------------------------------------------------------------------------

class rotable::Waiter : public rotable::User{
public:

    explicit Waiter(QObject *parent=0);

    inline virtual int accountType(){ return 0; }
private:

};  // class Waiter

//------------------------------------------------------------------------------

class rotable::Admin : public rotable::User{
public:

    Admin(QObject *parent=0);

    inline virtual int accountType(){ return 2; }
private:

};  // class Admin

//------------------------------------------------------------------------------


#endif // ROTABLE_CLIENT_H
