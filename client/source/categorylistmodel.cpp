#include "private/precomp.h"

#include "categorylistmodel.h"
#include "productcontainer.h"
#include "productcategory.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

CategoryListModel::CategoryListModel(QObject *parent, ProductContainer* products)
  : QAbstractListModel(parent), _products(products)
{
  Q_ASSERT(products);

  connect(_products, SIGNAL(categoryAdded(int)),
          this, SLOT(onCategoryAdded(int)));
  connect(_products, SIGNAL(categoryRemoved(rotable::ProductCategory*)),
          this, SLOT(onCategoryRemoved(rotable::ProductCategory*)));
  connect(_products, SIGNAL(categoryUpdated(rotable::ProductCategory*)),
          this, SLOT(onCategoryUpdated(rotable::ProductCategory*)));
}

//------------------------------------------------------------------------------

int CategoryListModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid()) {
    return 0;
  } else {
    return _products->categoryCount();
  }
}

//------------------------------------------------------------------------------

int CategoryListModel::columnCount(const QModelIndex &/*parent*/) const
{
  return 1;
}

//------------------------------------------------------------------------------

QVariant CategoryListModel::data(const QModelIndex &index, int role) const
{
  if (index.column() == 0 && _products->categoryCount() > index.row()) {
    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
    {
      int categoryId = _products->categoryIds()[index.row()];
      ProductCategory* category = _products->category(categoryId);
      if (category) {
        return QVariant(category->name());
      }
    } break;
    case IconRole:
    {
      int categoryId = _products->categoryIds()[index.row()];
      ProductCategory* category = _products->category(categoryId);
      if (category) {
        return QVariant(category->icon());
      }
    } break;
    case IdRole:
    {
      int categoryId = _products->categoryIds()[index.row()];
      return QVariant(categoryId);
    } break;
    default:
    {
      return QVariant();
    } break;
    }
  }

  return QVariant();
}

//------------------------------------------------------------------------------

QVariant CategoryListModel::headerData(int section,
                                       Qt::Orientation /*orientation*/,
                                       int role) const
{
  if (role == Qt::DisplayRole) {
    if (section == 0) {
      return QVariant(tr("Name"));
    }
  }

  return QVariant();
}

//------------------------------------------------------------------------------

QHash<int, QByteArray> CategoryListModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[IconRole] = "icon";
  roles[IdRole] = "categoryId";
  return roles;
}

//------------------------------------------------------------------------------

int CategoryListModel::count() const
{
  return _products->categoryCount();
}

//------------------------------------------------------------------------------

void CategoryListModel::onCategoryAdded(int /*id*/)
{
  beginResetModel();
  endResetModel();
  emit countChanged();
}

//------------------------------------------------------------------------------

void CategoryListModel::onCategoryRemoved(rotable::ProductCategory*)
{
  beginResetModel();
  endResetModel();
  emit countChanged();
}

//------------------------------------------------------------------------------

void CategoryListModel::onCategoryUpdated(ProductCategory */*category*/)
{
  beginResetModel();
  endResetModel();
}
