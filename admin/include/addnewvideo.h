#ifndef ADDNEWVIDEO_H
#define ADDNEWVIDEO_H
#include "ui_addnewvideodialog.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QBuffer>
#include <QDialog>
#include "compackage.h"

namespace Ui {
class AddNewVideo;
}

class AddNewVideo : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewVideo(QWidget *parent = 0);
    ~AddNewVideo();

    QStringList getStringVideo();
    void progressBarChanged(int value);

private slots:
    void on_addVideoButton_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::AddNewVideoDialog *ui;
    QStringList _videos;
};

#endif // ADDNEWVIDEO_H
