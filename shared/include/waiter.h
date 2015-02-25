#ifndef ROTABLE_WAITER_H
#define ROTABLE_WAITER_H

//------------------------------------------------------------------------------

#include <QObject>

//------------------------------------------------------------------------------

namespace rotable {
    class Waiter;
}

//------------------------------------------------------------------------------


/**
 * @brief The rotable::Waiter class defines an ordered item.
 */
class rotable::Waiter : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int id READ id)
  Q_PROPERTY(QString nick READ nick WRITE setNick)
  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(QString passwd READ hashPassword WRITE setPassword WRITE setHashPassword)

public:
  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; }

  inline QString name() const { return _name; }
  inline void setName(const QString  name) { _name = name; }

  inline QString nick() const { return _nick; }
  inline void setNick(const QString  nick) { _nick = nick; }

  inline QString hashPassword() const { return _passwd; }
  inline void setHashPassword(const QString  passwd) { _passwd = passwd; }
  void setPassword(QString password);

signals:


private:
  int _id;
  QString _nick;
  QString _name;
  /**
    @_passwd - store hash password (for secure) sha 512
  */
  QString _passwd;


}; // class OrderItem

#endif // ROTABLE_WAITER_H
