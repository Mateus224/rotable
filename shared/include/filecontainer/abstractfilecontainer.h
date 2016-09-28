#ifndef ABSTRACTFILECONTAINER_H
#define ABSTRACTFILECONTAINER_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QMap>
#include <QString>

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

    virtual bool addFile(const QString& name, QString* fileData){}
    virtual bool hasFile(const QString& name) const{}
    virtual QString getFile(const QString& name) const{}
    virtual void setDir(const QString& dir){}
    virtual QStringList fileNames() const{}

      QMap<QString, QImage*> _file;
      QString _imageDir;

};

#endif // ABSTRACTFILECONTAINER_H
