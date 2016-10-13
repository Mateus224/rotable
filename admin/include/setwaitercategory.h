#ifndef SETWAITERCATEGORY_H
#define SETWAITERCATEGORY_H

#include <QDialog>

namespace Ui {
class SetWaiterCategory;
}

class SetWaiterCategory : public QDialog
{
    Q_OBJECT

public:
    explicit SetWaiterCategory(QWidget *parent = 0);
    ~SetWaiterCategory();

private:
    Ui::SetWaiterCategory *ui;
};

#endif // SETWAITERCATEGORY_H
