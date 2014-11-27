#include "private/precomp.h"

#include "producttablemodel.h"
#include "productcontainer.h"
#include "productcategory.h"
#include "imagecontainer.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ProductTableModel::ProductTableModel(QObject* parent)
  : QAbstractTableModel(parent), _products(0), _images(0),
    _currentCategoryId(-1)
{

}

//------------------------------------------------------------------------------

ProductTableModel::~ProductTableModel()
{

}

//------------------------------------------------------------------------------

void ProductTableModel::setProductContainer(ProductContainer* products)
{
  _products = products;
}

//------------------------------------------------------------------------------

void ProductTableModel::setImageContainer(ImageContainer* images)
{
  _images = images;
}

//------------------------------------------------------------------------------

int ProductTableModel::rowCount(const QModelIndex& parent) const
{
  if (_currentCategoryId == -1 || parent.isValid()) {
    return 0;
  } else {
    return _products->productCount(_currentCategoryId);
  }
}

//------------------------------------------------------------------------------

QVariant ProductTableModel::data(const QModelIndex& index, int role) const
{

  if (role ==  Qt::BackgroundRole) {
    if (index.row() % 2) {
      return QVariant(QBrush(QColor(200, 250, 200)));
    } else {
      return QVariant(QBrush(QColor(220, 250, 220)));
    }
  }

  switch (index.column()) {
  case 0: // Name
  {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        return QVariant(product->name());
      }
    } else if (role == Qt::DecorationRole) {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        return _images->getImageAsPixmap(product->icon());
      }
    }
  } break;
  case 1: // Icon
  {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        return QVariant(product->icon());
      }
    }
  } break;
  case 2: // Price
  {
    if (role == Qt::DisplayRole) {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        return QVariant(product->priceStr());
      }
    } else if (role == Qt::EditRole) {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        return QVariant(product->price());
      }
    }
  } break;
  case 3: // Info
  {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        return QVariant(product->info());
      }
    }
  } break;
  }

  return QVariant();
}

//------------------------------------------------------------------------------

bool ProductTableModel::setData(const QModelIndex &index,
                                const QVariant &value,
                                int role)
{
  if (role == Qt::EditRole) {
    switch (index.column()) {
    case 0: // Name
    {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        product->setName(value.toString());
        return true;
      }
    } break;
    case 1: // Icon
    {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        product->setIcon(value.toString());
        return true;
      }
    } break;
    case 2: // Price
    {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        product->setPrice(value.toInt());
        return true;
      }
    } break;
    case 3: // Info
    {
      QList<int> productIds = _products->productIds(_currentCategoryId);
      Q_ASSERT(index.row() >= 0 && index.row() < productIds.count());
      Product* product = _products->product(productIds[index.row()]);
      Q_ASSERT(product);
      if (product) {
        product->setInfo(value.toString());
        return true;
      }
    } break;
    }


    return false;
  } else {
    return false;
  }
}

//------------------------------------------------------------------------------

Qt::ItemFlags ProductTableModel::flags(const QModelIndex &/*index*/) const
{
  return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

//------------------------------------------------------------------------------

int ProductTableModel::columnCount(const QModelIndex& /*parent*/) const
{
  return 4;
}

//------------------------------------------------------------------------------

QModelIndex ProductTableModel::index(int row, int column,
                                     const QModelIndex& parent) const
{
  if (!parent.isValid()) {
    QList<int> ids = _products->productIds(_currentCategoryId);
    if (row >= 0 && row < ids.size() && column >= 0 && column < 4) {
      return createIndex(row, column, ids[row]);
    }
  }

  return QModelIndex();
}

//------------------------------------------------------------------------------

QVariant ProductTableModel::headerData(int section,
                                       Qt::Orientation orientation,
                                       int role) const
{
  if (orientation == Qt::Horizontal) {
    if (role == Qt::DisplayRole) {
      switch (section) {
      case 0:
      {
        return QVariant("Name");
      } break;
      case 1:
      {
        return QVariant("Icon");
      } break;
      case 2:
      {
        return QVariant("Price");
      } break;
      case 3:
      {
        return QVariant("Info");
      } break;
      }
    }
  }

  return QVariant();
}

//------------------------------------------------------------------------------

void ProductTableModel::onProductAdded(int id)
{
  if (_products->product(id)->categoryId() == _currentCategoryId) {
    beginResetModel();
    endResetModel();
  }
}

//------------------------------------------------------------------------------

void ProductTableModel::onProductRemoved(Product* product)
{
  if (product->categoryId() == _currentCategoryId) {
    beginResetModel();
    endResetModel();
  }
}

//------------------------------------------------------------------------------

void ProductTableModel::onProductUpdated(Product* product)
{
  if (product->categoryId() == _currentCategoryId) {
    beginResetModel();
    endResetModel();
  }
}

//------------------------------------------------------------------------------

void ProductTableModel::onCategoryChanged(int id)
{
  beginResetModel();
  /*setHeaderData(0, Qt::Horizontal, tr("Name"));
  setHeaderData(1, Qt::Horizontal, tr("Icon"));
  setHeaderData(2, Qt::Horizontal, tr("Price"));
  setHeaderData(3, Qt::Horizontal, tr("Info"));*/
  _currentCategoryId = id;
  endResetModel();
}
