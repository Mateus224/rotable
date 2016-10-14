#ifndef VIDEOCONTAINER_H
#define VIDEOCONTAINER_H
#include <filecontainer/abstractfilecontainer.h>

class VideoContainer : public AbstractFileContainer
{
public:
    VideoContainer();

protected:
    bool addFile(const QString &name, QString *fileData);
    bool hasFile(const QString &name) const;
    QString getFile(const QString &name) const;
    //void setDir(const QStr);
};

#endif // VIDEOCONTAINER_H
