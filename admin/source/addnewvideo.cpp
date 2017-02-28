#include "addnewvideo.h"
#include "ui_addnewvideodialog.h"

#define maxVideoSize 200000000

AddNewVideo::AddNewVideo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewVideoDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
}

AddNewVideo::~AddNewVideo()
{
    delete ui;
}

QStringList AddNewVideo::getStringVideo()
{
    return _videos;
}

void AddNewVideo::on_addVideoButton_clicked()
{


    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(trUtf8("Video file (*.mp4)"));
    if (dialog.exec())
        _videos = dialog.selectedFiles();
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);

}

void AddNewVideo::on_buttonBox_clicked(QAbstractButton *button)
{
    QString compareSave= "&Save";
    if(compareSave.compare(button->text())==0)
        ;//qDebug()<<button->text();
    else
        ;//qDebug()<<"is false";
    QDialog::accept();
}
