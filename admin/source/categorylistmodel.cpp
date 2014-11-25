#include "private/precomp.h"

#include "categorylistmodel.h"
#include "productcontainer.h"
#include "productcategory.h"
#include "imagecontainer.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

CategoryListModel::CategoryListModel(QObject *parent)
  : QAbstractListModel(parent), _products(0), _images(0)
{

}

//------------------------------------------------------------------------------

CategoryListModel::~CategoryListModel()
{

}

//------------------------------------------------------------------------------

void CategoryListModel::setProductContainer(ProductContainer *products)
{
  _products = products;
}

//------------------------------------------------------------------------------

void CategoryListModel::setImageContainer(ImageContainer *images)
{
  _images = images;
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

QVariant CategoryListModel::data(const QModelIndex &index, int role) const
{
  if (index.column() == 0) {
    if (index.row() >= 0 && index.row() < _products->categoryCount()) {
      switch (role) {
      case Qt::DisplayRole:
      {
        QList<int> categoryIds = _products->categoryIds();
        ProductCategory* category = _products->category(categoryIds[index.row()]);
        return QVariant(category->name());
      } break;
      case Qt::DecorationRole:
      {
        QList<int> categoryIds = _products->categoryIds();
        ProductCategory* category = _products->category(categoryIds[index.row()]);
        return _images->getImageAsPixmap(category->icon());
      } break;
      case Qt::ToolTipRole:
      {
        QList<int> categoryIds = _products->categoryIds();
        ProductCategory* category = _products->category(categoryIds[index.row()]);
        return QVariant(category->name());
      } break;
      case Qt::BackgroundRole:
      {
        if (index.row() % 2) {
          return QVariant(QBrush(QColor(200, 200, 250)));
        } else {
          return QVariant(QBrush(QColor(220, 220, 250)));
        }
      } break;
      default:
        return QVariant();
      }
    }
  }

  return QVariant();
}

//------------------------------------------------------------------------------

int CategoryListModel::columnCount(const QModelIndex &/*parent*/) const
{
  return 1;
}

//------------------------------------------------------------------------------

QModelIndex CategoryListModel::index(int row, int column,
                                     const QModelIndex& parent) const
{
  if (parent.isValid()
      || row >= _products->categoryCount()
      || column != 0)
  {
    return QModelIndex();
  } else {
    return createIndex(row, 0, _products->categoryIds()[row]);
  }
}

//------------------------------------------------------------------------------

void CategoryListModel::onCategoryAdded(int /*id*/)
{
  beginResetModel();
  endResetModel();
}

//------------------------------------------------------------------------------

void CategoryListModel::onCategoryRemoved(ProductCategory* /*id*/)
{
  beginResetModel();
  endResetModel();
}

//------------------------------------------------------------------------------

void CategoryListModel::onCategoryUpdated(ProductCategory */*category*/)
{
  beginResetModel();
  endResetModel();
}
