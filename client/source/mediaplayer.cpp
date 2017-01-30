#include "include/mediaplayer.h"
using namespace rotable;

MediaPlayer::MediaPlayer(QObject* parent, Flags flags): QMediaPlayer(parent, flags)
{

}

void MediaPlayer::setVideoSurface(QAbstractVideoSurface* surface)
{
qDebug() << "Changing surface";
m_surface = surface;
setVideoOutput(m_surface);
}

QAbstractVideoSurface* MediaPlayer::getVideoSurface()
{
return m_surface;
}
