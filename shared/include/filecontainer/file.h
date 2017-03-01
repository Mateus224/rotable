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
class File;
}

class rotable::File : public QObject
{
    Q_OBJECT

public:

    explicit File(QObject* parent = 0);

    ~File();

    bool addFileOnSD(rotable::ComPackageSendFile* package);

    /**
     * @brief removeFileFromSD
     * First check which type this File has
     * for finding the File in the right folder
     * @return
     */
    bool removeFileFromSD();

    /**
     * @brief checkMediaOnSD
     * Check at start after we get the databaseinformation
     * which Medias have to be played, we have to check if
     * the client has this file on SD. If Yes
     * @return true
     */
    bool checkMediaOnSD();

    /**
     * @brief rename
     * @param oldName
     * @param newName
     * @return true on succed
     * find the old name and set a new name for a file on the the SD card
     */
    bool rename(QString &newName);

    /**
     * @brief getFileInfoFromFileAndSet
     * @param FileListName
     * Check the size of the added Files on the SD and store
     * it in Bytes in a QList<int>
     */
    void getFileInfoFromFileAndSet(QStringList FileListName);

    /**
     * @brief setDir
     * @return
     */
    bool setDir();
    /**
     * @brief setType
     * @param type
     * Set type of the sended Files (needed by adding files)
     */
    inline void setType(int type){_type=type;}

    /**
     * @brief getType
     * @return
     * get the type of the sended Files (used in database)
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

    virtual void updateData(File *file){;}


    inline int getId() const { return _fileInfo._id; }

    inline QString getName() const { return _fileInfo._name; }

    inline QString getDate() const { return _fileInfo._date; }

    inline int getSize() const { return _fileInfo._size ; }

    inline int getRemoved() const { return _fileInfo._removed; }

    void setId(const int &id);

    void setName(const QString &name);

    void setDate(const QString &date);

    void setSize(const int &size);

    void setRemoved(const int &removed);

protected:
  virtual void addAdditionalData(QJsonObject &obj) const=0;
  virtual void setAdditionalData(QJsonObject &obj)=0;


signals:
      void idChanged();
      void nameChanged();
      void dateChanged();
      void sizeChanged();
      void removedChanged();
//---------------------------------------

public:


      enum type{
          AdvertisingVideo=0
      };

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
    QStringList _paths;

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
