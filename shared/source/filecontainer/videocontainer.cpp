#include "include/filecontainer/videocontainer.h"
#include <QBuffer>

rotable::VideoContainer::VideoContainer(QObject* parent)
    : AbstractFileContainer(parent)
{
    //_fileDir.append("/advertisingVideos");
    //QDir::mkpath(_fileDir);
    //QDir::cd()
}

bool rotable::VideoContainer::addFile(rotable::ComPackageSendFile *package)
{
    QStringList FileListName=package->getFileNames();
    QStringList FileList=package->getFiles();
    int i=0;
    foreach(QString fileName, FileListName)
    {
        QByteArray ByteFile;
        QByteArray ba;
        QBuffer buffer(&ba);
        QByteArray File=package->base64ToQString( FileList.at(i));

        /* Try and open a file for output */
        QFile outputFile(fileName);
        outputFile.open(QIODevice::WriteOnly);

        /* Check it opened OK */
        if(!outputFile.isOpen()){
            qCritical() << "- Error, unable to open" << FileList.at(i) << "for output";
            return 1;
        }
        outputFile.write(File);
        i++;
        /* Close the file */
        outputFile.close();
    }
    return 0;
}


bool rotable::VideoContainer::hasFile(const QString& name) const
{

}

 QString rotable::VideoContainer::getFile(const QString& name) const
 {

 }

 void rotable::VideoContainer::changeFileName()
 {

 }

 void rotable::VideoContainer::rmFile()
 {

 }
