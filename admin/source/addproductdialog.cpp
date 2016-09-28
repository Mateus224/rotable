#include "private/precomp.h"

#include "addproductdialog.h"
#include "ui_addproductdialog.h"

#include "productcontainer.h"
#include "productcategory.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

AddProductDialog::AddProductDialog(ImageContainer* images, QWidget *parent) :
  QDialog(parent),
  _ui(new Ui::AddProductDialog), _images(images)
{
  _ui->setupUi(this);

  Q_ASSERT(_images);

  QStringList imageNames = _images->imageNames();
  foreach (const QString& name, imageNames) {
    QImage* image = _images->getImage(name);
    if (image) {
      QIcon ico(QPixmap::fromImage(*image));
      _ui->_comboBoxIcons->addItem(ico, name, QVariant(name));
    }
  }

  //_ui->_labelNameError->clear();
  _ui->_pushButtonAdd->setEnabled(false);

  connect(_ui->_comboBoxCategories, SIGNAL(activated(int)),
          this, SLOT(onCategoryChanged(int)));
  connect(_ui->_spinBoxPrice, SIGNAL(valueChanged(int)),
          this, SLOT(onPriceChanged(int)));
  connect(_ui->_lineEditName, SIGNAL(textChanged(QString)),
         this, SLOT(onNameChanged(QString)));
  connect(_ui->_pushButtonAdd, SIGNAL(clicked()),
          this, SLOT(onAddClicked()));
  connect(_ui->_pushButtonCancel, SIGNAL(clicked()),
          this, SLOT(onCancelClicked()));
}

//------------------------------------------------------------------------------

AddProductDialog::~AddProductDialog()
{
  delete _ui;
}

//------------------------------------------------------------------------------

void AddProductDialog::setProductContainer(ProductContainer* products)
{
  _products = products;

  QList<int> categoryIds = _products->categoryIds();
  for (int i = 0; i < categoryIds.count(); ++i) {
    ProductCategory* category = _products->category(categoryIds[i]);
    Q_ASSERT(category);
    if (category) {
      QImage* image = _images->getImage(category->icon());
      QIcon icon;
      if (image) {
        icon = QIcon(QPixmap::fromImage(*image));
      }

      _ui->_comboBoxCategories->addItem(icon, category->name(), category->id());

    }
  }
  _ui->_comboBoxCategories->setCurrentIndex(1);
}

//------------------------------------------------------------------------------

QString AddProductDialog::productName() const
{
  return _ui->_lineEditName->text();
}

//------------------------------------------------------------------------------

QString AddProductDialog::productInfo() const
{
  return _ui->_lineEditInfo->text();
}

//------------------------------------------------------------------------------

int AddProductDialog::productPrice() const
{
  return _ui->_spinBoxPrice->value();
}

//------------------------------------------------------------------------------

int AddProductDialog::categoryId() const
{
  QString categoryName = _ui->_comboBoxCategories->currentText();
  ProductCategory* category = _products->category(categoryName);
  if (category) {
    return category->id();
  } else {
    return -1;
  }
}

//------------------------------------------------------------------------------

QString AddProductDialog::iconName() const
{
  return _ui->_comboBoxIcons->currentText();
}

//------------------------------------------------------------------------------

QString AddProductDialog::productAmount() const
{
  return _ui->_lineEditAmount->text();
}

//------------------------------------------------------------------------------

void AddProductDialog::setCategory(int id)
{
  Q_ASSERT(id == -1 || id >= 0);

  QList<int> categoryIds = _products->categoryIds();
  for (int i = 0; i < categoryIds.count(); ++i) {
    if (categoryIds[i] == id) {
      _ui->_comboBoxCategories->setCurrentIndex(i);
      return;
    }
  }
}

//------------------------------------------------------------------------------

void AddProductDialog::onNameChanged(QString name)
{
  if (name.isEmpty()) {
    //_ui->_labelNameError->clear();
    _ui->_pushButtonAdd->setEnabled(false);
  /*} else if (_products->product(name, categoryId())) {
    _ui->_labelNameError->setText(
          tr("<font color=\"darkred\">Product already exists in this category!</font>"));
    _ui->_pushButtonAdd->setEnabled(false);*/
  } else {
    //_ui->_labelNameError->clear();
    _ui->_pushButtonAdd->setEnabled(true);
  }
}

//------------------------------------------------------------------------------

void AddProductDialog::onPriceChanged(int price)
{
  Product product;
  product.setPrice(price);
  _ui->_labelPriceString->setText(product.priceStr());
}

//------------------------------------------------------------------------------

void AddProductDialog::onCategoryChanged(int /*categoryId*/)
{
  onNameChanged(_ui->_lineEditName->text());
}

//------------------------------------------------------------------------------

void AddProductDialog::onAddClicked()
{
  accept();
}

//------------------------------------------------------------------------------

void AddProductDialog::onCancelClicked()
{
  done(QDialog::Rejected);
}

//------------------------------------------------------------------------------
