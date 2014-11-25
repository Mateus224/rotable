import QtQuick 2.0
import QtMultimedia 5.0
import "globals.js" as Global

Rectangle {
    width: 800
    height: 800
    //color: "#FF00FF"
    color: "#000000"

    Rectangle {
        id: screen
        width: parent.height
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#000000"
        state: client.state
        rotation: client.screenRotation

        ConnectionPage {
            id: connectionPage
        }

        ScreensaverPage {
            id: screensaverPage
        }

        StartPage {
            id: startPage
        }

        ProductPage {
            id: productPage
        }

        //! [states]
        states: [
            State {
                name: "DISCONNECTED"
                PropertyChanges { target: connectionPage; visible: true }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
            },
            State {
                name: "SCREENSAVER"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: true }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
            },
            State {
                name: "STARTSCREEN"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: true }
                PropertyChanges { target: productPage; visible: false }
            },
            State {
                name: "PRODUCTSCREEN"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: true }
            }
        ]
        //! [states]
    }
}
