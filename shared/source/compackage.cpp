#include "private/precomp.h"

#include "compackage.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

struct TypeStr2Enum {
  QString name;
  ComPackage::Type type;
};

#define ROTABLE_PACKAGE_COMMAND_CONNECTION_REQUEST_STR      QString("CR")
#define ROTABLE_PACKAGE_COMMAND_CONNECTION_ACCEPT_STR       QString("CA")
#define ROTABLE_PACKAGE_COMMAND_DATA_REQUEST_STR            QString("DR")
#define ROTABLE_PACKAGE_COMMAND_DATA_RETURN_STR             QString("DB")
#define ROTABLE_PACKAGE_COMMAND_DATA_CHANGED_STR            QString("DC")
#define ROTABLE_PACKAGE_COMMAND_DATA_SET_STR                QString("DS")
#define ROTABLE_PACKAGE_COMMAND_REJECT_STR                  QString("RJ")
#define ROTABLE_PACKAGE_COMMAND_COMMAND_STR                 QString("CC")
#define ROTABLE_PACKAGE_COMMAND_SEND_ORDER_STR              QString("SO")
#define ROTABLE_PACKAGE_COMMAND_NEED_STR                    QString("NE")
#define ROTABLE_PACKAGE_COMMAND_MESSAGE_STR                 QString("ME")
#define ROTABLE_PACKAGE_COMMAND_SEND_FILE                   QString("SF")

static const int S_types_count = 11;
static const TypeStr2Enum S_types[S_types_count] = {
  { ROTABLE_PACKAGE_COMMAND_CONNECTION_REQUEST_STR, ComPackage::ConnectionRequest },
  { ROTABLE_PACKAGE_COMMAND_CONNECTION_ACCEPT_STR, ComPackage::ConnectionAccept },
  { ROTABLE_PACKAGE_COMMAND_DATA_REQUEST_STR, ComPackage::DataRequest },
  { ROTABLE_PACKAGE_COMMAND_DATA_RETURN_STR, ComPackage::DataReturn },
  { ROTABLE_PACKAGE_COMMAND_DATA_CHANGED_STR, ComPackage::DataChanged },
  { ROTABLE_PACKAGE_COMMAND_DATA_SET_STR, ComPackage::DataSet },
  { ROTABLE_PACKAGE_COMMAND_REJECT_STR, ComPackage::Reject },
  { ROTABLE_PACKAGE_COMMAND_COMMAND_STR, ComPackage::Command },
  { ROTABLE_PACKAGE_COMMAND_NEED_STR, ComPackage::WaiterNeed },
  { ROTABLE_PACKAGE_COMMAND_MESSAGE_STR, ComPackage::Message},
  { ROTABLE_PACKAGE_COMMAND_SEND_FILE, ComPackage::File}
};

//------------------------------------------------------------------------------

#define ROTABLE_PACKAGE_COMMAND_STR                         QString("C")
#define ROTABLE_PACKAGE_CLIENT_NAME_STR                     QString("CN")
#define ROTABLE_PACKAGE_CLIENT_PASS_STR                     QString("CP")
#define ROTABLE_PACKAGE_CLIENT_TYPE_STR                     QString("CT")
#define ROTABLE_PACKAGE_DATA_CATEGORY_STR                   QString("DC")
#define ROTABLE_PACKAGE_DATA_NAME_STR                       QString("DN")
#define ROTABLE_PACKAGE_DATA_STR                            QString("D")
#define ROTABLE_PACKAGE_ID_STR                              QString("ID")
#define ROTABLE_PACKAGE_ORIGIN_ID_STR                       QString("OI")
#define ROTABLE_PACKAGE_COMMAND_TYPE_STR                    QString("CT")
#define ROTABLE_PACKAGE_TIME_CREATED_STR                    QString("TC")
#define ROTABLE_PACKAGE_LAST_CHANGED_STR                    QString("LC")
#define ROTABLE_PACKAGE_ORDER_STATE_STR                     QString("OS")
#define ROTABLE_PACKAGE_NEED_NEED_STR                       QString("NN")
#define ROTABLE_PACKAGE_NEED_TABLE_STR                      QString("NY")
#define ROTABLE_PACKAGE_MESSAGE_TYPE_STR                    QString("MT")
#define ROTABLE_PACKAGE_MESSAGE_MESSAGE_STR                 QString("MM")
#define ROTABLE_PACKAGE_FILE_INFORMATION_ARRAY              QString("FI")
#define ROTABLE_PACKAGE_FILE_NAMES                          QString("FN")
#define ROTABLE_PACKAGE_FILE_FILE                           QString("FF")
#define ROTABLE_PACKAGE_FILE_USAGE                          QString("FU")


