#ifndef ADDPRODUCTCATEGORY_H
#define ADDPRODUCTCATEGORY_H

//------------------------------------------------------------------------------

#include <QDialog>
#include "filecontainer/imagecontainer.h"
//------------------------------------------------------------------------------

namespace Ui {
class AddProductCategory;
}

namespace rotable {
class ImageContainer;
class ProductContainer;
}

//------------------------------------------------------------------------------

/**
 * This dialog lets the user specify and upload a new product category.
 */
class AddProductCategory : public QDialog
{
  Q_OBJECT

public:
  /**
   * Constructor.
   *
   * @param parent          parent widget
   */
  explicit AddProductCategory(rotable::ImageContainer* images,
                              QWidget *parent = 0);

  /**
   * Destructor
   */
  ~AddProductCategory();

  /**
   * Set product and category container.
   *
   * @param products       product container
   */
  void setProductContainer(rotable::ProductContainer* products);

  /**
   * Get category name.
   *
   * @return              category name
   */
  QString categoryName() const;

  /**
   * Get icon name.
   *
   * @return              icon name
   */
  QString iconName() const;

private slots:
  void onNameChanged(QString name);
  void onAddClicked();
  void onCancelClicked();

private:
  /* UI object */
  Ui::AddProductCategory *_ui;

  /* Products and categories */
  rotable::ProductContainer* _products;
}; // class AddProductCategory

//------------------------------------------------------------------------------

#endif // ADDPRODUCTCATEGORY_H
