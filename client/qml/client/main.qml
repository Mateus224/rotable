import QtQuick 2.0
import QtMultimedia 5.0
import "globals.js" as Global
import "games"
import "callWaiter"


//import "games/SpinBottle.qml"

Rectangle {
    id: mainScreen
    color: client.debug ? "#C0C0C0" : "#000000"

    Rectangle {
        id: screen
        width: Math.min(parent.height, parent.width)
        height: Math.min(parent.height, parent.width)
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

        MyOrderPage{
            id: myOrderPage
        }

        GamePage{
            id:gamePage
        }

        CallWaiterPage{
            id: callWaiterPage
        }

        //! [states]
        states: [
            State {
                name: "DISCONNECTED"
                PropertyChanges { target: connectionPage; visible: true }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
                PropertyChanges { target: myOrderPage; visible: false}
                PropertyChanges { target: gamePage; visible: false}
                PropertyChanges { target: callWaiterPage; visible: false}
            },
            State {
                name: "SCREENSAVER"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: true }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
                PropertyChanges { target: myOrderPage; visible: false}
                PropertyChanges { target: gamePage; visible: false}
                PropertyChanges { target: callWaiterPage; visible: false}
            },
            State {
                name: "STARTSCREEN"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: true }
                PropertyChanges { target: productPage; visible: false }
                PropertyChanges { target: myOrderPage; visible: false}
                PropertyChanges { target: gamePage; visible: false}
                PropertyChanges { target: callWaiterPage; visible: false}
            },
            State {
                name: "PRODUCTSCREEN"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: true }
                PropertyChanges { target: myOrderPage; visible: false}
                PropertyChanges { target: gamePage; visible: false}
                PropertyChanges { target: callWaiterPage; visible: false}
            },
            State {
                name: "MYORDERSCREEN"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
                PropertyChanges { target: myOrderPage; visible: true}
                PropertyChanges { target: gamePage; visible: false}
                PropertyChanges { target: callWaiterPage; visible: false}
            },
            State {
                name: "GAMEPAGE"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
                PropertyChanges { target: myOrderPage; visible: false}
                PropertyChanges { target: gamePage; visible: true}
                PropertyChanges { target: callWaiterPage; visible: false}
            },
            State {
                name: "CALLWAITERPAGE"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
                PropertyChanges { target: myOrderPage; visible: false}
                PropertyChanges { target: gamePage; visible: false}
                PropertyChanges { target: callWaiterPage; visible: true}

            }
        ]
        //! [states]
    }
}
