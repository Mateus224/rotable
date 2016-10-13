#include "private/precomp.h"

#include "producttablepricespinboxdelegate.h"

//------------------------------------------------------------------------------

ProductTablePriceSpinBoxDelegate::ProductTablePriceSpinBoxDelegate(QObject *parent)
 : QStyledItemDelegate(parent)
{

}

//------------------------------------------------------------------------------

QWidget *ProductTablePriceSpinBoxDelegate::createEditor(QWidget *parent,
                                                        const QStyleOptionViewItem &option,
                                                        const QModelIndex &index) const
{
  Q_UNUSED(index)
  Q_UNUSED(option)
  QSpinBox *editor = new QSpinBox(parent);
  editor->setFrame(false);
  editor->setMinimum(0);
  editor->setMaximum(65535);
  return editor;
}

//------------------------------------------------------------------------------

void ProductTablePriceSpinBoxDelegate::setEditorData(QWidget *editor,
                                                     const QModelIndex &index) const
{
  int value = index.model()->data(index, Qt::EditRole).toInt();

  QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
  spinBox->setValue(value);
}

//------------------------------------------------------------------------------

void ProductTablePriceSpinBoxDelegate::setModelData(QWidget *editor,
                                                    QAbstractItemModel *model,
                                                    const QModelIndex &index) const
{
  QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
  spinBox->interpretText();
  int value = spinBox->value();

  model->setData(index, value, Qt::EditRole);
}

//------------------------------------------------------------------------------

void ProductTablePriceSpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                                            const QStyleOptionViewItem &option,
                                                            const QModelIndex &index) const
{
  Q_UNUSED(index)
  editor->setGeometry(option.rect);
}
