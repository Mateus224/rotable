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
    PlayAdvertising(rotable::AdvertisingVideo & _advertisingVideo,rotable::TouchEvent &touch, QObject *parent = 0);

    void startPlayAdvertising();
private:

    void timerStart(const QString name);
    void timer(int sec, QTime& timer);
signals:
    void startTimer(QString);


private slots:
    void timerEnd(QString& name);

private:

    void advertisingTimerQueue();

    struct Timers{
        QTime* _timer;
        QString* _videoName;
    }
    *st_timer;

    QList<Timers*>* L_timers;

    QList<Timers*>* L_timerQueue;

    rotable::AdvertisingVideo* _advertisingVideo;

    rotable::TouchEvent* _touch;




};

#endif // PLAYADVERTISING_H
