#include "private/precomp.h"

#include "categorylistview.h"

//------------------------------------------------------------------------------

CategoryListView::CategoryListView(QWidget *parent) :
    QListView(parent)
{
}

//------------------------------------------------------------------------------

void CategoryListView::selectionChanged(const QItemSelection& selected,
                                        const QItemSelection& /*deselected*/)
{
  Q_ASSERT(selected.indexes().count() <= 1);
  if (selected.indexes().count()) {
    QModelIndex selection = selected.indexes()[0];
    Q_ASSERT(selection.column() == 0);
    emit selectionChanged(selection.internalId());
  } else {
    emit selectionChanged(-1);
  }
}
