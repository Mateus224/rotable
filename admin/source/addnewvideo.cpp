#include "addnewvideo.h"
#include "ui_addnewvideodialog.h"

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

QStringList AddNewVideo::getList()
{
    QStringList list;
    list.append(_video);
    return list;
}

void AddNewVideo::on_addVideoButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select advertising video"), "~", tr("Video file (*.mpeg)"));

    if(fileName != "")
    {
        QFile f(fileName);
        if (!f.open(QFile::ReadOnly | QFile::Text))
            //TODO: show error message
            return;
        //QTextStream in(&f);

        _video = fileName;
    }



}
