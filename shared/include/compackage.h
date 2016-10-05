#ifndef ROTABLE_COMPACKAGE_H
#define ROTABLE_COMPACKAGE_H

//------------------------------------------------------------------------------

#ifndef QBYTEARRAY_H
#include <QByteArray>
#endif

#ifndef QJSONOBJECT_H
#include <QJsonObject>
#endif

#ifndef QJSONDOCUMENT_H
#include <QJsonDocument>
#endif

#include <logmanager.h>
#include <QDebug>
#include <QJsonArray>
#include <QStringList>

//------------------------------------------------------------------------------

namespace rotable {
  class ComPackage;
  class ComPackageConnectionRequest;
  class ComPackageConnectionAccept;
  class ComPackageDataRequest;
  class ComPackageDataReturn;
  class ComPackageDataChanged;
  class ComPackageDataSet;
  class ComPackageReject;
  class ComPackageCommand;
  class ComPackageSendOrder;
  class ComPackageLogin;
  class ComPackageWaiterNeed;
  class ComPackageMessage;
  class ComPackageSendFile;
}

//------------------------------------------------------------------------------

/**
 * The ComPackage class encapsulates a client/server communication package.
 * This is just the base class.
 */
class rotable::ComPackage
{
public:
  /**
   * Enumeration of package types.
   */
  enum Type {
    /* Client wants to connect */
    ConnectionRequest = 0,

    /* Connection of client was accepted */
    ConnectionAccept,

    /* Client requests data */
    DataRequest,

    /* Requested data is sent */
    DataReturn,

    /* Informing a client that data has changed */
    DataChanged,

    /* Client wants to set data */
    DataSet,

    /* A package has been rejected */
    Reject,

    /* Client sends a command */
    Command,

    /* Change waiter needed status on table*/
    WaiterNeed,

    /* Message system */
    Message,

    /*Package for sending Files*/
    File
  };

  /**
   * Enumeration of data request category types.
   */
  enum DataRequestCategory {
    /* Client requests an image */
    RequestImage = 0,

    /* Request list of category ids */
    RequestCategoryIds,

    /* Request list of product ids for a given category id */
    RequestProductIds,

    /* Request category data from a given category id */
    RequestCategory,

    /* Request product data from a given product id */
    RequestProduct,

    /* Request order data from a given order id */
    RequestOrder,

    /* Request waiter data from a given product id or when login*/
    RequestWaiter,

    /* Request orderIds*/
    RequestOrderIds,

    /* Request list of connected table ids */
    RequestTableIds,

    /* Request table data from a table id */
    RequestTable,

    /* Request list order on table*/
    RequestOrderOnTable,

    /* Request config on server*/
    RequestConfig,

    /* Request licence info from server*/
    RequestLicence,

    /* Request income from certain day */
    RequestIncome
  };

  /**
   * Enumeration of data set category types.
   */
  enum DataSetCategory {
    /* Set/Update an image */
    SetImage = 0,

    /* Set/Update a product category */
    SetCategory,

    /* Set/Update a product */
    SetProduct,

    /* Set/Update order*/
    SetOrder,

    /* Set licence */
    SetLicence,

    /*Set Video*/
    SetVideo

  };

  /**
   * Enumeration of commands a client can send to the server.
   */
  enum CommandType {
    /* Reset the whole database */
    ResetDatabase = 0,

    /* Delete a product category from the database */
    DeleteCategory,

    /* Delete a product from the database */
    DeleteProduct,

    /* Select licence path */
    SetLicencePath,

    /* Select video path*/
    SetVideoPath
  };

  /**
   * Enumeration of account type client can login.
   */
  enum LoginType {
    /* Waiter account type */
    WaiterAccount = 0,
    TableAccount,
    AdminAccount
  };


  enum FileUsage {

      /*File for Advertising on clients*/
      AdvertisingVideo,

      /*File for Advertising on clients*/
      AdvertisingPicture,

      /*Icons which are send to clients*/
      CatergoryIcon,

      /*Icons which are send to clients*/
      ProductIcone,

      /*Files for checking the License*/
      //LicenseFiles
  };

  /**
   * Create a package object from a byte array.
   * (e.g. received via tcp)
   *
   * @param doc               JSON document
   * @return                  package object or 0 on error
   */
  static ComPackage* fromJson(const QJsonDocument& doc);

  /**
   * Default constructor.
   */
  ComPackage();

  /**
   * Get package type.
   *
   * @return                  package type
   */
  virtual Type type() const = 0;

  /**
   * Get package id.
   *
   * @return                  package id
   */
  inline const QString id() const { return _id; }

