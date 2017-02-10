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

    /**
     * This funktion init the playing of the Advertising videos
     * It goes through a list with the advertisingVideos
     * If the admin put on "play=true" and the frequenc more than
     * 1min than we creat a AdvertisingTimers struct
     * at the end me creat for every advertising a threat with singleShot
     *
     * @brief startPlayAdvertising
     */
    void startPlayAdvertising();

    /**
     * @brief advertisingVideoEnded this method is called from the
     * Client Class. We are chacking which video was played set in the list the
     * lastPlayed and we started again the Timer for the next play
     * @param name
     */
    void advertisingVideoEnded(QString name);

private:

    bool _playing; //is the video now playing

    struct AdvertisingTimers{
        QTime* _timer;
        QTime* _lastPlay;
        QString* _videoName;
        int _frequency;
        int _id;
        int _startDelay;
    }
    *st_timer;

    QList<AdvertisingTimers*> L_timers;

    QList<AdvertisingTimers*> L_timerQueue;

    QList<rotable::AdvertisingVideo*> l_advertisingVideo;

    rotable::TouchEvent* _touch;

    QList<int> _frequncy;

    int _delay;

    int _playListLenth;

    enum source{
        tryLaterAgain,
        putOnlyInQueue
    };

     bool creatAdvertisingPlayList();

     void advertisingTimerQueue(AdvertisingTimers* video, source info);

     /**
      * @brief MinBreakTime make a check when the last
      * @return
      */
     bool MinBreakTime();

     /**
      * This Method we need for calculate the first start of a advertising
      * If all advertisings have the same frequency we calculate different start times
      * @brief calculateDelay
      */
     void calculateDelay();

    void timer(int sec, QTime& timer);

    bool alreadyInQueue(int id);

    void calculatePlayListLength();

    int ggT(int a, int b);
    int kgV(int a, int b);

    int PlayListLength(int kgV);

signals:
    /**
     * Sends information to the Client Class to change the state and
     * to start the video with the given ID
     * @brief play
     * @param id
     */
    void play(QString *name);


private slots:
    /**
     * If one timer of the advertisingVideos ends this
     * method will be called.
     * We check first when was the last touch on the Display
     * Than we check when the table did play the last time an advertising
     * Than we check if somthing is in the Queue
     * The last what we have to check if the _playing flag is on false
     * [This flag is needed because theoretical this method cann be called
     * at the "same" time.
     * If all is fine we set the _playing on true this and we emit a signal
     * to the Client Class that the Video have to be played [signals: void play(QString *name)]
     *
     * If someting was false we put the Video in a Queue
     * @brief timerEnd
     * @param id
     */
    void timerEnd(AdvertisingTimers* video);





private slots:
    void playVideoInQueue(AdvertisingTimers* nameOfTimer);


};

#endif // PLAYADVERTISING_H
