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

class AbstractFileContainer : public QObject
{
    Q_OBJECT

public:
    explicit AbstractFileContainer(QObject* parent = 0);


protected:
    virtual bool addFiles(rotable::ComPackageSendFile* package){}

protected:
    virtual bool hasFile(const QString& name){}
    virtual QString getFile(const QString& name) const{}
    virtual void changeFileName(){}
    virtual void rmFile(){}

      QMap<QString, QImage*> _file;
      QDir* _fileDir;

};

#endif // ABSTRACTFILECONTAINER_H
