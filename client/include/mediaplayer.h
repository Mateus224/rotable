#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QMediaPlayer>

namespace rotable {
class MediaPlayer;
}

class rotable::MediaPlayer: public QMediaPlayer
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface* videoSurface READ getVideoSurface WRITE setVideoSurface )

    public:
    MediaPlayer(QObject * parent = 0, Flags flags = 0);

    public slots:

    void setVideoSurface(QAbstractVideoSurface* surface);
    QAbstractVideoSurface* getVideoSurface();


    private:
    QAbstractVideoSurface* m_surface;
    };


#endif // MEDIAPLAYER_H
