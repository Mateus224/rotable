#include "private/precomp.h"

#include "productcontainer.h"
#include "product.h"
#include "productcategory.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------


ProductContainer::ProductContainer(QObject* parent)
  : QObject(parent)
{
   _products = new QHash<int, rotable::Product*> ;
   _orderProducts = new QHash<int, rotable::Product*> ;
    //_products=*_products_;
}

//------------------------------------------------------------------------------

ProductContainer::~ProductContainer()
{
  clear();
}

//------------------------------------------------------------------------------

bool ProductContainer::addProduct(Product *product)
{
  if (0 == product) {
    Q_ASSERT(product);
    return false;
  }

  if (product->id() == -1) {
    qDebug() << tr("Could not add product: No product id set!");
    return false;
  }

  if (product->categoryId() == -1) {
    qDebug() << tr("Could not add product: No category id set!");
    return false;
  }

  if (!_categories.contains(product->categoryId())) {
    qDebug() << tr("Could not add product: Category of id '%1' is unknown!")
                .arg(product->categoryId());
    return false;
  }

  if (_products->contains(product->id())) {
    qDebug() << tr("Could not add product: Product of id '%1' is already in list!")
                .arg(product->id());
    return false;
  }

  (*_products)[product->id()] = product;
  connect(product, SIGNAL(iconChanged()), this, SLOT(onProductUpdated()));
  connect(product, SIGNAL(nameChanged()), this, SLOT(onProductUpdated()));
  connect(product, SIGNAL(infoChanged()), this, SLOT(onProductUpdated()));
  connect(product, SIGNAL(priceChanged()), this, SLOT(onProductUpdated()));
  emit productAdded(product->id());

  return true;
}

//------------------------------------------------------------------------------

bool ProductContainer::updateProduct(Product* product)
{
  if (product
      && product->id() != -1
      && _categories.contains(product->categoryId()))
  {
    if (!_products->contains(product->id())) {
      return addProduct(product);
    } else {
      Product *p = (*_products)[product->id()];
      p->setAmount(product->amount());
      p->setCategoryId(product->categoryId());
      p->setIcon(product->icon());
      p->setInfo(product->info());
      p->setPrice(product->price());
      emit productUpdated(p);
      return true;
    }
  } else {
    return false;
  }
}

//------------------------------------------------------------------------------

bool ProductContainer::removeCategory(ProductCategory *category)
{
  if (category) {
    if (removeCategory(category->id())) {
      return true;
    }
  }

  return false;
}

//------------------------------------------------------------------------------

bool ProductContainer::removeCategory(int id)
{
  if (_categories.contains(id)) {
    ProductCategory* category = _categories[id];
    _categories.remove(id);
    emit categoryRemoved(category);
    delete category;
    return true;
  } else {
    return false;
  }
}

//------------------------------------------------------------------------------

bool ProductContainer::removeProduct(Product *product)
{
  if (product) {
    if (removeProduct(product->id())) {
      return true;
    }
  }

  return false;
}

//------------------------------------------------------------------------------

bool ProductContainer::removeProduct(int id)
{
  if (_products->contains(id)) {
    Product* product = (*_products)[id];
    (*_products).remove(id);
    emit productRemoved(product);
    delete product;
    return true;
  } else {
    return false;
  }
}

//------------------------------------------------------------------------------

bool ProductContainer::addCategory(ProductCategory *category)
{
  if (category
      && category->id() != -1
      && !_categories.contains(category->id()))
  {
    _categories[category->id()] = category;
    connect(category, SIGNAL(nameChanged()), this, SLOT(onCategoryUpdated()));
    connect(category, SIGNAL(iconChanged()), this, SLOT(onCategoryUpdated()));
    emit categoryAdded(category->id());
    return true;
  } else {
    return false;
  }
}

//------------------------------------------------------------------------------

