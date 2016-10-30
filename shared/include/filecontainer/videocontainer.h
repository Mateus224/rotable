#ifndef VIDEOCONTAINER_H
#define VIDEOCONTAINER_H
#include <filecontainer/abstractfilecontainer.h>

namespace rotable {
    class VideoContainer;
}

class rotable::VideoContainer : public AbstractFileContainer
{
    Q_OBJECT

public:
    explicit VideoContainer(QObject* parent = 0);


    bool addFile(rotable::ComPackageSendFile* package);

protected:
    bool hasFile(const QString& name) const;
    QString getFile(const QString& name) const;
    void changeFileName();
    void rmFile();

private:
    QString _fileName;
};

#endif // VIDEOCONTAINER_H
