#include "private/precomp.h"

#include "producttableview.h"
#include "producttablemodel.h"
#include "producttableiconcomboboxdelegate.h"
#include "producttablepricespinboxdelegate.h"

//------------------------------------------------------------------------------

ProductTableView::ProductTableView(QWidget *parent) :
    QTableView(parent)
{
  _comboBoxDelegate = new ProductTableIconComboboxDelegate(this);
  _spinBoxDelegate = new ProductTablePriceSpinBoxDelegate(this);

  setItemDelegateForColumn(ProductTableModel::icon, _comboBoxDelegate);
  setItemDelegateForColumn(ProductTableModel::price, _spinBoxDelegate);
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
