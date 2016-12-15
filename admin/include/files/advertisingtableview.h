#ifndef ADVERTISINGTABLEVIEW_H
#define ADVERTISINGTABLEVIEW_H

//------------------------------------------------------------------------------

#include <QTableView>

//------------------------------------------------------------------------------


class AdvertisingTableView : public QTableView
{
    Q_OBJECT
public:
    explicit AdvertisingTableView(QWidget *parent = 0);

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
};

#endif // ADVERTISINGLISTVIEW_H
