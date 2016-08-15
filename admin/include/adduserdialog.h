#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

namespace Ui {
class adduserdialog;
}

/**
 * @brief Dialog used for get data to create new user
 * @see Executor, User
 */
class AddUserDialog : public QDialog {
  Q_OBJECT

public:
  /**
   * @brief Default constructor
   *
   * @param parent  Pointer to parent object
   */
  explicit AddUserDialog(QWidget *parent = 0);

  /**
   * @brief Default destructor
   *
   */
  ~AddUserDialog();

  /**
   * @brief User password
   *
   * @return QString with password
   */
  QString password() const;

  /**
   * @brief User name
   *
   * @return QString with name
   */
  QString name() const;

  /**
   * @brief User account tyoe
   *
   * @return int with account type
   */
  int accountType() const;

private slots:
  /**
   * @brief
   *
   */
  void on_buttonBox_accepted();

private:
  Ui::adduserdialog *ui; /**< UI */
  QString _password;     /**< Field store password */
  QString _name;         /**< Field store name */
  int _accountType;  /**< Field store account type */
};

#endif // ADDUSERDIALOG_H
