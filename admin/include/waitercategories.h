#ifndef WAITERCATEGORIES_H
#define WAITERCATEGORIES_H

//------------------------------------------------------------------------------

#include <QDialog>
#include <ui_waitercategories.h>

//------------------------------------------------------------------------------

#include "productcontainer.h"
#include "client.h"

//------------------------------------------------------------------------------

/**
 * @brief
 *
 */
class WaiterCategories : public QDialog {
  Q_OBJECT
public:
  /**
   * @brief
   *
   * @param parent
   */
  explicit WaiterCategories(QWidget *parent = nullptr);
  /**
   * @brief
   *
   * @param container
   * @param waiter
   * @param parent
   */
  explicit WaiterCategories(rotable::ProductContainer *container, rotable::Waiter *waiter, QWidget *parent = nullptr);
  /**
   * @brief
   *
   */
  ~WaiterCategories();
private:
  void loadListView();
  /* UI object */
  UiWaiter::Dialog *_ui;
  rotable::ProductContainer *_container;
  rotable::Waiter *_waiter;
};

#endif // WAITERCATEGORIES_H
