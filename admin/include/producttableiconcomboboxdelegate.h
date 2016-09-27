#ifndef PRODUCTTABLEICONCOMBOBOXDELEGATE_H
#define PRODUCTTABLEICONCOMBOBOXDELEGATE_H

//------------------------------------------------------------------------------

#include <QItemDelegate>

//------------------------------------------------------------------------------

namespace rotable {
  //class ProductContainer;
  //class ImageContainer;
  //class Product;
}

class QModelIndex;
class QWidget;
class QVariant;

//------------------------------------------------------------------------------

/**
 * The ProductTableIconComboboxDelegate class is a ComboBox for the product
 * table and allows the user to easily change a products icon.
 */
class ProductTableIconComboboxDelegate : public QItemDelegate
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param parent          parent object
   */
  ProductTableIconComboboxDelegate(QObject *parent = 0);

  /**
   * Returns the widget used to edit the item specified by index for editing.
   * The parent widget and style option are used to control how the editor widget appears.
   *
   * @param parent          parent widget
   * @param option          style options
   * @param index           item index
   * @return                created editor
   */
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;

  /**
   * Sets the data to be displayed and edited by the editor from the data model
   * item specified by the model index.
   *
   * @param editor          editor
   * @param index           item index
   */
  void setEditorData(QWidget *editor, const QModelIndex &index) const;

  /**
   * Gets data from the editor widget and stores it in the specified model at
   * the item index.
   *
   * @param editor          editor
   * @param model
   * @param index           item index
   */
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

  /**
   * Updates the editor for the item specified by index according to the style
   * option given.
   *
   * @param editor          editor
   * @param option          style option
   * @param index           item index
   */
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const;

  /**
   * Renders the delegate using the given painter and style option for the item
   * specified by index.
   *
   * @param painter         painter
   * @param option          style option
   * @param index           item index
   */
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;

private:
  QStringList _items; /**< TODO: describe */
}; // class ProductTableIconComboboxDelegate

//------------------------------------------------------------------------------

#endif // PRODUCTTABLEICONCOMBOBOXDELEGATE_H
