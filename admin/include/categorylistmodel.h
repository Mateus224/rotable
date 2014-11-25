#ifndef CATEGORYLISTMODEL_H
#define CATEGORYLISTMODEL_H

//------------------------------------------------------------------------------

#include <QAbstractListModel>

//------------------------------------------------------------------------------

namespace rotable {
class ProductContainer;
class ImageContainer;
class ProductCategory;
}

//------------------------------------------------------------------------------

/**
 * The CategoryListModel class provides data for the CategoryListView.
 */
class CategoryListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param parent                parent object
   */
  CategoryListModel(QObject* parent = 0);

  /**
   * Destructor
   */
  ~CategoryListModel();

  /**
   * Set the product container.
   *
   * @param products              product container
   */
  void setProductContainer(rotable::ProductContainer* products);

  /**
   * Set the image container.
   *
   * @param images          image container
   */
  void setImageContainer(rotable::ImageContainer* images);

  /**
   * Returns the number of rows under the given parent.
   *
   * When the parent is valid it means that rowCount is returning the number of
   * children of parent.
   *
   * @param parent              parent
   * @return                    number of rows
   */
  int rowCount(const QModelIndex & parent = QModelIndex()) const;

  /**
   * Returns the data stored under the given role for the item referred to by
   * the index.
   *
   * @param index               data index
   * @param role                data role
   * @return                    data
   */
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  /**
   * Returns the number of columns for the children of the given parent.
   *
   * @param parent              parent item
   * @return                    column count
   */
  int columnCount(const QModelIndex & parent = QModelIndex()) const;

  /**
   * Returns the index of the data in row and column with parent.
   *
   * @param row               row
   * @param column            column
   * @param parent            parent
   * @return                  index
   */
  QModelIndex index(int row, int column = 0,
                    const QModelIndex & parent = QModelIndex()) const;

public slots:
  /**
   * A new category has been added.
   *
   * @param id                  id of new category
   */
  void onCategoryAdded(int id);

  /**
   * A category has been removed.
   *
   * @param id                  id of removed category
   */
  void onCategoryRemoved(rotable::ProductCategory* category);

  /**
   * A category has been updated.
   *
   * @param category            updated category
   */
  void onCategoryUpdated(rotable::ProductCategory* category);

private:
  /* Product container */
  rotable::ProductContainer* _products;

  /* Images */
  rotable::ImageContainer* _images;
}; // class CategoryListModel

//------------------------------------------------------------------------------

#endif // CATEGORYLISTMODEL_H
