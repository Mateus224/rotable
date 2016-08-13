#ifndef PRODUCTTABLEVIEW_H
#define PRODUCTTABLEVIEW_H

//------------------------------------------------------------------------------

#include <QTableView>

//------------------------------------------------------------------------------

class ProductTableIconComboboxDelegate;
class ProductTablePriceSpinBoxDelegate;

//------------------------------------------------------------------------------

/**
 * @brief
 *
 */
class ProductTableView : public QTableView
{
  Q_OBJECT

public:
  /**
   * Constructor.
   *
   * @param parent            parent widget
   */
  explicit ProductTableView(QWidget *parent = 0);

signals:
  /**
   * The current selection has been changed.
   *
   * @param id                selected product id
   */
  void selectionChanged(int id);

protected slots:
  /**
   * This slot is called when the selection is changed. The previous selection
   * (which may be empty), is specified by deselected, and the new selection by
   * selected.
   *
   * @param selected          new selection
   * @param deselected        previous selection
   */
  void selectionChanged(const QItemSelection & selected,
                        const QItemSelection & deselected);

private:
  ProductTableIconComboboxDelegate* _comboBoxDelegate; /**< TODO: describe */
  ProductTablePriceSpinBoxDelegate* _spinBoxDelegate; /**< TODO: describe */
}; // class ProductTableView

//------------------------------------------------------------------------------

#endif // PRODUCTTABLEVIEW_H
