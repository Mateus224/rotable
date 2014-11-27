#ifndef PRODUCTTABLEMODEL_H
#define PRODUCTTABLEMODEL_H

//------------------------------------------------------------------------------

#include <QAbstractTableModel>

//------------------------------------------------------------------------------

namespace rotable {
  class ProductContainer;
  class ImageContainer;
  class Product;
}

//------------------------------------------------------------------------------

/**
 * The ProductTableModel class provides data for the ProductTableView.
 */
class ProductTableModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param parent                parent object
   */
  ProductTableModel(QObject* parent = 0);

  /**
   * Destructor
   */
  ~ProductTableModel();

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
   * This method gets called, when a user edits the table data.
   *
   * @param index               item index
   * @param value               new item value
   * @param role                role
   * @return                    true on success
   */
  bool setData(const QModelIndex & index, const QVariant & value,
               int role = Qt::EditRole);

  /**
   * Returns the item flags for the given index.
   *
   * @param index               item index
   * @return                    item flags
   */
  Qt::ItemFlags flags(const QModelIndex & index) const;

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

  /**
   * Returns the data for the given role and section in the header with the
   * specified orientation.
   *
   * @param section
   * @param orientation
   * @param role
   * @return
   */
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

public slots:
  /**
   * A new product has been added.
   *
   * @param id                  id of new product
   */
  void onProductAdded(int id);

  /**
   * A product has been removed.
   *
   * @param product             removed product
   */
  void onProductRemoved(rotable::Product* product);

  /**
   * A product has been updated.
   *
   * @param product             updated product
   */
  void onProductUpdated(rotable::Product* product);

  /**
   * The category changed.
   *
   * @param id                    category id
   */
  void onCategoryChanged(int id);

private:
  /* Product container */
  rotable::ProductContainer* _products;

  /* Images */
  rotable::ImageContainer* _images;

  /* ID of currently displayed category */
  int _currentCategoryId;
}; // class ProductTableModel

//------------------------------------------------------------------------------

#endif // PRODUCTTABLEMODEL_H
