#include "private/precomp.h"

#include "producttableiconcomboboxdelegate.h"

//------------------------------------------------------------------------------

ProductTableIconComboboxDelegate::ProductTableIconComboboxDelegate(QObject *parent)
 : QItemDelegate(parent)
{
  _items.append("beer");
  _items.append("bottle");
  _items.append("cocktail");
  _items.append("hotdrink");
  _items.append("longdrink");
  _items.append("shot");
  _items.append("soft");
  _items.append("wine");
  _items.append("shisha");
  _items.append("food");
}

//------------------------------------------------------------------------------

QWidget *ProductTableIconComboboxDelegate::createEditor(
    QWidget *parent, const QStyleOptionViewItem &/*option*/,
    const QModelIndex &/*index*/) const
{
  QComboBox* editor = new QComboBox(parent);

  for (int i = 0; i < _items.count(); ++i) {
    editor->addItem(_items[i]);
  }

  return editor;
}

//------------------------------------------------------------------------------

void ProductTableIconComboboxDelegate::setEditorData(
    QWidget *editor, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  QString value = index.model()->data(index, Qt::EditRole).toString();

  comboBox->setCurrentIndex(0);
  for (int i = 0; i < _items.size(); ++i) {
    if (_items.at(i) == value) {
      comboBox->setCurrentIndex(i);
      break;
    }
  }
}

//------------------------------------------------------------------------------

void ProductTableIconComboboxDelegate::setModelData(
    QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  model->setData(index, _items.at(comboBox->currentIndex()), Qt::EditRole);
}

//------------------------------------------------------------------------------

void ProductTableIconComboboxDelegate::updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
  editor->setGeometry(option.rect);
}

//------------------------------------------------------------------------------

void ProductTableIconComboboxDelegate::paint(
    QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyleOptionViewItem myOption = option;
  myOption.text = index.model()->data(index, Qt::EditRole).toString();

  QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
}
