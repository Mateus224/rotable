#ifndef ADVERTISINGVIDEO_H
#define ADVERTISINGVIDEO_H
#include "filecontainer/filecontainer.h"
#include <QObject>

class AdvertisingVideo : public QObject, public FileContainer
{
    Q_OBJECT
public:
    explicit AdvertisingVideo(QObject *parent = 0);
    ~AvertisingVideo();

    /**
     * @brief setFrequency
     * @param min
     * how often will be the video played in minutes
     */
    void setFrequency(int min);

    int getFrequency();

    /**
     * @brief setPlay
     * @param play
     * set true if the video have to be played
     */
    void setPlay(bool play);

    /**
     * @brief setPlayed
     * @param played
     * set how often the video was played
     */
    void setPlayed(int played);

    void updateVideo();

    QJsonValue toJSON()const;

    AdvertisingVideo* fromJSOPN(const QJsonValue &val);

signals:

public slots:

public:
    int _mediaId;
    int _frequency;
    bool _play;
    int _played;
};

#endif // ADVERTISINGVIDEO_H
