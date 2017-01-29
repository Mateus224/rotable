import QtQuick 2.0
import "globals.js" as Global
import "games"
import QtQuick.Controls 2.0
import "advertising"

Rectangle {

    id: mainScreen

    MouseArea{
        anchors.fill: parent
        onClicked: touchEvent.newTouchEvent()
    }

    RotationButton{
        id: rotationButton_leftTop
        anchors.left: parent.left
        //property double topMargin: 0.01
        //property double bottomMargin: 0.005
        property int _rotation: 180
        //z:0
    }
    RotationButton{
        id: rotationButton_rightTop
        anchors.right: parent.right
        //property double topMargin: 0.01
        //property double bottomMargin: 0.005
        property int _rotation: 270
        //z:2
    }
    RotationButton{
        id: rotationButton_rightBottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        //property double topMargin: 0.005
        //property double bottomMargin: 0.01
        property int _rotation: 0
        //z:2
    }
    RotationButton{
        id: rotationButton_leftBottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        //property double topMargin: 0.005
        //property double bottomMargin: 0.01
        property int _rotation: 90
        //z:2
    }

//------------------------------------------------------------

    Rectangle {
        id: screen
        width: Math.min(parent.height, parent.width)
        height: Math.min(parent.height, parent.width)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#000000"
        state: client.state ? client.state: "STARTSCREEN"
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

        SentPage{
            id:sentPage
        }

        SendAccept{
            id: sendAccept
        }

        PlayAdvertising{
            id:playAdvertising
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
                PropertyChanges { target: sentPage; visible: false}
                PropertyChanges { target: sendAccept; visible: false}
                PropertyChanges { target: playAdvertising; visible: false}
                PropertyChanges { target: screen; width: Math.min(parent.height, parent.width); height:Math.min(mainScreen.width, mainScreen.height)}

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
                PropertyChanges { target: sentPage; visible: false}
                PropertyChanges { target: sendAccept; visible: false}
                PropertyChanges { target: playAdvertising; visible: false}
                PropertyChanges { target: screen; width: Math.min(parent.height, parent.width); height:Math.min(mainScreen.width, mainScreen.height)}
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
                PropertyChanges { target: sentPage; visible: false}
                PropertyChanges { target: sendAccept; visible: false}
                PropertyChanges { target: playAdvertising; visible: false}
                PropertyChanges { target: screen; width: Math.min(parent.height, parent.width); height:Math.min(mainScreen.width, mainScreen.height)}
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
                PropertyChanges { target: sentPage; visible: false}
                PropertyChanges { target: sendAccept; visible: false}
                PropertyChanges { target: playAdvertising; visible: false}
                PropertyChanges { target: screen; width: Math.min(parent.height, parent.width); height:Math.min(mainScreen.width, mainScreen.height)}
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
                PropertyChanges { target: sentPage; visible: false}
                PropertyChanges { target: sendAccept; visible: false}
                PropertyChanges { target: playAdvertising; visible: false}
                PropertyChanges { target: screen; width: Math.min(parent.height, parent.width); height:Math.min(mainScreen.width, mainScreen.height)}
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
                PropertyChanges { target: sentPage; visible: false}
                PropertyChanges { target: sendAccept; visible: false}
                PropertyChanges { target: playAdvertising; visible: false}
                PropertyChanges { target: screen; width: Math.min(parent.height, parent.width); height:Math.min(mainScreen.width, mainScreen.height)}
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
                PropertyChanges { target: sentPage; visible: false}
                PropertyChanges { target: sendAccept; visible: false}
                PropertyChanges { target: playAdvertising; visible: false}
                PropertyChanges { target: screen; width: Math.min(parent.height, parent.width); height:Math.min(mainScreen.width, mainScreen.height)}
            },
            State {
                name: "SENTPAGE"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
                PropertyChanges { target: myOrderPage; visible: false}
                PropertyChanges { target: gamePage; visible: false}
                PropertyChanges { target: callWaiterPage; visible: false}
                PropertyChanges { target: sentPage; visible: true}
                PropertyChanges { target: sendAccept; visible: false}
                PropertyChanges { target: playAdvertising; visible: false}
                PropertyChanges { target: screen; width: Math.min(parent.height, parent.width); height:Math.min(mainScreen.width, mainScreen.height)}
            },
            State {
                name: "SENDACCEPT"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
                PropertyChanges { target: myOrderPage; visible: false}
                PropertyChanges { target: gamePage; visible: false}
                PropertyChanges { target: callWaiterPage; visible: false}
                PropertyChanges { target: sentPage; visible: false}
                PropertyChanges { target: sendAccept; visible: true}
                PropertyChanges { target: playAdvertising; visible: false}
                PropertyChanges { target: screen; width: Math.min(parent.height, parent.width); height:Math.min(mainScreen.width, mainScreen.height)}
            },
            State {
                name: "PLAYADVERTISING"
                PropertyChanges { target: connectionPage; visible: false }
                PropertyChanges { target: screensaverPage; visible: false }
                PropertyChanges { target: startPage; visible: false }
                PropertyChanges { target: productPage; visible: false }
                PropertyChanges { target: myOrderPage; visible: false}
                PropertyChanges { target: gamePage; visible: false}
                PropertyChanges { target: callWaiterPage; visible: false}
                PropertyChanges { target: sentPage; visible: false}
                PropertyChanges { target: sendAccept; visible: false}
                PropertyChanges { target: playAdvertising; visible: true}
                PropertyChanges { target: screen; width:  mainScreen.width; height:  mainScreen.height}
            }
        ]
        //! [states]
    }

}
