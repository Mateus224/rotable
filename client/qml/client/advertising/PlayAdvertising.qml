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
        source: "file:///opt/rotable/advertisingVideo/"+client.AdvertisingVideoName
        autoLoad: true

        onStatusChanged: {
            if (status == MediaPlayer.EndOfMedia)
            {
                client.state="STARTSCREEN"
                client.playAdvertisingEnded(client.AdvertisingVideoName)
            }
        }
        z: 1
        focus: true
    }
    states: [
        State {
            name: "PLAYADVERTISING"
            PropertyChanges { target: video.play()}
        }
    ]

}