//------------------------------------------------------------------------------

ComPackage* ComPackage::fromJson(const QJsonDocument& doc)
{
  if (doc.isNull()) {
    qDebug() << "WARNING: invalid JSON data.";
    return 0;
  }

  QJsonObject o = doc.object();

  if (o.isEmpty()) {
    qDebug() << "WARNING: empty JSON data.";
    return 0;
  }

  if (!o.contains(ROTABLE_PACKAGE_COMMAND_STR)) {
    qWarning() << "ERROR: no command specified!";
    return 0;
  }

  if (!o.contains(ROTABLE_PACKAGE_ID_STR)) {
    qWarning() << "ERROR: no package id specified!";
    return 0;
  }

  QString command = o[ROTABLE_PACKAGE_COMMAND_STR].toString();

  bool unknownCommand = true;
  Type t;
  for (int i = 0; i < S_types_count && unknownCommand; ++i) {
    if (S_types[i].name == command) {
      t = S_types[i].type;
      unknownCommand = false;
    }
  }

  if (unknownCommand) {
    qWarning() << QString("ERROR: unknown command: %1!").arg(command);
    return 0;
  }

  ComPackage* ret = 0;

  switch (t) {
  case DataRequest:
  {
    if (!o.contains(ROTABLE_PACKAGE_DATA_CATEGORY_STR)) {
      qWarning() << "ERROR: no data category specified!";
      return 0;
    }
    if (!o.contains(ROTABLE_PACKAGE_DATA_NAME_STR)) {
      qWarning() << "ERROR: no data name specified!";
      return 0;
    }

    ComPackageDataRequest* p = new ComPackageDataRequest();
    p->_dataCategory = o[ROTABLE_PACKAGE_DATA_CATEGORY_STR].toInt();
    p->_dataName = o[ROTABLE_PACKAGE_DATA_NAME_STR].toString();
    ret = p;
  } break;
  case DataReturn:
  {
    if (!o.contains(ROTABLE_PACKAGE_DATA_CATEGORY_STR)) {
      qWarning() << "ERROR: no data category specified!";
      return 0;
    }
    if (!o.contains(ROTABLE_PACKAGE_DATA_NAME_STR)) {
      qWarning() << "ERROR: no data name specified!";
      return 0;
    }
    if (!o.contains(ROTABLE_PACKAGE_DATA_STR)) {
      qWarning() << "ERROR: no data specified!";
      return 0;
    }
    if (!o.contains(ROTABLE_PACKAGE_ORIGIN_ID_STR)) {
      qWarning() << "ERROR: no origin id specified!";
      return 0;
    }

    ComPackageDataReturn* p = new ComPackageDataReturn();
    p->_dataCategory = o[ROTABLE_PACKAGE_DATA_CATEGORY_STR].toInt();
    p->_dataName = o[ROTABLE_PACKAGE_DATA_NAME_STR].toString();
    p->_data = o.value(ROTABLE_PACKAGE_DATA_STR);
    p->_originId = o[ROTABLE_PACKAGE_ORIGIN_ID_STR].toString();

    ret = p;
  } break;
  case DataSet:
  {
    if (!o.contains(ROTABLE_PACKAGE_DATA_CATEGORY_STR)) {
      qWarning() << "ERROR: no data category specified!";
      return 0;
    }
    if (!o.contains(ROTABLE_PACKAGE_DATA_NAME_STR)) {
      qWarning() << "ERROR: no data name specified!";
      return 0;
    }
    if (!o.contains(ROTABLE_PACKAGE_DATA_STR)) {
      qWarning() << "ERROR: no data specified!";
      return 0;
    }

    ComPackageDataSet* p = new ComPackageDataSet();
    p->_dataCategory = o[ROTABLE_PACKAGE_DATA_CATEGORY_STR].toInt();
    p->_dataName = o[ROTABLE_PACKAGE_DATA_NAME_STR].toString();
    p->_data = o[ROTABLE_PACKAGE_DATA_STR];

    ret = p;
  } break;
  case Reject:
  {
    if (!o.contains(ROTABLE_PACKAGE_ORIGIN_ID_STR)) {
      qWarning() << "ERROR: no origin id specified!";
      return 0;
    }

    ComPackageReject* p = new ComPackageReject();
    p->_originId = o[ROTABLE_PACKAGE_ORIGIN_ID_STR].toString();

    ret = p;
  } break;
  case DataChanged:
  {
    if (!o.contains(ROTABLE_PACKAGE_DATA_CATEGORY_STR)) {
      qWarning() << "ERROR: no data category specified!";
      return 0;
    }
    if (!o.contains(ROTABLE_PACKAGE_DATA_NAME_STR)) {
      qWarning() << "ERROR: no data name specified!";
      return 0;
    }

    ComPackageDataChanged* p = new ComPackageDataChanged();
    p->_dataCategory = o[ROTABLE_PACKAGE_DATA_CATEGORY_STR].toInt();
    p->_dataName = o[ROTABLE_PACKAGE_DATA_NAME_STR].toString();

    ret = p;
  } break;
  case ConnectionRequest:
  {
    if (!o.contains(ROTABLE_PACKAGE_CLIENT_NAME_STR)) {
      qWarning() << "ERROR: no client name specified!";
      return 0;
    }
    // Password is optional...

    ComPackageConnectionRequest* p = new ComPackageConnectionRequest();
    p->_clientName = o[ROTABLE_PACKAGE_CLIENT_NAME_STR].toString();
    p->_clientPass = o[ROTABLE_PACKAGE_CLIENT_PASS_STR].toString();
    p->_clientType = o[ROTABLE_PACKAGE_CLIENT_TYPE_STR].toInt();
    ret = p;
  } break;
  case ConnectionAccept:
  {
    ret = new ComPackageConnectionAccept();
  } break;
  case Command:
  {
    if (!o.contains(ROTABLE_PACKAGE_COMMAND_TYPE_STR)) {
      qWarning() << "ERROR: no command type specified!";
      return 0;
    }
    if (!o.contains(ROTABLE_PACKAGE_DATA_STR)) {
      qWarning() << "ERROR: no data specified!";
      return 0;
    }

    ComPackageCommand* p = new ComPackageCommand();
    p->_commandType = o[ROTABLE_PACKAGE_COMMAND_TYPE_STR].toInt();
    p->_data = o.value(ROTABLE_PACKAGE_DATA_STR);

    ret = p;
  } break;
  case WaiterNeed:{
    ComPackageWaiterNeed* p = new ComPackageWaiterNeed();
    p->_need = o[ROTABLE_PACKAGE_NEED_NEED_STR].toBool();
    p->_tableId = o[ROTABLE_PACKAGE_NEED_TABLE_STR].toInt();

    ret = p;
  } break;
  case Message:{
    ComPackageMessage* p = new ComPackageMessage();
    p->_msgType = o[ROTABLE_PACKAGE_MESSAGE_TYPE_STR].toInt();
    p->_msg = o[ROTABLE_PACKAGE_MESSAGE_MESSAGE_STR].toString();

    ret = p;
  } break;
  case File:{
    ComPackageSendFile* p=new ComPackageSendFile();
    p->_fileUsage=o[ROTABLE_PACKAGE_FILE_USAGE].toInt();
    QJsonArray jsonFileArray= o[ROTABLE_PACKAGE_FILE_INFORMATION_ARRAY].toArray();
    for(auto&& item: jsonFileArray)
    {
        const QJsonObject& so= item.toObject();
        p->_fileNames.append(so[ROTABLE_PACKAGE_FILE_NAMES].toString());
        //p->_files.append(so[ROTABLE_PACKAGE_FILE_FILE].toString());
        p->_files.append(p->base64ToQString(so[ROTABLE_PACKAGE_FILE_FILE].toString()));
    }
    if(p->_fileUsage > 0)
      for(auto file: p->_files)
        LogManager::getInstance()->logInfo(file);

    ret=p;  
  } break;
  default:
    qDebug("This should never ever happen (above switch is incomplete)!");
    return 0;
  }

  ret->_id = o[ROTABLE_PACKAGE_ID_STR].toString();

  return ret;
}

