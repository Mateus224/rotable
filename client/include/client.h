#ifndef ROTABLE_CLIENT_H
#define ROTABLE_CLIENT_H

//------------------------------------------------------------------------------

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QSTRING_H
#include <QString>
#endif

#ifndef QTIMER_H
#include <QTimer>
#endif

#include "configclient.h"
#include "tcpclient.h"
#include "sensors.h"
#include "productorder.h"
#include "productorderlistmodel.h"
#include "callwaiter.h"
#include "messageconnector.h"
#include "queue.h"
#include "filecontainer/advertisingvideo.h"
#include "playadvertising.h"



//------------------------------------------------------------------------------

namespace rotable {
  class Client;
  class ImageProvider;
  class ComPackage;
  class ComPackageDataReturn;
  class ComPackageReject;
  class ComPackageDataRequest;
  class ComPackageDataChanged;
  class ProductContainer;
  class ProductOrder;
  class PlayAdvertising;
}

class ProductOrderListModel;
class QAbstractListModel;
class ProductListModel;

//------------------------------------------------------------------------------

/**
 * Client logic
 */
class rotable::Client : public QObject
{
  Q_OBJECT

  //Q_PROPERTY(QString test READ test WRITE settest NOTIFY testChanged)

  Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
  Q_PROPERTY(int currentCategoryId READ currentCategoryId WRITE setCurrentCategoryId NOTIFY currentCategoryIdChanged)
  Q_PROPERTY(QString currentCategoryName READ currentCategoryName NOTIFY currentCategoryIdChanged)

  Q_PROPERTY(int screenRotation READ screenRotation NOTIFY rotationChanged)
  Q_PROPERTY(bool contact READ contact NOTIFY contactChanged)
  Q_PROPERTY(int device_ READ device_() )
  Q_PROPERTY(bool debug READ debug NOTIFY debugChanged)

public:
  /**
   * Constructor
   *
   * @param configFilePath      path to config file
   * @param parent              parent object
   */
  Client(const QString& configFilePath = QString("config.ini"),
         QObject *parent = 0);

  /**
   * Destructor
   */
  ~Client();

  /**
   * Startup client (connect to server).
   *
   * @return                false on critical error
   */
  bool startup();

  /**
   * Get a category list model.
   *
   * @return                category list model
   */
  QAbstractListModel *categoryListModel();

  /**
   * Get a product list model.
   *
   * @return                product list model
   */
  QAbstractListModel *productListModel();


    inline int device_(){return _device;}

  /**
   * Get screen rotation.
   *  0 ... 0°
   *  1 ... 90°
   *  2 ... 180°
   *  3 ... 270°
   *
   * @return                screen rotation
   */
  int screenRotation();

  /**
   * Get whether distance sensors have a contact.
   *
   * @return                true on contact
   */
  inline bool contact() const { return _sensors.contact(); }

  /**
   * Get current category id.
   *
   * @return                category id
   */
  inline int currentCategoryId() const { return _currentCategoryId; }

  /**
   * Get current GUI state.
   * (as defined in qml-files)
   *
   * @return                GUI state
   */
  inline const QString& state() const { return _state; }

  /**
   * Get name of current category.
   *
   * @return                category name
   */
  QString currentCategoryName() const;

  /**
   * Request an image from the server.
   * (listen to imageReceived for result)
   *
   * @param name        image name
   * @return            data request id
   */
  QString requestImage(const QString& name);

  /**
   * Set image provider.
   *
   * @param provider    new image provider
   */
  inline void setImageProvider(ImageProvider* provider) {
    _imageProvider = provider;
  }

  /**
   * Check whether client is still waiting for a data request to be
   * returned by the server.
   *
   * @param packageId         package id of data request
   * @return                  true if request is still pending
   */
  inline bool hasPackage(const QString& packageId) const {
    return _dataRequest.contains(packageId);
  }

  /**
   * Get whether this application has been build in debug mode.
   *
   * @return                  true on debug mode
   */
  inline bool debug() const {
#if defined(_DEBUG) || defined(DEBUG) || defined(QT_DEBUG)
    return true;
#else
    return false;
#endif
  }
public:
  /* Products */
  rotable::ProductContainer* _products;
  rotable::CallWaiter _callWaiter;
  rotable::Queue _queue;
  rotable::ProductOrder* _productOrder;  
  /* Table sensors */
  rotable::Sensors _sensors;
  int _device;

signals:
  /**
   * Current GUI state has changed.Sending to QML File.
   */
  void stateChanged();

