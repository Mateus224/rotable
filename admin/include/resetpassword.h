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

public slots:
  virtual void accept();

private:
  Ui::ResetPassword *ui;
};

#endif // RESETPASSWORD_H