//------------------------------------------------------------------------------

ComPackage::ComPackage()
{
  // Create a random package id
  union ConvertInt2Qint64 {
    int i32[2];
    qint64 i64;
  } conv;

  conv.i32[0] = qrand();
  conv.i32[1] = qrand();

  _id = QString("%1").arg(conv.i64);
}

//------------------------------------------------------------------------------

void ComPackage::addData(QJsonObject& o) const
{
  o[ROTABLE_PACKAGE_ID_STR] = _id;
}

//------------------------------------------------------------------------------

ComPackageConnectionRequest::ComPackageConnectionRequest()
  : ComPackage()
{

}

//------------------------------------------------------------------------------

QByteArray ComPackageConnectionRequest::toByteArray() const
{
  QJsonObject o;
  addData(o);
  o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_CONNECTION_REQUEST_STR;
  o[ROTABLE_PACKAGE_CLIENT_NAME_STR] = _clientName;
  o[ROTABLE_PACKAGE_CLIENT_PASS_STR] = _clientPass;
  o[ROTABLE_PACKAGE_CLIENT_TYPE_STR] = _clientType;
  return QJsonDocument(o).toBinaryData();
}

//------------------------------------------------------------------------------

ComPackageConnectionAccept::ComPackageConnectionAccept()
  : ComPackage()
{

}

