import QtQuick 2.0
import QtMultimedia 5.0

Rectangle {
    id:_media_
    anchors.fill: parent
    //width: mainScreen.width
    //height: mainScreen.height
    color: "#111111"
    z: 1
    Video {
        id: video
        anchors.fill: parent
        source: "file:///opt/rotable/advertisingVideo/test01.mp4"
        autoLoad: true
        visible: true

        MouseArea {
            anchors.fill: parent
            onClicked: {
                 video.play()
            }
        }
        z: 1
        focus: true
        Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
        Keys.onLeftPressed: video.seek(video.position - 5000)
        Keys.onRightPressed: video.seek(video.position + 5000)
    }

}
