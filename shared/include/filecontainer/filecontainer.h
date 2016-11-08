#ifndef ABSTRACTFILECONTAINER_H
#define ABSTRACTFILECONTAINER_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QMap>
#include <QString>
#include <QDirIterator>
#include <QFile>
#include "compackage.h"
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
    void getSize(QStringList FileListName, int& size);

    QMap<QString, QImage*> _file;
    QDir* _fileDir;
    QString _destinationFoler;

};

#endif // ABSTRACTFILECONTAINER_H
