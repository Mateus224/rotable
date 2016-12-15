#include "include/files/advertisingtableview.h"
#include "private/precomp.h"
AdvertisingTableView::AdvertisingTableView(QWidget *parent) :
QTableView(parent)
{

}

void AdvertisingTableView::selectionChanged(const QItemSelection& selected,
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
