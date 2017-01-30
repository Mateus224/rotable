import QtQuick 2.0
import QtMultimedia 5.5

Rectangle {
    id:playAdvertising
    anchors.fill: parent
    color: "#111111"
    state:client.state ? client.state: "STARTSCREEN"
    z: 1
    VideoOutput {
    id: videooutput
    anchors.fill: parent
    source: mediaplayer

    }
    /*Video {
        id: video
        anchors.fill: parent
        source: "file:///opt/rotable/advertisingVideo/"+client.AdvertisingVideoName
        autoLoad: true
        autoPlay: true

        onStatusChanged: {
            if (status == MediaPlayer.EndOfMedia)
            {
                client.state="STARTSCREEN"
                client.playAdvertisingEnded(client.AdvertisingVideoName)
            }
            console.log(status)
        }
        focus: true
    }*/
    states: [
        State {
            name: "PLAYADVERTISING"
            //PropertyChanges { target: video.play()}
        },
        State {
            name: "STARTSCREEN"
            //PropertyChanges { target: video.}
        }
    ]

}
