#include "filecontainer/file.h"
#include "filecontainer/advertisingvideo.h"
#include "logmanager.h"
#include <QStandardPaths>
using namespace rotable;

//------------------------------------------------------------------------------

File::File( QObject *parent) : QObject(parent),_fileInfo()
{
    //This sequence have be the same like the FileUsage see also Comapackge
    auto dir = QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation));
    QString s_advertisingvideo=dir.absolutePath().append("/rotable/advertisingVideos/");
    QString s_advertisingPicture=dir.absolutePath().append("/rotable/advertisingPictures/");
    QString s_CategoryIcons=dir.absolutePath().append("/rotable/categoryIcons/");
    _paths<<s_advertisingvideo<<s_advertisingPicture<<s_CategoryIcons;
    for(QString &path: _paths)
        {
        _fileDir = new QDir(path);
        if(!_fileDir->exists())
        {
            _fileDir->mkpath(path);
        }
    }
}

File::~File()
{
    delete _fileDir;
}

//------------------------------------------------------------------------------

bool File::addFileOnSD(rotable::ComPackageSendFile *package)
{
    QStringList FileNameList=package->getFileNames();
    QStringList FileList=package->getFiles();
    int i=0;
    foreach(QString fileName, FileNameList)
    {
        QByteArray File=package->base64ToQString( FileList.at(i));
        _fileDir->setCurrent(_paths.at(package->getFileUsage()));

        QFile outputFile(fileName);
        outputFile.open(QIODevice::WriteOnly);

        if(!outputFile.isOpen()){
            qCritical() << "- Error, unable to open" << FileList.at(i) << "for output";
            return false;
        }
        outputFile.write(File);
        i++;

        outputFile.close();
    }
    return true;
}

//------------------------------------------------------------------------------

bool File::removeFileFromSD()
{
    //LogManager::getInstance()->logInfo(_paths.at(_fileInfo._type));
    if(_fileDir->setCurrent(_paths.at(_fileInfo._type)));
    QFile rmFile(getName());
    if(rmFile.remove())
        return true;
    return false;
}
//------------------------------------------------------------------------------

bool File::checkMediaOnSD(){
    if(_fileDir->setCurrent(_paths.at(_fileInfo._type)));
    QFile existFile(getName());
    if(existFile.exists())
        return true;
    return false;
}

//------------------------------------------------------------------------------

bool File::rename(QString &newName)
{
    //choose the type
    switch (_fileInfo._type) {
    case AdvertisingVideo:{
        QFile fileExist(_paths.at(AdvertisingVideo) + newName);
        if(fileExist.exists())
            return true;
        QFile renameFile(_paths.at(AdvertisingVideo) + _fileInfo._name);
        renameFile.open(QIODevice::WriteOnly| QIODevice::ReadOnly);
        if(!renameFile.rename(newName))
        {
            qCritical()<<"err with rename file";
            renameFile.close(); // !true if other information were changed but not the filename
            return false;
        }
        renameFile.close();
    }break;
    default:{

    }break;
    }
    return true;
}

//------------------------------------------------------------------------------

bool File::setDir(){
   if(_fileDir->setCurrent(_paths.at(_fileInfo._type)))
       return true;
   return false;
}

//------------------------------------------------------------------------------

void File::setId(const int& id)
{
  if (_fileInfo._id != id) {
    _fileInfo._id = id;
    emit idChanged();
  }
}

void File::setName(const QString& name)
{
  if (_fileInfo._name != name) {
    _fileInfo._name = name;
    emit nameChanged();
  }
}

void File::setDate(const QString& date)
{
  if (_fileInfo._date != date) {
    _fileInfo._date = date;
    emit dateChanged();
  }
}

void File::setSize(const int& size)
{
  if (_fileInfo._size != size) {
    _fileInfo._size = size;
    emit sizeChanged();
  }
}

void File::setRemoved(const int& removed)
{
  if (_fileInfo._removed != removed) {
    _fileInfo._removed = removed;
    emit removedChanged();
  }
}

 //------------------------------------------------------------------------------

 void File::getFileInfoFromFileAndSet(QStringList FileListNames)
 {
    foreach(QString fileName, FileListNames)
    {
        QString path =_paths.at(AdvertisingVideo);
        fileInfo struct_fileInfo;
        path.append(fileName);
        QFileInfo file(path);
        struct_fileInfo._name=fileName;
        struct_fileInfo._size=file.size();
        l_fileInfo.append(struct_fileInfo);
    }
 }
 //------------------------------------------------------------------------------

//void File
 //------------------------------------------------------------------------------

 QJsonValue File::toJSON() const {
   QJsonObject o;
   o["id"]=_fileInfo._id;
   o["date"]=_fileInfo._date;
   o["name"]=_fileInfo._name;
   o["removed"]=_fileInfo._removed;
   o["size"]=_fileInfo._size;
   o["type"]= fileType();
   addAdditionalData(o);
   return QJsonValue(o);
 }

 //------------------------------------------------------------------------------

 File *File::fromJSON(const QJsonValue &jval)
 {
   QJsonObject o = jval.toObject();

   if (o.contains("id")
           &&o.contains("name")
           &&o.contains("date")
           &&o.contains("size")
           &&o.contains("removed")
           &&o.contains("type"))
   {
     File *fc = nullptr;

     switch (o["type"].toInt()) {
     case rotable::ComPackage::AdvertisingVideo:
     {
       fc = new rotable::AdvertisingVideo();
     } break;
     case rotable::ComPackage::AdvertisingPicture: {

     } break;
     case rotable::ComPackage::CatergoryIcon: {

     } break;
     }
     fc->setAdditionalData(o);
     fc->_fileInfo._id=o["id"].toInt();
     fc->_fileInfo._date=o["date"].toString();
     fc->_fileInfo._name=o["name"].toString();
     fc->_fileInfo._removed=o["removed"].toBool();
     fc->_fileInfo._size=o["size"].toInt();

     return fc;
   }

   return NULL;
 }

 //------------------------------------------------------------------------------

