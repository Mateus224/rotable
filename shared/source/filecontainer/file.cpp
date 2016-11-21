#include "filecontainer/file.h"
#include "filecontainer/advertisingvideo.h"
#include "logmanager.h"
#include "compackage.h"

using namespace rotable;

//------------------------------------------------------------------------------

File::File( QObject *parent) : QObject(parent)
{

    _path="/opt/rotable/";
    _fileDir = new QDir(_path);
    if(!_fileDir->exists())
    {
        _fileDir->mkpath(_path);
    }
}

File::~File()
{
    delete _fileDir;
}



bool File::addFileOnSD(rotable::ComPackageSendFile *package)
{
    QStringList FileNameList=package->getFileNames();
    QStringList FileList=package->getFiles();
    int i=0;
    foreach(QString fileName, FileNameList)
    {
        QByteArray File=package->base64ToQString( FileList.at(i));

        /* Try and open a file for output */
        QFile outputFile(_fileDir->filePath(fileName));
        outputFile.open(QIODevice::WriteOnly);

        /* Check it opened OK */
        if(!outputFile.isOpen()){
            qCritical() << "- Error, unable to open" << FileList.at(i) << "for output";
            return 0;
        }
        outputFile.write(File);
        i++;
        /* Close the file */
        outputFile.close();
    }
    return 1;
}

//------------------------------------------------------------------------------


bool File::hasFile(const QString& name) const
{

}

 QString File::getFile(const QString& name) const
 {

 }

 void File::changeFileName()
 {

 }

 void File::rmFile()
 {

 }


 //------------------------------------------------------------------------------

 void File::getFileInfoFromFileAndSet(QStringList FileListName)
 {
    foreach(QString fileName, _fileListNames)
    {
        QString path =_path;
        fileInfo struct_fileInfo;
        path.append(fileName);
        QFileInfo file(path);
        struct_fileInfo._name=fileName;
        struct_fileInfo._size=file.size();
        l_fileInfo.append(struct_fileInfo);
    }
 }

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
     case 0:
     {
       fc = new AdvertisingVideo();
     } break;
     case 1: {

     } break;
     case 2: {

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

