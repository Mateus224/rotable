#ifndef PRODUCTCONTAINER_H
#define PRODUCTCONTAINER_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QHash>
#include <QList>

//------------------------------------------------------------------------------

namespace rotable {
class Product;
class ProductCategory;
class ProductContainer;
}

//------------------------------------------------------------------------------

/**
 * The ProductContainer class stores products and categories.
 */
class rotable::ProductContainer : public QObject
{
  Q_OBJECT

public:
  /**
   * Default constructor
   *
   * @param parent          parent object
   */
  explicit ProductContainer(QObject* parent = 0);

  /**
   * Destructor
   */
  ~ProductContainer();

  /**
   * Add a product category.
   *
   * @param category        category
   * @return                true on success
   */
  bool addCategory(rotable::ProductCategory* category);

  /**
   * Add a product.
   *
   * @param product         product
   * @return                true on success
   */
  bool addProduct(rotable::Product* product);

  /**
   * Remove given category (will also destroy the object)
   *
   * @param category        category to remove
   * @return                true on success
   */
  bool removeCategory(rotable::ProductCategory* category);

  /**
   * Remove category given by id.
   *
   * @param id              id of category to remove
   * @return                true on success
   */
  bool removeCategory(int id);

  /**
   * Remove given product (will also destroy the object)
   *
   * @param product         product to remove
   * @return                true on success
   */
  bool removeProduct(rotable::Product* product);

  /**
   * Remove product given by id.
   *
   * @param id              id of product to remove
   * @return                true on success
   */
  bool removeProduct(int id);

  /**
   * Get a product category by id.
   *
   * @param id              product category id
   * @return                pointer to category or null on error
   */
  rotable::ProductCategory *category(int id);

  /**
   * Get a product category by name.
   *
   * @param name            product category name
   * @return                pointer to category or null on error
   */
  rotable::ProductCategory* category(const QString& name);

  /**
   * Get a product by id.
   *
   * @param id              product id
   * @return                pointer to product or null on error
   */
  rotable::Product *product(int id);

  /**
   * Get a product by name and category id.
   *
   * @param name            product name
   * @param categoryId      category id
   * @return                pointer to product or null on error
   */
  rotable::Product* product(const QString& name, int categoryId);

  /**
   * Get list of all product category ids.
   *
   * @return                category ids
   */
  QList<int> categoryIds() const;

  /**
   * Get list of all product ids.
   *
   * @return                product ids
   */
  QList<int> productIds() const;

  /**
   * Get list of all product ids of a category given by id.
   *
   * @param categoryId      category id
   * @return                product ids of given category
   */
  QList<int> productIds(int categoryId) const;

  /**
   * Get total number of categories.
   *
   * @return                category count
   */
  int categoryCount() const;

  /**
   * Get total number of products.
   *
   * @return                product count
   */
  int productCount() const;

  /**
   * Get number of products in category given by id.
   *
   * @return                product count in given category
   */
  int productCount(int categoryId) const;

  /**
   * Clear all products and categories.
   */
  void clear();

  /**
   * Clear all products of given category.
   *
   * @param categoryId      category id
   */
  void clearProducts(int categoryId);

signals:
  void categoryAdded(int id);
  void productAdded(int id);

  void categoryRemoved(rotable::ProductCategory* category);
  void productRemoved(rotable::Product* product);

  void categoryUpdated(rotable::ProductCategory* category);
  void productUpdated(rotable::Product* product);

private slots:
  void onCategoryUpdated();
  void onProductUpdated();

private:
  /* Categories (Mapping of category id to object) */
  QHash<int, rotable::ProductCategory*> _categories;

  /* Products (Mapping of product id to object) */
  QHash<int, rotable::Product*> _products;
}; // class ProductContainer

//------------------------------------------------------------------------------

#endif // PRODUCTCONTAINER_H
