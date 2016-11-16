#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QMap>
#include <QString>
#include <QDirIterator>
#include <QFile>
#include <QTime>
#include "compackage.h"
#include "logmanager.h"
//------------------------------------------------------------------------------

/**
 * @brief The File class
 * This Abstract Class is for up- and downloading files.
 */
namespace rotable {
class AdvertisingVideo;
class File;
}

class rotable::File : public QObject
{
    Q_OBJECT

public:

    explicit File(QObject* parent = 0);

    ~File();
  /*  enum File{
        advertising=0,

    };*/


    bool addFileOnSD(rotable::ComPackageSendFile* package);
    bool setName(QString fileName){_fileListNames.append(fileName);}



    bool hasFile(const QString& name)const;
    QString getFile(const QString& name) const;
    void changeFileName();
    void rmFile();



    /**
     * @brief getFileInfoFromFileAndSet
     * @param FileListName
     * Check the size of the added Files on the SD and store
     * it in Bytes in a QList<int>
     */
    void getFileInfoFromFileAndSet(QStringList FileListName);

    /**
     * @brief setType
     * @param type
     * Set type of the sended File
     */
    inline void setType(int type){_type=type;}

    /**
     * @brief getType
     * @return
     * get the type of the sended File
     */
    inline int getType(){return _type;}

    /**
     * @brief toJSON prepare data for sending
     * depending on the Object get additional data
     * @return
     */
    QJsonValue toJSON()const;

    /**
     * @brief fromJSON
     * @param jval
     * @return
     */
    static File* fromJSON(const QJsonValue &jval);

    inline virtual int fileType() const { return -1; }

protected:
  virtual void addAdditionalData(QJsonObject &obj) const=0;
  virtual void setAdditionalData(QJsonObject &obj)=0;


//---------------------------------------

public:
    /**
     * @brief The fileInfo struct
     * stores basic Information about the to adding file
     */
    struct fileInfo{
        int _id;
        int _type;
        QString _name;
        QString _date;
        int _size;
        int _removed;
    };

    fileInfo _fileInfo;
    /**
     * @brief l_fileInfo
     * stores a list of the struct with the name and the size of the files
     */
    QList<fileInfo> l_fileInfo;

    QList<QString> _fileListNames;

    QDir* _fileDir;

    /**
     * @brief _path
     * The path to the folders were the files will be stored
     */
    QString _path;

    /**
     * @brief _destinationFoler
     * The Path were the Files will be stored
     */
    QString _destinationFoler;

    /**
     * @brief _fileListNames
     * A List of all adding filenames
     */
    QString _fileName;

    /**
     * @brief _size
     * A List of the size of all adding files
     */
    int _size;

    /**
     * @brief _type
     * Type of
     */
    int _type;

    int _id;

};

#endif // ABSTRACTFILE_H
