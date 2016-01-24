#include "include/productorderlistmodel.h"
#include "private/precomp.h"
#include "productcontainer.h"
#include "productcategory.h"
//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------


ProductOrderListModel::ProductOrderListModel(QObject *parent, ProductOrder *products)
    : QAbstractListModel(parent), _products(products), _categoryId(-1)
    {

      Q_ASSERT(products);

      connect(&(_products->_productcontainer), SIGNAL(categoryAdded(int)),
              this, SLOT(onCategoryAdded(int)));
      connect(&(_products->_productcontainer), SIGNAL(categoryRemoved(rotable::ProductCategory*)),
              this, SLOT(onCategoryRemoved(rotable::ProductCategory*)));
      connect(&(_products->_productcontainer), SIGNAL(categoryUpdated(rotable::ProductCategory*)),
              this, SLOT(onCategoryUpdated(rotable::ProductCategory*)));

      connect(&(_products->_productcontainer), SIGNAL(productAdded(int)),
              this, SLOT(onProductAdded(int)));
      connect(&(_products->_productcontainer), SIGNAL(productRemoved(rotable::Product*)),
              this, SLOT(onProductRemoved(rotable::Product*)));
      connect(&(_products->_productcontainer), SIGNAL(productUpdated(rotable::Product*)),
              this, SLOT(onProductUpdated(rotable::Product*)));
      connect(_products, SIGNAL(AmountChanged()),
              this, SLOT(AmountUpdated()));
    }

//------------------------------------------------------------------------------

int ProductOrderListModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid() || -1 == _categoryId) {
    return  _products->_productcontainer._orderProducts->count();
  } else {
    //QList<int> ids = _products->productIds(_categoryId);
    //return ids.count();
    return 15;
  }
}

//------------------------------------------------------------------------------

int ProductOrderListModel::columnCount(const QModelIndex &/*parent*/) const
{
  return 1;
}

//------------------------------------------------------------------------------


QVariant ProductOrderListModel::data(const QModelIndex &index, int role) const
{
  QList<int> ids;
  //if (_categoryId != -1) {
    ids = _products->_productcontainer.productIds_();
  //}

  if (index.column() == 0) {
    switch (role) {
    //case Qt::DisplayRole:
    case NameRole:
    {
      if (ids.count() > index.row()) {
        int productId = ids[index.row()];
        Product* product =  _products->_productcontainer.product(productId);
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
        Product* product =  _products->_productcontainer.product(productId);
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
        Product* product =  _products->_productcontainer.product(productId);
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
    case PriceStrRole:
    {
      if (ids.count() > index.row()) {
        int productId = ids[index.row()];
        Product* product =  _products->_productcontainer.product(productId);
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
        Product* product =  _products->_productcontainer.product(productId);
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

QVariant ProductOrderListModel::headerData(int section,
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

QHash<int, QByteArray> ProductOrderListModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[InfoRole] = "info";
  roles[IconRole] = "icon";
  roles[IdRole] = "productId";
  roles[PriceStrRole] = "priceStr";
  roles[AmountRole] = "amount";
  return roles;
}

//------------------------------------------------------------------------------

int ProductOrderListModel::count() const
{
  if (-1 != _categoryId) {
    return  _products->_productcontainer.productIds(_categoryId).count();
  } else {
    return 0;
  }
}

//------------------------------------------------------------------------------

void ProductOrderListModel::setCategoryId(int id)
{
  _categoryId = id;
  beginResetModel();
  endResetModel();
  emit countChanged();
}

//------------------------------------------------------------------------------

void ProductOrderListModel::onCategoryAdded(int /*id*/)
{

}

//------------------------------------------------------------------------------

void ProductOrderListModel::onCategoryRemoved(ProductCategory *category)
{
  if (category->id() == _categoryId) {
    beginResetModel();
    endResetModel();
    emit countChanged();
  }
}

//------------------------------------------------------------------------------

void ProductOrderListModel::onCategoryUpdated(ProductCategory *category)
{
  if (category->id() == _categoryId) {
    beginResetModel();
    endResetModel();
    emit countChanged();
  }
}

//------------------------------------------------------------------------------

void ProductOrderListModel::onProductAdded(int id)
{
  Product* product = _products->_productcontainer.product(id);
  if (product) {
      beginResetModel();
      endResetModel();
      emit countChanged();
  }
}

//----------------------------------------------------------------------------

//------------------------------------------------------------------------------

void ProductOrderListModel::onProductRemoved(Product *product)
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

void ProductOrderListModel::onProductUpdated(Product *product)
{
  if (product) {
    if (product->categoryId() == _categoryId) {
      beginResetModel();
      endResetModel();
      qDebug()<<"updated";
    }
  }
}

void ProductOrderListModel::AmountUpdated()
{
    qDebug()<<"hier";
    beginResetModel();
    endResetModel();
    emit countChanged();
}
