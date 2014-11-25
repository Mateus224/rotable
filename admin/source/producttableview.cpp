#include "private/precomp.h"

#include "producttableview.h"
#include "producttableiconcomboboxdelegate.h"

//------------------------------------------------------------------------------

ProductTableView::ProductTableView(QWidget *parent) :
    QTableView(parent)
{
  _comboBoxDelegate = new ProductTableIconComboboxDelegate(this);
  setItemDelegateForColumn(1, _comboBoxDelegate);
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
