#ifndef SYSTEMUPDATEDIALOG_H
#define SYSTEMUPDATEDIALOG_H
#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class SystemUpdateDialog;
}

class SystemUpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SystemUpdateDialog(QWidget *parent = 0);
    ~SystemUpdateDialog();

public slots:
    void on_buttonBox_clicked(QAbstractButton *button);
private:
    Ui::SystemUpdateDialog *ui;
};

#endif // SYSTEMUPDATEDIALOG_H
