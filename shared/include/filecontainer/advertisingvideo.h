#ifndef ADVERTISINGVIDEO_H
#define ADVERTISINGVIDEO_H
#include "file.h"
#include <QObject>

namespace rotable {
class AdvertisingVideo;
}

class rotable::AdvertisingVideo :  public rotable::File
{
    Q_OBJECT
public:
     AdvertisingVideo(QObject *parent = 0);
    ~AdvertisingVideo();

    void addAdvertisingVideo();


    void setA_id(const int& id);

    /**
     * @brief setFrequency
     * @param min
     * how often will be the video played in minutes
     */
    void setFrequency(const int& frequency);

    void setMedia_id(const int& mediaId);
    /**
     * @brief setPlay
     * @param play
     * set true if the video have to be played
     */
    void setPlay(const bool& play);

    /**
     * @brief setPlayed
     * @param played
     * set how often the video was played
     */
    void setPlayed(const int& played);

    void updateVideo();

    //QJsonValue toJSON()const;

    //static AdvertisingVideo* fromJSON(const QJsonValue &val);

    void addAdditionalData(QJsonObject &obj) const;
    void setAdditionalData(QJsonObject &obj);

    inline int fileType() const { return 0; }

    void updateData(AdvertisingVideo *file);

signals:
    void idChanged();
    void frequencyChanged();
    void mediaIdChanged();
    void playChanged();
    void playedChanged();

public:

    /**
     * @brief The advertisingInfo struct
     * stores the spacific information about the advertising file
     */
    struct advertisingInfo{
        int _id;
        int _mediaId;
        int _frequency;
        bool _play;
        int _played;
    };

    advertisingInfo _advertisingInfo;

    QList<advertisingInfo> l_advertisingInfo;


};

#endif // ADVERTISINGVIDEO_H
