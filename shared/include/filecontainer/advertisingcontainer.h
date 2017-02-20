#ifndef ADVERTISINGCONTAINER_H
#define ADVERTISINGCONTAINER_H
#include "filecontainer/advertisingvideo.h"

#include <QObject>
#include <QHash>

namespace  rotable {
    class AdvertisingContainer;
}

class rotable::AdvertisingContainer : public QObject
{
    Q_OBJECT
public:
    explicit AdvertisingContainer(QObject *parent = nullptr);

    ~AdvertisingContainer();

    void addFile(AdvertisingVideo *file);

    QList<int> fileIds() const;

    int count() const;

    AdvertisingVideo* file(int idx) const;

    /**
     * @brief Clear object
     *
     */
    void clear();
    AdvertisingVideo* getSelectedFile() const;
    void setSelectedFile(AdvertisingVideo *value);
    void setSelectedFile(int inx);

    void playTimeNextElement(int id);



signals:
    /**
     * @brief
     *
     * @param user
     */
    void fileAdded(AdvertisingVideo *file);
    /**
     * @brief
     *
     */
    void fileRemoved();
    /**
     * @brief
     *
     */
    void fileUpdated();
    /**
     * @brief
     *
     */
    void updateView();

    void advertisingVideoUpdated(rotable::AdvertisingVideo* advertisingVideo);


private slots:

    void onFileUpdated();

private:
    bool calculatePercentNextElement_PlayTime(int SumOfplayTimes);

    QHash<int,AdvertisingVideo*> *_files; /** Container with files */
    AdvertisingVideo *selectedFile;
    AdvertisingVideo *tmpFile;
    AdvertisingVideo *nextFile;
};

#endif // ADVERTISINGCONTAINER_H
