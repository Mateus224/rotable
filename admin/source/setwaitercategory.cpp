#include "setwaitercategory.h"
#include "ui_setwaitercategory.h"

SetWaiterCategory::SetWaiterCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetWaiterCategory)
{
    ui->setupUi(this);
}

SetWaiterCategory::~SetWaiterCategory()
{
    delete ui;
}
