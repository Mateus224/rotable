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
   * @return double
   */
  inline double income() const { return _income; }
  /**
   * @brief
   *
   * @param income
   */
  inline void setIncome(double income) { _income = income; emit incomeChange(); }

  /**
   * @brief
   *
   * @return QDate
   */
  inline QDate date() const { return _date; }
  /**
   * @brief
   *
   * @param income
   */
  inline void setDate(QDate income) { _date = income;}

  /**
   * @brief
   *
   * @return QString
   */
  inline QString formatedDate(){ return _date.toString(_format); }
  /**
   * @brief
   *
   * @param date
   */
  inline void setFormatedDate(QString date){ _date=QDate::fromString(date, _format); }

  /**
   * @brief
   *
   * @return QJsonValue
   */
  QJsonValue toJSON() const;
  /**
   * @brief
   *
   * @param jval
   * @return Income
   */
  static Income* fromJSON(const QJsonValue& jval);

signals:
  /**
   * @brief
   *
   */
  void incomeChange();

private:
  int _id; /**< TODO: describe */
  double _income; /**< TODO: describe */
  QDate _date; /**< TODO: describe */
  static QString _format; /**< TODO: describe */

}; // class Income

#endif // INCOME_H

