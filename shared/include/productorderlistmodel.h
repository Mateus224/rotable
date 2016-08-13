#ifndef PRODUCTORDERLISTMODEL_H
#define PRODUCTORDERLISTMODEL_H

//#include "private/precomp.h"
//#include "productcontainer.h"
//#include "productcategory.h"
#include "product.h"
#include "productorder.h"

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
 * @brief
 *
 */
class ProductOrderListModel : public QAbstractListModel
{
  Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)


public:
  /**
   * @brief
   *
   */
  enum DataRoles {
    NameRole = Qt::UserRole + 1,
    InfoRole,
    IconRole,
    IdRole,
    PriceStrRole,
    AmountRole
  };

    /**
     * @brief
     *
     * @param parent
     * @param products
     */
    ProductOrderListModel(QObject* parent, rotable::ProductOrder* products);
    /**
     * Get number of rows in given parent.
     *
     * @param parent          parent index
     * @return                row count
     */
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    int columnCount(const QModelIndex & parent = QModelIndex()) const;

    /**
     * @brief
     *
     * @param index
     * @param role
     * @return QVariant
     */
    QVariant data(const QModelIndex & index,
                  int role = Qt::DisplayRole) const;


    /**
     * @brief
     *
     * @param section
     * @param orientation
     * @param role
     * @return QVariant
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    /**
     * @brief
     *
     * @return QHash<int, QByteArray>
     */
    QHash<int, QByteArray> roleNames() const;

    /**
     * @brief
     *
     * @return int
     */
    int count() const;

    /**
     * @brief
     *
     * @param id
     */
    void setCategoryId(int id);


  signals:
    /**
     * @brief
     *
     */
    void countChanged();

private slots:
    /**
     * @brief
     *
     * @param id
     */
    void onCategoryAdded(int id);
    /**
     * @brief
     *
     * @param category
     */
    void onCategoryRemoved(rotable::ProductCategory* category);
    /**
     * @brief
     *
     * @param category
     */
    void onCategoryUpdated(rotable::ProductCategory* category);

    /**
     * @brief
     *
     * @param id
     */
    void onProductAdded(int id);
    /**
     * @brief
     *
     * @param product
     */
    void onProductRemoved(rotable::Product* product);
    /**
     * @brief
     *
     * @param product
     */
    void onProductUpdated(rotable::Product* product);
    /**
     * @brief
     *
     */
    void AmountUpdated();

  private:
    rotable::ProductOrder* _products; /**< TODO: describe */
    int _categoryId; /**< TODO: describe */
};

#endif // PRODUCTORDERLISTMODEL_H
