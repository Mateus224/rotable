#ifndef PLAYADVERTISING_H
#define PLAYADVERTISING_H

#include <QTime>
#include <QObject>

#include "filecontainer/advertisingvideo.h"
#include "touchevent.h"


namespace rotable {
class PlayAdvertising;
}
class rotable::PlayAdvertising : public QObject
{
    Q_OBJECT
public:
    PlayAdvertising(QList<rotable::AdvertisingVideo*> & _advertisingVideo,rotable::TouchEvent &touch, QObject *parent = 0);

    void startPlayAdvertising();

     void advertisingVideoEnded(QString name);

private:

    void timerStart(const QString name);
    void timer(int sec, QTime& timer);
signals:
    void startTimer(QString);
    /**
     * Sends information to the Client Class to change the state and
     * to start the video with the given ID
     * @brief play
     * @param id
     */
    void play(QString *name);


private slots:
    void timerEnd(int& id);

private:

    void advertisingTimerQueue(const int &id);

    int MinBreakTime();

    bool _playing; //is the video now playing

    struct AdvertisingTimers{
        QTime* _timer;
        QTime* _lastPlay;
        QString* _videoName;
        int _frequency;
        int _id;
    }
    *st_timer;

    QList<AdvertisingTimers*> L_timers;

    QList<AdvertisingTimers*> L_timerQueue;

    QList<rotable::AdvertisingVideo*> l_advertisingVideo;

    rotable::TouchEvent* _touch;




};

#endif // PLAYADVERTISING_H
