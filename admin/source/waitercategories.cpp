#include "waitercategories.h"
#include "productcategory.h"

#include <QCheckBox>
#include <QStandardItemModel>

//------------------------------------------------------------------------------

WaiterCategories::WaiterCategories(QWidget *parent)
    : QDialog(parent), _ui(new UiWaiter::Dialog) {
  _ui->setupUi(this);
}

//------------------------------------------------------------------------------

WaiterCategories::WaiterCategories(rotable::ProductContainer *container,
                                   rotable::Waiter *waiter, QWidget *parent)
    : WaiterCategories(parent) {
  _container = container;
  _waiter = waiter;
  loadListView();
}

//------------------------------------------------------------------------------

WaiterCategories::~WaiterCategories() { delete _ui; }

//------------------------------------------------------------------------------

void WaiterCategories::loadListView() {
  QList<int> *categories = _waiter->categories();
  QStandardItemModel *model = new QStandardItemModel(_ui->listView);
  int i = 0;

  for (auto categoryId : _container->categoryIds()) {
    auto *item = new QStandardItem();
    item->setText(_container->category(categoryId)->name());
    item->setCheckable(true);
    item->setData(categories->contains(categoryId) ? Qt::CheckState::Checked
                                                   : Qt::CheckState::Unchecked,
                  Qt::CheckStateRole);

    model->setItem(i++, item);
  }
  _ui->listView->setModel(model);
}

//------------------------------------------------------------------------------