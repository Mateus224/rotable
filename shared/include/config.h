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
  inline void setId(int id) { _id = id; }

  /**
   * @brief
   *
   * @return int
   */
  inline int name() const { return _name; }
  /**
   * @brief
   *
   * @param name
   */
  inline void setName(int name) { _name = name;}

  /**
   * @brief
   *
   * @return QString
   */
  inline QString value() const { return _value; }
  /**
   * @brief
   *
   * @param value
   */
  inline void setValue(QString value) { _value = value; emit valueChange();}

  /**
   * @brief
   *
   */
  enum {
      day_begin = 0,
      closeState,
      dbVersion,
      triggerProductUpdate
  };

signals:
  /**
   * @brief
   *
   */
  void nameChange();
  /**
   * @brief
   *
   */
  void valueChange();

private:
  int _id; /**< TODO: describe */
  int _name; /**< TODO: describe */
  QString _value; /**< TODO: describe */

};

#endif // CONFIG_H