  /**
   * Convert this package into a byte array.
   *
   * @return                  byte array
   */
  virtual QByteArray toByteArray() const = 0;

protected:
  /**
   * Add data of this base package to given JSON object.
   *
   * @param o                 JSON object
   */
  void addData(QJsonObject& o) const;

private:
  /* Package id */
  QString _id;
}; // class ComPackage

//------------------------------------------------------------------------------

/**
 * This package is used by a client to request a new connection.
 */
class rotable::ComPackageConnectionRequest : public ComPackage
{
  friend class ComPackage;

public:
  /**
   * Default constructor
   */
  ComPackageConnectionRequest();

  inline const QString& clientName() const { return _clientName; }
  inline const QString& clientPass() const { return _clientPass; }
  inline const int& clientType() const { return _clientType; }
  inline Type type() const { return ConnectionRequest; }

  QByteArray toByteArray() const;

  inline void setClientName(const QString& clientName) { _clientName = clientName; }
  inline void setClientPass(const QString& clientPass) { _clientPass = clientPass; }
  inline void setClientType(const int &clientType) { _clientType = clientType; }

private:
  /* Name of the client */
  QString _clientName;

  /* Password of the client */
  QString _clientPass;

  /*Type of client, Table, Waiter, Admin, etc.*/
  int _clientType;
}; // class ComPackageConnectionRequest

//------------------------------------------------------------------------------

class rotable::ComPackageConnectionAccept : public ComPackage
{
  friend class ComPackage;

public:
  /**
   * Default constructor
   */
  ComPackageConnectionAccept();

  inline Type type() const { return ConnectionAccept; }

  QByteArray toByteArray() const;
}; // class ComPackageConnectionAccept

//------------------------------------------------------------------------------

class rotable::ComPackageDataRequest : public ComPackage
{
  friend class ComPackage;

public:
  /**
   * Default constructor
   */
  ComPackageDataRequest();

  inline Type type() const { return DataRequest; }

  inline int dataCategory() const { return _dataCategory; }
  inline const QString& dataName() const { return _dataName; }

  inline void setDataCategory(DataRequestCategory dataCategory) { _dataCategory = dataCategory; }
  inline void setDataName(const QString& dataName) { _dataName = dataName; }

  QByteArray toByteArray() const;

private:
  int _dataCategory;
  int _databaseRequest;
  QString _dataName;
}; // class ComPackageConnectionRequest

//------------------------------------------------------------------------------

class rotable::ComPackageDataReturn : public ComPackage
{
  friend class ComPackage;

public:
  /**
   * Default constructor
   */
  ComPackageDataReturn();

  /**
   * Constructor used to create a return package from a request.
   *
   * @param r           request package
   * @param data        returned data
   */
  ComPackageDataReturn(const ComPackageDataRequest& r, const QJsonValue& data);

  inline Type type() const { return DataReturn; }

  inline int dataCategory() const { return _dataCategory; }
  inline const QString& dataName() const { return _dataName; }
  inline const QJsonValue& data() const { return _data; }
  inline const QString& originId() const { return _originId; }

  inline void setDataCategory(DataRequestCategory dataCategory) { _dataCategory = dataCategory; }
  inline void setDataName(const QString& dataName) { _dataName = dataName; }
  inline void setData(const QJsonValue& data) { _data = data; }

  QByteArray toByteArray() const;

  /**
   * Create human readable string of JSON data.
   *
   * @return            string of JSON data in package
   */
  QString toString() const;

private:
  int _dataCategory;
  QString _dataName;
  QJsonValue _data;

  /* ID of the package that requested the data */
  QString _originId;
}; // class ComPackageDataReturn

//------------------------------------------------------------------------------

class rotable::ComPackageDataChanged : public ComPackage
{
  friend class ComPackage;

public:
  /**
   * Default constructor
   */
  ComPackageDataChanged();

  inline Type type() const { return DataChanged; }

  inline int dataCategory() const { return _dataCategory; }
  inline const QString& dataName() const { return _dataName; }

  inline void setDataCategory(DataRequestCategory dataCategory) { _dataCategory = dataCategory; }
  inline void setDataName(const QString& dataName) { _dataName = dataName; }

  QByteArray toByteArray() const;

private:
  int _dataCategory;
  QString _dataName;
}; // class ComPackageDataChanged

//------------------------------------------------------------------------------

class rotable::ComPackageDataSet : public ComPackage
{
  friend class ComPackage;

public:
  /**
   * Default constructor
   */
  ComPackageDataSet();

  inline Type type() const { return DataSet; }

  inline int dataCategory() const { return _dataCategory; }
  inline const QString& dataName() const { return _dataName; }
  inline const QJsonValue& data() const { return _data; }

