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

private:
  /* UI object */
  Ui::Dialog *_ui;

}; // class AddNewLicence

//------------------------------------------------------------------------------

#endif // ADDNEWLICENCE_H
