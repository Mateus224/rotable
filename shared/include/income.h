#ifndef INCOME_H
#define INCOME_H

//------------------------------------------------------------------------------

#ifndef QDATETIME_H
#include <QDate>
#endif
#include <QtGui>

//------------------------------------------------------------------------------

namespace rotable {
    class Income;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::Income class defines an income.
 */
class rotable::Income : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int id READ id WRITE setId)
  Q_PROPERTY(float income READ income WRITE setIncome NOTIFY incomeChange)
  Q_PROPERTY(QDate date READ date WRITE setDate)
  Q_PROPERTY(QString format MEMBER _format)

public:
  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; }

  inline float income() const { return _income; }
  inline void setIncome(float income) { _income = income; emit incomeChange(); }

  inline QDate date() const { return _date; }
  inline void setDate(QDate income) { _date = income;}

  inline QString formatedDate(){ return _date.toString(_format); }
  inline void setFormatedDate(QString date){ _date=QDate::fromString(date, _format); }

signals:
  void incomeChange();

private:
  int _id;
  float _income;
  QDate _date;
  static QString _format;

}; // class Income

#endif // INCOME_H

