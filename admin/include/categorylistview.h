#ifndef CATEGORYLISTVIEW_H
#define CATEGORYLISTVIEW_H

//------------------------------------------------------------------------------

#include <QListView>

//------------------------------------------------------------------------------

class QAbstractItemModel;

//------------------------------------------------------------------------------

/**
 * List view for categories
 */
class CategoryListView : public QListView
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param parent            widget
   */
  explicit CategoryListView(QWidget *parent = 0);

signals:
  /**
   * The current selection has been changed.
   *
   * @param id                selected category id
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
}; // class CategoryListView

//------------------------------------------------------------------------------

#endif // CATEGORYLISTVIEW_H
