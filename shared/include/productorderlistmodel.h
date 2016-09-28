#ifndef PRODUCTORDERLISTMODEL_H
#define PRODUCTORDERLISTMODEL_H

//#include "private/precomp.h"
//#include "productcontainer.h"
//#include "productcategory.h"
#include "product.h"
#include "productorder.h"
#include "filecontainer/imagecontainer.h"

//------------------------------------------------------------------------------

#include <QAbstractListModel>

//------------------------------------------------------------------------------

namespace rotable {
  class ProductContainer;
  class ProductCategory;
  class Product;

}

//------------------------------------------------------------------------------

class ProductOrderListModel : public QAbstractListModel
{
  Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)


public:
  enum DataRoles {
    NameRole = Qt::UserRole + 1,
    InfoRole,
    IconRole,
    IdRole,
    PriceStrRole,
    AmountRole
  };

    ProductOrderListModel(QObject* parent, rotable::ProductOrder* products);
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
    void AmountUpdated();

  private:
    rotable::ProductOrder* _products;
    int _categoryId;
};

#endif // PRODUCTORDERLISTMODEL_H
