#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_hostNameLineEdit_textChanged(const QString &arg1);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
private slots:
    void setLicenceDateEditValues(const QDate &date);
    void on_plainTextEdit_textChanged();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
