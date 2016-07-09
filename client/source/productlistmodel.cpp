#include "private/precomp.h"

#include "productlistmodel.h"
#include "productcontainer.h"
#include "productcategory.h"
#include "product.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ProductListModel::ProductListModel(QObject *parent, ProductContainer *products)
: QAbstractListModel(parent), _products(products), _categoryId(-1)
{

  Q_ASSERT(products);

  connect(_products, SIGNAL(categoryAdded(int)),
          this, SLOT(onCategoryAdded(int)));
  connect(_products, SIGNAL(categoryRemoved(rotable::ProductCategory*)),
          this, SLOT(onCategoryRemoved(rotable::ProductCategory*)));
  connect(_products, SIGNAL(categoryUpdated(rotable::ProductCategory*)),
          this, SLOT(onCategoryUpdated(rotable::ProductCategory*)));

  connect(_products, SIGNAL(productAdded(int)),
          this, SLOT(onProductAdded(int)));
  connect(_products, SIGNAL(productRemoved(rotable::Product*)),
          this, SLOT(onProductRemoved(rotable::Product*)));
  connect(_products, SIGNAL(productUpdated(rotable::Product*)),
          this, SLOT(onProductUpdated(rotable::Product*)));
}

//------------------------------------------------------------------------------

int ProductListModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid() || -1 == _categoryId) {
    return 0;
  } else {
    //QList<int> ids = _products->productIds(_categoryId);
    //return ids.count();
    return 10;
  }
}

//------------------------------------------------------------------------------

int ProductListModel::columnCount(const QModelIndex &/*parent*/) const
{
  return 1;
}

//------------------------------------------------------------------------------

QVariant ProductListModel::data(const QModelIndex &index, int role) const
{
  QList<int> ids;
  if (_categoryId != -1) {
    ids = _products->productIds(_categoryId);
  }

  if (index.column() == 0) {
    switch (role) {
    //case Qt::DisplayRole:
    case NameRole:
    {
      if (ids.count() > index.row()) {
        int productId = ids[index.row()];
        Product* product = _products->product(productId);
        if (product) {
          return QVariant(product->name());
        }
      } else {
        return QString();
      }
    } break;
    case InfoRole:
    {
      if (ids.count() > index.row()) {
        int productId = ids[index.row()];
        Product* product = _products->product(productId);
        if (product) {
          return QVariant(product->info());
        }
      }
      return QString();
    } break;
    case IconRole:
    {
      if (ids.count() > index.row()) {
        int productId = ids[index.row()];
        Product* product = _products->product(productId);
        if (product) {
          return QVariant(product->icon());
        }
      }
    } break;
    case IdRole:
    {
      if (ids.count() > index.row()) {
        int productId = ids[index.row()];
        return QVariant(productId);
      } else {
        return QVariant(-1);
      }
    } break;
    case ColorRole:
    {
      static const char* c_colors[3] = {
        "#8772c0",
        "#0798d1",
        "#f9a8d8"
      };

      int column = index.row() % 5;
      int row = index.row() / 5;

      if (column == 2) {
        return QString(c_colors[2]);
      } else if ((column == 0 || column == 3) && (row % 2) == 0) {
        return QString(c_colors[0]);
      } else if ((column == 1 || column == 4) && (row % 2) == 1) {
        return QString(c_colors[0]);
      } else if ((column == 1 || column == 4) && (row % 2) == 0) {
        return QString(c_colors[1]);
      } else if ((column == 0 || column == 3) && (row % 2) == 1) {
        return QString(c_colors[1]);
      } else {
        qDebug() << tr("unknown color!");
      }
    } break;
    case PriceStrRole:
    {
      if (ids.count() > index.row()) {
        int productId = ids[index.row()];
        Product* product = _products->product(productId);
        if (product) {
          return QVariant(product->priceStr());
        }
      } else {
        return QVariant("");
      }
    } break;
    case AmountRole:
    {
      if (ids.count() > index.row()) {
        int productId = ids[index.row()];
        Product* product = _products->product(productId);
        if (product) {
          return QVariant(product->amount());
        }
      } else {
        return QVariant("");
      }
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

QVariant ProductListModel::headerData(int section,
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

QHash<int, QByteArray> ProductListModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[InfoRole] = "info";
  roles[IconRole] = "icon";
  roles[ColorRole] = "rectColor";
  roles[IdRole] = "productId";
  roles[PriceStrRole] = "priceStr";
  roles[AmountRole] = "amount";
  return roles;
}

//------------------------------------------------------------------------------

int ProductListModel::count() const
{
  if (-1 != _categoryId) {
    return _products->productIds(_categoryId).count();
  } else {
    return 0;
  }
}

//------------------------------------------------------------------------------

void ProductListModel::setCategoryId(int id)
{
  _categoryId = id;
  beginResetModel();
  endResetModel();
  emit countChanged();
}

//------------------------------------------------------------------------------

void ProductListModel::onCategoryAdded(int /*id*/)
{

}

//------------------------------------------------------------------------------

void ProductListModel::onCategoryRemoved(ProductCategory *category)
{
  if (category->id() == _categoryId) {
    beginResetModel();
    endResetModel();
    emit countChanged();
  }
}

//------------------------------------------------------------------------------

void ProductListModel::onCategoryUpdated(ProductCategory *category)
{
  if (category->id() == _categoryId) {
    beginResetModel();
    endResetModel();
    emit countChanged();
  }
}

//------------------------------------------------------------------------------

void ProductListModel::onProductAdded(int id)
{
  Product* product = _products->product(id);
  if (product) {
    if (product->categoryId() == _categoryId) {
      beginResetModel();
      endResetModel();
      emit countChanged();
    }
  }
}

//------------------------------------------------------------------------------

void ProductListModel::onProductRemoved(Product *product)
{
  if (product) {
    if (product->categoryId() == _categoryId) {
      beginResetModel();
      endResetModel();
      emit countChanged();
    }
  }
}

//------------------------------------------------------------------------------

void ProductListModel::onProductUpdated(Product *product)
{
  if (product) {
    if (product->categoryId() == _categoryId) {
      beginResetModel();
      endResetModel();
    }
  }
}
