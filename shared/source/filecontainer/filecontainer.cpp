#include "include/filecontainer/filecontainer.h"
#include "logmanager.h"
FileContainer::FileContainer(const QString folder, QObject *parent) : QObject(parent),_destinationFoler(folder)
{
    _path="/opt/rotable/";
    _path.append(_destinationFoler);
    _fileDir = new QDir(_path);
    if(!_fileDir->exists())
    {
        _fileDir->mkpath(_path);
    }
}

FileContainer::~FileContainer()
{
    delete _fileDir;
}



bool FileContainer::addFile(rotable::ComPackageSendFile *package)
{
    _fileListNames=package->getFileNames();
    QStringList FileList=package->getFiles();
    int i=0;
    foreach(QString fileName, _fileListNames)
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


bool FileContainer::hasFile(const QString& name) const
{

}

 QString FileContainer::getFile(const QString& name) const
 {

 }

 void FileContainer::changeFileName()
 {

 }

 void FileContainer::rmFile()
 {

 }

 void FileContainer::setFileInfo(QStringList FileListName)
 {
    foreach(QString fileName, FileListName)
    {
        fileInfo struct_fileInfo;
        _path.append(fileName);
        QFileInfo file(_path);
        struct_fileInfo._name=fileName;
        struct_fileInfo._size=file.size();
        l_fileInfo.append(file);
    }
 }