//------------------------------------------------------------------------------

QByteArray ComPackageConnectionAccept::toByteArray() const
{
  QJsonObject o;
  addData(o);
  o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_CONNECTION_ACCEPT_STR;
  return QJsonDocument(o).toBinaryData();
}

//------------------------------------------------------------------------------


ComPackageDataRequest::ComPackageDataRequest()
  : ComPackage()
{

}

//------------------------------------------------------------------------------

QByteArray ComPackageDataRequest::toByteArray() const
{
  QJsonObject o;
  addData(o);
  o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_DATA_REQUEST_STR;
  o[ROTABLE_PACKAGE_DATA_CATEGORY_STR] = _dataCategory;
  o[ROTABLE_PACKAGE_DATA_NAME_STR] = _dataName;
  return QJsonDocument(o).toBinaryData();
}

//------------------------------------------------------------------------------

ComPackageDataReturn::ComPackageDataReturn()
  : ComPackage()
{

}

//------------------------------------------------------------------------------

ComPackageDataReturn::ComPackageDataReturn(const ComPackageDataRequest &r,
                                           const QJsonValue& data)
  : ComPackage(), _dataCategory(r.dataCategory()), _dataName(r.dataName()),
    _data(data), _originId(r.id())
{

}

//------------------------------------------------------------------------------

QByteArray ComPackageDataReturn::toByteArray() const
{
  QJsonObject o;
  addData(o);
  o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_DATA_RETURN_STR;
  o[ROTABLE_PACKAGE_DATA_CATEGORY_STR] = _dataCategory;
  o[ROTABLE_PACKAGE_DATA_NAME_STR] = _dataName;
  o[ROTABLE_PACKAGE_DATA_STR] = _data;
  o[ROTABLE_PACKAGE_ORIGIN_ID_STR] = _originId;

  return QJsonDocument(o).toBinaryData();
}

//------------------------------------------------------------------------------

QString ComPackageDataReturn::toString() const
{
  QJsonObject o;
  addData(o);
  o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_DATA_RETURN_STR;
  o[ROTABLE_PACKAGE_DATA_CATEGORY_STR] = _dataCategory;
  o[ROTABLE_PACKAGE_DATA_NAME_STR] = _dataName;
  o[ROTABLE_PACKAGE_DATA_STR] = _data;
  o[ROTABLE_PACKAGE_ORIGIN_ID_STR] = _originId;
  return QJsonDocument(o).toJson();
}

//------------------------------------------------------------------------------

ComPackageDataSet::ComPackageDataSet()
  : ComPackage()
{

}

//------------------------------------------------------------------------------

