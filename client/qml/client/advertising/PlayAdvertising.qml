import QtQuick 2.0
import QtMultimedia 5.0

Rectangle {
    id:playAdvertising
    anchors.fill: parent
    //width: mainScreen.width
    //height: mainScreen.height
    color: "#111111"
    state:client.state ? client.state: "STARTSCREEN"
    z: 1
    Video {
        id: video
        anchors.fill: parent
        source: "file:///opt/rotable/advertisingVideo/test01.mp4"
        autoLoad: true
        //play: startPlay

        onStatusChanged: {
            if (status == MediaPlayer.EndOfMedia)
                client.state="STARTSCREEN"
        }
        z: 1
        focus: true
        Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
        Keys.onLeftPressed: video.seek(video.position - 5000)
        Keys.onRightPressed: video.seek(video.position + 5000)
    }
    states: [
        State {
            name: "PLAYADVERTISING"
            PropertyChanges { target: video.play()}
        }
    ]

}