  inline void setDataCategory(DataSetCategory dataCategory) { _dataCategory = dataCategory; }
  inline void setDataName(const QString& dataName) { _dataName = dataName; }
  inline void setData(const QJsonValue& data) { _data = data; }

  QByteArray toByteArray() const;

private:
  int _dataCategory;
  QString _dataName;
  QJsonValue _data;
}; // class ComPackageDataSet

//------------------------------------------------------------------------------

class rotable::ComPackageReject : public ComPackage
{
  friend class ComPackage;

public:
  /**
   * Default constrcutor
   */
  ComPackageReject();

  /**
   * Constrcutor
   *
   * @param originId        id of rejected package
   */
  ComPackageReject(const QString& originId);

  inline Type type() const { return Reject; }

  inline const QString& originId() const { return _originId; }

  QByteArray toByteArray() const;

private:
  /* ID of the package that has been rejected */
  QString _originId;
}; // class ComPackageReject

//------------------------------------------------------------------------------

/**
 * The command package can be user to send special commands to the server.
 */
class rotable::ComPackageCommand : public ComPackage
{
  friend class ComPackage;

public:
  /**
   * Default constrcutor
   */
  ComPackageCommand();

  inline Type type() const { return Command; }

  /**
   * Get command type.
   *
   * @return              command type
   */
  inline int commandType() const { return _commandType; }
  inline const QJsonValue& data() const { return _data; }

  /**
   * Set command type.
   *
   * @param commandType   command type
   */
  inline void setCommandType(CommandType commandType) { _commandType = commandType; }
  inline void setData(const QJsonValue& data) { _data = data; }

  QByteArray toByteArray() const;

private:
  /* Command type */
  int _commandType;

  /* Additional data */
  QJsonValue _data;
}; // class ComPackageReject

//------------------------------------------------------------------------------

/**
 * The waiter request package change waiter need on table.
 */
class rotable::ComPackageWaiterNeed : public ComPackage
{
  friend class ComPackage;

public:
  /**
   * Default constrcutor
   */
  ComPackageWaiterNeed(): ComPackage(), _tableId(-1) {}

  inline Type type() const { return WaiterNeed; }

  /**
   * Get need.
   *
   * @return              true if waiter is need
   */
  inline bool need() const { return _need; }

  /**
   * Get table id
   *
   * @return              table id
   */
  inline int tableId() const { return _tableId; }

  /**
   * Set need.
   *
   * @param need          need
   */
  inline void setNeed(const bool &need) { _need = need; }

  inline void setTableId(const int &id) { _tableId = id; }

  QByteArray toByteArray() const Q_DECL_OVERRIDE;

private:
  /* Command type */
  bool _need;
  int _tableId;

}; // class ComPackageWaiterNeed

//------------------------------------------------------------------------------

class rotable::ComPackageMessage : public ComPackage
{
  friend class ComPackage;
public:

  /**
   * Default constructor
   */
  ComPackageMessage();

  inline Type type() const { return Message; }

  inline int msgType() const { return _msgType; }
  inline void setMsgType(const int &type) { _msgType = type; }

  inline QString message() const {return _msg; }
  inline void setMessage(const QString &message) { _msg = message; }

  QByteArray toByteArray() const Q_DECL_OVERRIDE;

private:
    int _msgType;
    QString _msg;
};

//------------------------------------------------------------------------------
class rotable::ComPackageSendFile : public ComPackage
{
  friend class ComPackage;
public:

  /**
   * Default constructor
   */
  ComPackageSendFile();

  inline Type type() const { return File; }

  /**
   * 1= Advertising Video
   * 2= Advertising Picture
   * 3= Category Icon
   * 4= Product Icon
   */
  inline void setFileUsage(FileUsage fileUsage){_fileUsage=fileUsage;}
  inline int getFileUsage(){return _fileUsage;}

  inline void setFiles(const QStringList &files) { _files = files; }
  inline QStringList getFiles()const{return _files;}

  inline void setFileNames(const QStringList &fileNames){_fileNames=fileNames;}
  inline QStringList getFileNames()const{return _fileNames;}

  inline void byteArrayToBase64(const QByteArray &ba){_files.append(ba.toBase64(QByteArray::Base64UrlEncoding));}\
  QString base64ToQString(QString encodeFile);

  QByteArray toByteArray() const Q_DECL_OVERRIDE;  //for what is this

private:
    int _fileUsage;

    QStringList _files;

    QStringList _fileNames;
};

//------------------------------------------------------------------------------
#endif // ROTABLE_COMPACKAGE_H
