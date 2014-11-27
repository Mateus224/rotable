#include "private/precomp.h"

#include "producttableview.h"
#include "producttableiconcomboboxdelegate.h"
#include "producttablepricespinboxdelegate.h"

//------------------------------------------------------------------------------

ProductTableView::ProductTableView(QWidget *parent) :
    QTableView(parent)
{
  _comboBoxDelegate = new ProductTableIconComboboxDelegate(this);
  _spinBoxDelegate = new ProductTablePriceSpinBoxDelegate(this);

  setItemDelegateForColumn(1, _comboBoxDelegate);
  setItemDelegateForColumn(2, _spinBoxDelegate);
}

//------------------------------------------------------------------------------

void ProductTableView::selectionChanged(const QItemSelection& selected,
                                        const QItemSelection& /*deselected*/)
{
  Q_ASSERT(selected.indexes().count() <= 1);
  if (selected.indexes().count()) {
    QModelIndex selection = selected.indexes()[0];
    emit selectionChanged(selection.internalId());
  } else {
    emit selectionChanged(-1);
  }
}
