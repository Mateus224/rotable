#include "include/filecontainer/filecontainer.h"

FileContainer::FileContainer(const QString folder, QObject *parent) : QObject(parent),_destinationFoler(folder)
{
    QString path="/opt/rotable/";
    path.append(_destinationFoler);
    _fileDir = new QDir(path);
    if(!_fileDir->exists())
    {
        _fileDir->mkpath(path);
    }
}

FileContainer::~FileContainer()
{

}



bool FileContainer::addFile(rotable::ComPackageSendFile *package)
{
    QStringList FileListName=package->getFileNames();
    QStringList FileList=package->getFiles();
    int i=0;
    foreach(QString fileName, FileListName)
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

void FileContainer::getSize(QStringList FileListName, int& size)
 {
    foreach(QString fileName, FileListName)
    {
        
    }
 }

