#ifndef RESETPASSWORD_H
#define RESETPASSWORD_H

#include <QDialog>

namespace Ui {
  class ResetPassword;
}

class ResetPassword : public QDialog
{
  Q_OBJECT

public:
  explicit ResetPassword(QWidget *parent = 0);
  ~ResetPassword();
  QString password() const;

public slots:
  virtual void accept();

private:
  Ui::ResetPassword *ui;
  QString _password;
};

#endif // RESETPASSWORD_H
