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
class rotable::Client : public QObject {
  Q_OBJECT

  Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
  /**
   * @brief
   *
   * @param parent
   */
  explicit Client(QObject *parent = 0);
  /**
   * @brief
   *
   */
  ~Client();

  /**
   * @brief
   *
   * @return int
   */
  inline int id() const { return _id; }
  /**
   * @brief
   *
   * @param id
   */
  inline void setId(int id) {
    _id = id;
    emit idChanged();
  }

  /**
   * @brief
   *
   * @return QString
   */
  inline QString name() const { return _name; }
  /**
   * @brief
   *
   * @param name
   */
  inline void setName(const QString name) {
    _name = name;
    emit nameChanged();
  }

  QJsonValue toJSON() const;
  static Client *fromJSON(const QJsonValue &jval);

  /**
   * @brief
   *
   * @return int
   */
  inline virtual int accountType() const { return -1; }

signals:
  /**
   * @brief
   *
   */
  void idChanged();
  /**
   * @brief
   *
   */
  void nameChanged();

protected:

  virtual void addAdditionalData(QJsonObject &obj) const = 0;
  virtual void setAdditionalData(QJsonObject &obj) = 0;
  int _id;       /**< TODO: describe */
  QString _name; /**< TODO: describe */

}; // class Client

//------------------------------------------------------------------------------

/**
 * @brief
 *
 */
class rotable::User : public rotable::Client {
  Q_OBJECT

  Q_PROPERTY(QString nick READ nick WRITE setNick NOTIFY nickChanged)
  Q_PROPERTY(QString hashPassword READ hashPassword WRITE setHashPassword NOTIFY
                 hashPasswordChanged)
public:
  /**
   * @brief Default constructor
   *
   * @param parent
   */
  explicit User(QObject *parent = 0);


  /**
   * @brief Default destructor
   *
   */
  ~User();

  /**
   * @brief
   *
   * @return QString
   */
  inline QString nick() const { return _nick; }
  /**
   * @brief
   *
   * @param nick
   */
  inline void setNick(const QString nick) {
    _nick = nick;
    emit nickChanged();
  }

  /**
   * @brief
   *
   * @return QString
   */
  inline QString hashPassword() const { return _passwd; }
  /**
   * @brief
   *
   * @param passwd
   */
  inline void setHashPassword(const QString passwd) {
    _passwd = passwd;
    emit hashPasswordChanged();
  }
  /**
   * @brief
   *
   * @param password
   * @return QString
   */
  static QString generateHashPassword(const QString &password);
  /**
   * @brief
   *
   * @param password
   */
  void setPassword(const QString &password);

  /**
   * @brief
   *
   * @param user
   */
  virtual void updateData(User *user);

signals:
  /**
   * @brief
   *
   */
  void nickChanged();
  /**
   * @brief
   *
   */
  void hashPasswordChanged();
  /**
   * @brief
   *
   */
  void userChanged();
protected:
  virtual void addAdditionalData(QJsonObject &obj) const;
  virtual void setAdditionalData(QJsonObject &obj);
private:
  QString _nick; /**< TODO: describe */
                 /**
                   @_passwd - store hash password (for secure) sha 512
                 */
  QString _passwd;
}; // class User

//------------------------------------------------------------------------------

/**
 * @brief
 *
 */
class rotable::Waiter : public rotable::User {
public:
  /**
   * @brief Default constructor
   *
   * @param parent
   */
  explicit Waiter(QObject *parent = 0);


  /**
   * @brief Default destructor
   *
   */
  ~Waiter();

  /**
   * @brief
   *
   * @return int
   */
  inline virtual int accountType() const { return 0; }

  /**
   * @brief Get list with allow categories
   *
   * @return QList<int> nullptr or list
   */
  QList<int> *categories() const;

  /**
   * @brief set list with allow categories
   *
   * @param categories  QList with categories id
   */
  void setCategories(QList<int> *categories);

protected:
  virtual void addAdditionalData(QJsonObject &obj) const;
  virtual void setAdditionalData(QJsonObject &obj);
private:
  QList<int> *_categories;
}; // class Waiter

//------------------------------------------------------------------------------

/**
 * @brief
 *
 */
class rotable::Admin : public rotable::User {
public:
  /**
   * @brief
   *
   * @param parent
   */
  Admin(QObject *parent = 0);

  /**
   * @brief
   *
   * @return int
   */
  inline virtual int accountType() const { return 2; }
protected:
  virtual void addAdditionalData(QJsonObject &obj) const;
  virtual void setAdditionalData(QJsonObject &obj);
private:
}; // class Admin

//------------------------------------------------------------------------------

#endif // ROTABLE_CLIENT_H