bool ProductContainer::updateCategory(ProductCategory* category)
{
  if (category && category->id() != -1) {
    if (!_categories.contains(category->id())) {
      return addCategory(category);
    } else {
      ProductCategory* c = _categories[category->id()];
      c->setIcon(category->icon());
      c->setName(category->name());

      foreach (Product* p, (*_products)) {
        if (p->categoryId() == c->id()) {
          _products->remove(p->id());
        }
      }
      emit categoryUpdated(c);
      return true;
    }
  } else {
    return false;
  }
}

//------------------------------------------------------------------------------

ProductCategory *ProductContainer::category(int id)
{
  if (_categories.contains(id)) {
    return _categories[id];
  } else {
    return 0;
  }
}

//------------------------------------------------------------------------------

ProductCategory* ProductContainer::category(const QString& name)
{
  foreach (ProductCategory* category, _categories) {
    if (category->name().compare(name, Qt::CaseInsensitive) == 0) {
      return category;
    }
  }

  return 0;
}

//------------------------------------------------------------------------------

Product *ProductContainer::product(int id)
{
  if (_products->contains(id)) {
    return (*_products)[id];
  } else {
    return 0;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


void ProductContainer::addForOrderProduct_(int id)
{
  if (_products->contains(id)) {
     (*_orderProducts)[product(id)->id()] =product(id);
      connect(product(id), SIGNAL(iconChanged()), this, SLOT(onProductUpdated()));
      connect(product(id), SIGNAL(nameChanged()), this, SLOT(onProductUpdated()));
      connect(product(id), SIGNAL(infoChanged()), this, SLOT(onProductUpdated()));
      connect(product(id), SIGNAL(priceChanged()), this, SLOT(onProductUpdated()));
      emit productAdded(product(id)->id());

  } else {

  }
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

Product*ProductContainer::product(const QString& name, int categoryId)
{
  foreach (Product* product, (*_products)) {
    if (product->categoryId() == categoryId
        && product->name().compare(name, Qt::CaseInsensitive) == 0)
    {
      return product;
    }
  }

  return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


QList<int> ProductContainer::categoryIds() const
{
  return _categories.keys();
}

//------------------------------------------------------------------------------

QList<int> ProductContainer::productIds() const
{
  return (*_products).keys();
}

//------------------------------------------------------------------------------

QList<int> ProductContainer::productIds(int categoryId) const
{
  QList<int> ids;

  foreach (Product* product, (*_products).values()) {
    if (product->categoryId() == categoryId) {
      ids << product->id();
    }
  }

  return ids;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

QList<int> ProductContainer::productIds_() const
{
  return (*_orderProducts).keys();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


int ProductContainer::categoryCount() const
{
  return _categories.count();
}

//------------------------------------------------------------------------------

int ProductContainer::productCount() const
{
  return (*_products).count();
}

//------------------------------------------------------------------------------

int ProductContainer::productCount(int categoryId) const
{
  int count = 0;

  foreach (Product* product,(*_products).values()) {
    if (product->categoryId() == categoryId) {
      ++count;
    }
  }

  return count;
}

//------------------------------------------------------------------------------

void ProductContainer::clear()
{
  foreach (Product* product, (*_products)) {
    emit productRemoved(product);
    delete product;
  }
  _products->clear();

  foreach (ProductCategory* category, _categories) {
    emit categoryRemoved(category);
    delete category;
  }
  _categories.clear();
}

//------------------------------------------------------------------------------

void ProductContainer::clearProducts(int categoryId)
{
  QList<Product*> removals;

  foreach (Product* product, (*_products).values()) {
    if (product->categoryId() == categoryId) {
      emit productRemoved(product);
      removals << product;
    }
  }

  foreach (Product* product, removals) {
    delete product;
    (*_products).remove(product->id());
  }
}

//------------------------------------------------------------------------------

void ProductContainer::onCategoryUpdated()
{
  ProductCategory* category = static_cast<ProductCategory*>(QObject::sender());
  emit categoryUpdated(category);
}

//------------------------------------------------------------------------------

void ProductContainer::onProductUpdated()
{
  Product* product = static_cast<Product*>(QObject::sender());
  emit productUpdated(product);
}
