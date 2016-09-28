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

QString AddNewVideo::getStringVideo()
{
    QString list;
    list.append(_video);
    return list;
}

void AddNewVideo::on_addVideoButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select advertising video"), "~", tr("Video file (*.mp4)"));

    if(fileName != "")
    {
        QFile f(fileName);
        if (!f.open(QFile::ReadOnly | QFile::Text)){
            //TODO: show error message
            qDebug()<<"error reading file";
            return;
        }
        QTextStream in(&f);
        if(f.size()>maxVideoSize){


        }
        else{
            _video = fileName;
            //iSize= _video.size();
            ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
        }

    }



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
