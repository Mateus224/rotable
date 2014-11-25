#ifndef CATEGORYLISTMODEL_H
#define CATEGORYLISTMODEL_H

//------------------------------------------------------------------------------

#include <QAbstractListModel>

//------------------------------------------------------------------------------

namespace rotable {
  class ProductContainer;
  class ProductCategory;
}

//------------------------------------------------------------------------------

/**
 * List model for any category list view.
 */
class CategoryListModel : public QAbstractListModel
{
  Q_OBJECT

  Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
  enum DataRoles {
    NameRole = Qt::UserRole + 1,
    IconRole,
    IdRole
  };

  /**
   * Constructor.
   *
   * @param parent          parent object
   * @param products        products (contains categories)
   */
  CategoryListModel(QObject* parent, rotable::ProductContainer* products);

  int rowCount(const QModelIndex & parent = QModelIndex()) const;
  int columnCount(const QModelIndex & parent = QModelIndex()) const;

  QVariant data(const QModelIndex & index,
                int role = Qt::DisplayRole) const;

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  QHash<int, QByteArray> roleNames() const;

  int count() const;

signals:
  void countChanged();

private slots:
  void onCategoryAdded(int id);
  void onCategoryRemoved(rotable::ProductCategory* category);
  void onCategoryUpdated(rotable::ProductCategory* category);

private:
  rotable::ProductContainer* _products;
}; // class CategoryListModel

//------------------------------------------------------------------------------

#endif // CATEGORYLISTMODEL_H
