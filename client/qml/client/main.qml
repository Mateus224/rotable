import QtQuick 2.0
import "globals.js" as Global
import "games"
//import "callWaiter"


//import "games/SpinBottle.qml"

Rectangle {
    id: mainScreen
    color: "#000000"
    function device(){
        var buttonColor
        if(client.device_===1){
            buttonColor= "grey"

        }
        else {
            buttonColor= "black"
        }
        return buttonColor
    }
    //width: parent.width ? parent.width :  200
    //height: parent.height ? parent.height : 200
    Rectangle{
        id: rotationButton_1
        width: (parent.width-Math.min(parent.height, parent.width))/2
        height: parent.height/2
        anchors.left: parent.left
        color: device()
    }
    Rectangle{
        id: rotationButton_2
        width: (parent.width-Math.min(parent.height, parent.width))/2
        height: parent.height/2
        anchors.right: parent.right
        color: device()
    }
    Rectangle{
        id: rotationButton_3
        width: (parent.width-Math.min(parent.height, parent.width))/2
        height: parent.height/2
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        color:device()
    }
    Rectangle{
        id: rotationButton_4
        width: (parent.width-Math.min(parent.height, parent.width))/2
        height: parent.height/2
        anchors.bottom: parent.bottom
        color: device()
    }


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
            }
        ]
        //! [states]
    }
}
