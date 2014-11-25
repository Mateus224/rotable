#ifndef PRODUCTLISTMODEL_H
#define PRODUCTLISTMODEL_H

//------------------------------------------------------------------------------

#include <QAbstractListModel>

//------------------------------------------------------------------------------

namespace rotable {
  class ProductContainer;
  class ProductCategory;
  class Product;
}

//------------------------------------------------------------------------------

/**
 * List model for any product list view.
 */
class ProductListModel : public QAbstractListModel
{
  Q_OBJECT

  Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
  enum DataRoles {
    NameRole = Qt::UserRole + 1,
    InfoRole,
    IconRole,
    ColorRole,
    IdRole
  };

  /**
   * Constructor.
   *
   * @param parent          parent object
   * @param products        products (contains categories)
   */
  ProductListModel(QObject* parent, rotable::ProductContainer* products);

  /**
   * Get number of rows in given parent.
   *
   * @param parent          parent index
   * @return                row count
   */
  int rowCount(const QModelIndex & parent = QModelIndex()) const;

  int columnCount(const QModelIndex & parent = QModelIndex()) const;

  QVariant data(const QModelIndex & index,
                int role = Qt::DisplayRole) const;

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  QHash<int, QByteArray> roleNames() const;

  int count() const;

  void setCategoryId(int id);

signals:
  void countChanged();

private slots:
  void onCategoryAdded(int id);
  void onCategoryRemoved(rotable::ProductCategory* category);
  void onCategoryUpdated(rotable::ProductCategory* category);

  void onProductAdded(int id);
  void onProductRemoved(rotable::Product* product);
  void onProductUpdated(rotable::Product* product);

private:
  rotable::ProductContainer* _products;
  int _categoryId;
}; // class ProductListModel

//------------------------------------------------------------------------------

#endif // CATEGORYLISTMODEL_H
