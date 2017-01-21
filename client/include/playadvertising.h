#ifndef PLAYADVERTISING_H
#define PLAYADVERTISING_H

#include <QTouchEvent>
//#include <QTimer>
#include <qtimer.h>
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
signals:
    void startTimer(QString);


private slots:
    void timerEnd(QString name);
    void test(QString name);

private:
    QTimer* _timer;
    rotable::AdvertisingVideo* _advertisingVideo;


};

#endif // PLAYADVERTISING_H
