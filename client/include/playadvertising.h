#ifndef PLAYADVERTISING_H
#define PLAYADVERTISING_H

#include <QTouchEvent>
#include <QTimer>
#include <QTime>
#include <QObject>

#include "filecontainer/advertisingvideo.h"


namespace rotable {
class PlayAdvertising;
}
class rotable::PlayAdvertising : public QObject
{
    Q_OBJECT
public:
    PlayAdvertising(rotable::AdvertisingVideo & _advertisingVideo, QObject *parent = 0);

    void startPlayAdvertising();
private:

    void timerStart(const QString name);
    void timer(int sec, QTime& timer);
signals:
    void startTimer(QString);


private slots:
    void timerEnd(QString& name);

private:
    struct Timers{
        QTime* _timer;
        QString* _videoName;
    }
    *st_timer;

    QList<Timers*>* L_timers;

    rotable::AdvertisingVideo* _advertisingVideo;


};

#endif // PLAYADVERTISING_H
