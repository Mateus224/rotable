#ifndef CONTROLLER_H
#define CONTROLLER_H

//------------------------------------------------------------------------------

#include "executor.h"
#include "productcontainer.h"
#include "filecontainer/imagecontainer.h"
#include "usertablemodel.h"
#include "filecontainer/advertisingcontainer.h"
#include "files/advertisingtablemodel.h"
#include "files/advertisingtableview.h"


#include <QObject>
#include <QMap>

//------------------------------------------------------------------------------

namespace rotable {
  class ProductCategory;
  class Product;
}

class CategoryListModel;
class ProductTableModel;
class MainWindow;

//------------------------------------------------------------------------------

/**
 * Controller class (connects signals and slots, contains data)
 */
class Controller : public QObject
{
  Q_OBJECT

public:
  /**
   * Constructor.
   *
   * @param mainwindow      mainwindow object
   * @param configFilePath  path to config file
   */
  Controller(MainWindow* mainwindow, const QString& configFilePath);

  /**
   * Connect GUI signals and slots.
   */
  void connect_signals();

private:
  /* MainWindow */
  MainWindow* _mainwindow;

  /* Executor object */
  Executor _executor;

  /* Product container */
  rotable::ProductContainer _products;

  /* Images */
  rotable::ImageContainer _images;

  /* Users */
  rotable::UserContainter _users;

  /* Model for category list view */
  CategoryListModel* _categoryListModel;

  /* Model for product table view */
  ProductTableModel* _productTableModel;
\
  /* Model for user table view */
  UserTableModel* _userTableModel;

  /*Model for Advertising Videos*/
  AdvertisingTableModel* _advertisingTableModel;

  /*Files*/
  rotable::AdvertisingContainer _files;


  AdvertisingTableView _advertisingTableView;

}; // class Controller

//------------------------------------------------------------------------------

#endif // CONTROLLER_H
