#include "private/precomp.h"

#include "addproductcategory.h"
#include "ui_addproductcategorydialog.h"

#include "productcontainer.h"
#include "productcategory.h"
#include "imagecontainer.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

AddProductCategory::AddProductCategory(ImageContainer* images, QWidget *parent) :
  QDialog(parent),
  _ui(new Ui::AddProductCategory), _products(0)
{
  _ui->setupUi(this);

  QStringList imageNames = images->imageNames();
  foreach (const QString& name, imageNames) {
    QImage* image = images->getImage(name);
    if (image) {
      QIcon ico(QPixmap::fromImage(*image));
      _ui->_comboBoxIcons->addItem(ico, name, QVariant(name));
    }
  }

  _ui->_labelNameError->clear();
  _ui->_pushButtonAdd->setEnabled(false);

  connect(_ui->_lineEditName, SIGNAL(textChanged(QString)),
          this, SLOT(onNameChanged(QString)));
  connect(_ui->_pushButtonAdd, SIGNAL(clicked()),
          this, SLOT(onAddClicked()));
  connect(_ui->_pushButtonCancel, SIGNAL(clicked()),
          this, SLOT(onCancelClicked()));
}

//------------------------------------------------------------------------------

AddProductCategory::~AddProductCategory()
{
  delete _ui;
}

//------------------------------------------------------------------------------

void AddProductCategory::setProductContainer(rotable::ProductContainer* products)
{
  _products = products;
}

//------------------------------------------------------------------------------

QString AddProductCategory::categoryName() const
{
  return _ui->_lineEditName->text();
}

//------------------------------------------------------------------------------

QString AddProductCategory::iconName() const
{
  return _ui->_comboBoxIcons->currentText();
}

//------------------------------------------------------------------------------

void AddProductCategory::onNameChanged(QString name)
{
  if (name.isEmpty()) {
    _ui->_labelNameError->clear();
    _ui->_pushButtonAdd->setEnabled(false);
  } else if (_products->category(name)) {
    _ui->_labelNameError->setText(
          tr("<font color=\"darkred\">Category already exists!</font>"));
    _ui->_pushButtonAdd->setEnabled(false);
  } else {
    _ui->_labelNameError->clear();
    _ui->_pushButtonAdd->setEnabled(true);
  }
}

//------------------------------------------------------------------------------

void AddProductCategory::onAddClicked()
{
  accept();
}

//------------------------------------------------------------------------------

void AddProductCategory::onCancelClicked()
{
  done(QDialog::Rejected);
}
