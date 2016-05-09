#ifndef ADDNEWLICENCE_H
#define ADDNEWLICENCE_H

//------------------------------------------------------------------------------

#include <QDialog>

//------------------------------------------------------------------------------

#include "ui_addnewlicencedialog.h"

//------------------------------------------------------------------------------

/**
 * This dialog lets the user add licence
 */
class AddNewLicence : public QDialog
{
  Q_OBJECT

public:
  /**
   * Constructor.
   *
   * @param parent          parent widget
   */
  explicit AddNewLicence(QWidget *parent = 0);

  /**
   * Destructor
   */
  ~AddNewLicence();

private slots:
    void on_addLicenceButton_clicked();

    void on_addLicenceSignButton_clicked();

private:    
    bool checkLicenceHash(QString licence);


  /* UI object */
  Ui::Dialog *_ui;

  QString _licence, _sign;

}; // class AddNewLicence

//-----------------------------------s-------------------------------------------

#endif // ADDNEWLICENCE_H
