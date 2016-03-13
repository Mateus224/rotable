#ifndef CONFIG_H
#define CONFIG_H

//------------------------------------------------------------------------------

#ifndef QJSONOBJECT_H
#include <QJsonObject>
#endif

#ifndef QSTRING_H
#include <QString>
#endif
#include <QtGui>

//------------------------------------------------------------------------------

namespace rotable {
    class Config;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::Income class defines an income.
 */
class rotable::Config : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int id READ id WRITE setId)
  Q_PROPERTY(int name READ name WRITE setName)
  Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChange)

public:
  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; }

  inline int name() const { return _name; }
  inline void setName(int name) { _name = name;}

  inline QString value() const { return _value; }
  inline void setValue(QString value) { _value = value; emit valueChange();}

  enum {
      day_begin = 0,
      closeState,
      dbVersion
  };

signals:
  void nameChange();
  void valueChange();

private:
  int _id;
  int _name;
  QString _value;

};

#endif // CONFIG_H