QByteArray ComPackageDataSet::toByteArray() const
{
  QJsonObject o;
  addData(o);
  o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_DATA_SET_STR;
  o[ROTABLE_PACKAGE_DATA_CATEGORY_STR] = _dataCategory;
  o[ROTABLE_PACKAGE_DATA_NAME_STR] = _dataName;
  o[ROTABLE_PACKAGE_DATA_STR] = _data;
  return QJsonDocument(o).toBinaryData();
}

//------------------------------------------------------------------------------

ComPackageReject::ComPackageReject()
  : ComPackage()
{

}

//------------------------------------------------------------------------------

ComPackageReject::ComPackageReject(const QString& originId)
  : ComPackage(), _originId(originId)
{

}

//------------------------------------------------------------------------------

QByteArray ComPackageReject::toByteArray() const
{
  QJsonObject o;
  addData(o);
  o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_REJECT_STR;
  o[ROTABLE_PACKAGE_ORIGIN_ID_STR] = _originId;
  return QJsonDocument(o).toBinaryData();
}

//------------------------------------------------------------------------------

ComPackageDataChanged::ComPackageDataChanged()
  : ComPackage()
{

}

//------------------------------------------------------------------------------

QByteArray ComPackageDataChanged::toByteArray() const
{
  QJsonObject o;
  addData(o);
  o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_DATA_CHANGED_STR;
  o[ROTABLE_PACKAGE_DATA_CATEGORY_STR] = _dataCategory;
  o[ROTABLE_PACKAGE_DATA_NAME_STR] = _dataName;
  return QJsonDocument(o).toBinaryData();
}

//------------------------------------------------------------------------------

ComPackageCommand::ComPackageCommand()
  : ComPackage(), _commandType(-1)
{

}

//------------------------------------------------------------------------------

QByteArray ComPackageCommand::toByteArray() const
{
  QJsonObject o;
  addData(o);
  o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_COMMAND_STR;
  o[ROTABLE_PACKAGE_COMMAND_TYPE_STR] = _commandType;
  o[ROTABLE_PACKAGE_DATA_STR] = _data;
  return QJsonDocument(o).toBinaryData();
}

//------------------------------------------------------------------------------
QByteArray ComPackageWaiterNeed::toByteArray() const
{
    QJsonObject o;
    addData(o);
    o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_NEED_STR;
    o[ROTABLE_PACKAGE_NEED_NEED_STR] = _need;
    o[ROTABLE_PACKAGE_NEED_TABLE_STR] = _tableId;
    return QJsonDocument(o).toBinaryData();
}

//------------------------------------------------------------------------------

ComPackageMessage::ComPackageMessage() :  ComPackage()
{

}

//------------------------------------------------------------------------------

QByteArray ComPackageMessage::toByteArray() const
{
    QJsonObject o;
    addData(o);
    o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_SEND_FILE;
    o[ROTABLE_PACKAGE_MESSAGE_TYPE_STR] = _msgType;
    o[ROTABLE_PACKAGE_MESSAGE_MESSAGE_STR] = _msg;
    return QJsonDocument(o).toBinaryData();
}
//------------------------------------------------------------------------------

ComPackageSendFile::ComPackageSendFile() :  ComPackage()
{

}
//------------------------------------------------------------------------------

QString ComPackageSendFile::base64ToQString(QString encodeFile)
{
    QByteArray ba=NULL;
    ba.append(encodeFile);
    return QByteArray::fromBase64(ba);
}

//------------------------------------------------------------------------------

QByteArray ComPackageSendFile::toByteArray() const
{

    QJsonObject o;
    addData(o);

    o[ROTABLE_PACKAGE_COMMAND_STR] = ROTABLE_PACKAGE_COMMAND_SEND_FILE;
    o[ROTABLE_PACKAGE_FILE_USAGE] = _fileUsage;
    QJsonArray jsonFileArray;
        for(int i=0; i<_fileNames.length(); i++)
        {
            QJsonObject so;
            so[ROTABLE_PACKAGE_FILE_NAMES] = _fileNames.at(i);
            so[ROTABLE_PACKAGE_FILE_FILE] = _files.at(i);
            jsonFileArray.append(so);
        }
    o[ROTABLE_PACKAGE_FILE_INFORMATION_ARRAY]= jsonFileArray;

    return QJsonDocument(o).toBinaryData();
}
