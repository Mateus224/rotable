#ifndef CONFIG_H
#define CONFIG_H

//------------------------------------------------------------------------------

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QSTRING_H
#include <QString>
#endif

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
  Q_PROPERTY(QString name READ name WRITE setName)
//  Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChange)

public:
  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; }

  inline QString name() const { return _name; }
  inline void setName(QString name) { _name = name;}

  inline QObject* value() const { return _value; }
  inline void setValue(QObject *value) { _value = value; emit valueChange();}

signals:
  void nameChange();
  void valueChange();

private:
  int _id;
  QString _name;
  QObject *_value;

};

#endif // CONFIG_H
