#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

//------------------------------------------------------------------------------

#include <QDialog>

//------------------------------------------------------------------------------

namespace Ui {
class AddProductDialog;
}

namespace rotable {
class ImageContainer;
class ProductContainer;
}

//------------------------------------------------------------------------------

class AddProductDialog : public QDialog
{
  Q_OBJECT

public:
  /**
   * Constructor.
   *
   * @param images            images
   * @param parent            parent widget
   */
  explicit AddProductDialog(rotable::ImageContainer* images, QWidget *parent = 0);

  /**
   * Destructor
   */
  ~AddProductDialog();

  /**
   * Set product and category container.
   *
   * @param products       product container
   */
  void setProductContainer(rotable::ProductContainer* products);

  /**
   * Get product name.
   *
   * @return              product name
   */
  QString productName() const;

  /**
   * Get product info.
   *
   * @return              product info
   */
  QString productInfo() const;

  /**
   * Get product price.
   *
   * @return              product price
   */
  int productPrice() const;

  /**
   * Get category id.
   *
   * @return              category id
   */
  int categoryId() const;

  /**
   * Get icon name.
   *
   * @return              icon name
   */
  QString iconName() const;

  /**
   * Get product amount.
   *
   * @return              amount
   */
  QString productAmount() const;

  /**
   * Set current category id.
   *
   * @param id            category id
   */
  void setCategory(int id);

private slots:
  void onNameChanged(QString name);
  void onPriceChanged(int price);
  void onCategoryChanged(int categoryId);
  void onAddClicked();
  void onCancelClicked();

private:
  /* UI object */
  Ui::AddProductDialog *_ui;

  /* Products and categories */
  rotable::ProductContainer *_products;

  /* Images */
  rotable::ImageContainer* _images;
}; // class AddProductDialog

//------------------------------------------------------------------------------

#endif // ADDPRODUCTDIALOG_H
