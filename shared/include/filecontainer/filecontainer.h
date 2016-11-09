#ifndef ABSTRACTFILECONTAINER_H
#define ABSTRACTFILECONTAINER_H

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
 * @brief The AbstractFileContainer class
 * This Abstract Class is for up- and downloading files.
 */

class FileContainer : public QObject
{
    Q_OBJECT

public:

    explicit FileContainer(const QString folder, QObject* parent = 0);
    ~FileContainer();
    enum File{
        advertising=0,

    };


    bool addFile(rotable::ComPackageSendFile* package);
    bool hasFile(const QString& name)const;
    QString getFile(const QString& name) const;
    void changeFileName();
    void rmFile();

    /**
     * @brief setFileInfo
     * @param FileListName
     * Check the size of the added Files and store it in Bytes in a QList<int>
     */
    void setFileInfo(QStringList FileListName);

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


//---------------------------------------

    struct fileInfo{
        QString _name;
        int _size;
    };

    QList<fileInfo> l_fileInfo;

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

};

#endif // ABSTRACTFILECONTAINER_H