  /**
   * Current category id has changed. Sending to QML File.
   */
  void currentCategoryIdChanged();

  /**
   * Screen rotation has changed.Sending to QML File. Sending to QML File.
   */
  void rotationChanged();

  /**
   * Contact sensor state has changed. Sending to QML File.
   */
  void contactChanged();

  /**
   * Debugging status of software has changed (probably never happens). Sending to QML File.
   */
  void debugChanged();

  /**
   * Recive new message
   */
  void reciveMessagePackage(ComPackageMessage *msgPcg);

public slots:
void payedSlot(int i){qDebug()<<i;}
  /**
   * Start reconnection with rotable-server.
   */
  void reconnect();

  /**
   * Slot to be called when connection to server is established.
   */
  void connected();

  /**
   * Slot to be called when connection to server has been lost.
   */
  void disconnected();

  /**
   * A package from the server has been received.
   *
   * @param package     package
   */
  void packageReceived(ComPackage* package);

  /**
   * A package has been rejected.
   *
   * @param rej        reject package
   */
  void rejected(ComPackageReject* rej);

  /**
   * Set current GUI state.
   *
   * @param state       new GUI state
   */
  void setState(const QString& state);

  /**
   * @brief requestMediaIds
   * request for all Media Ids from the server
   */
  void requestMediaIds();

  /**
   * Set current category id.
   *
   * @param id          new category id
   */
  void setCurrentCategoryId(int id);

  /**
   * Send order to server
   */
  void sendOrder();

  /**
   * Slot allow modules of client send package
   * @param package     package to send
   */
  void sendPackage(rotable::ComPackage *package);

  /**
   * Interpreting order status
   * @param msg
   * Method to recive Message with order send status
   * @param msg         message
   */
  void orderSendSuccesfull(rotable::Message *msg);

  /**
   * Order is invalid
   */

  void invalidOrder();
  /**
   * Method to recive Message with NeedWaiter send status
   *
   * @param msg         message
   */
  void needWaiterStatus(rotable::Message *msg);

  /**
   * Slot for recive order Queue
   * @param msg         Message
   */
  void orderQueue(rotable::Message *msg);

private:
  /**
   * Request all category ids.
   */
  void requestCategoryIds();

  /**
   * Request product ids of given category.
   * (result received in dataReturned())
   *
   * @param categoryId      id of category to request product ids from
   */
  void requestProductIds(int categoryId);

  /**
   * Request category information.
   * (result received in dataReturned())
   *
   * @param categoryId      category id
   */
  void requestCategory(int categoryId);

  /**
   * Request product information.
   * (result received in dataReturned())
   *
   * @param productId       product id
   */
  void requestProduct(int productId);

  /**
   * Handle data received from the server.
   *
   * @param ret         received data package
   */
  void dataReturned(ComPackageDataReturn* ret);

  /**
   * Handle data changed information from the server.
   *
   * @param package     received package
   */
  void dataChanged(rotable::ComPackageDataChanged* package);

  /**
   * @brief typeOfFileDestination is a funktion in which we are chacking the kind of sended file
   * @param package
   * @return
   */
  bool typeOfFileDestination(rotable::ComPackageSendFile* package);

  void requestAdvertising(int fileId);

  void prepareForPlayAdvertising();


  //----------------------------------------------------------------------------

  /* Configuration file access */
  ConfigClient _config;

  /* TCP-Socket object */
  TcpClient _tcp;

  QMap<QString, QImage> _images;

  /* Currently pending data requests */
  QMap<QString, ComPackageDataRequest*> _dataRequest;

  /* Whether this client has been accepted by the server */
  bool _accepted;

  /* Program state */
  QString _state;

  /* Timer for waiting before reconnect */
  QTimer _reconnectTimer;

  /* Whether the program is currently shutting */
  bool _stopping;

  /* Current category id */
  int _currentCategoryId;

  /* Table sensors */
  //rotable::Sensors _sensors;

  /*save the last direction from the sensor (for games)*/
  int _lastRotation;

  /* Product list model */
  ProductListModel* _productListModel;

//  ProductOrderListModel* _productorderlistmodel;

  /* Image provider */
  rotable::ImageProvider* _imageProvider;

  rotable::MessageConnector _connector;

  rotable::File *_file;

  rotable::AdvertisingVideo *_TmpAdvertisingVideo;

  rotable::AdvertisingVideo *_advertisingVideo;

  rotable::PlayAdvertising * _playA;

  int _numberOfMedias, _countIncomeMedias;



}; // class Client

//------------------------------------------------------------------------------

#endif // ROTABLE_CLIENT_H
