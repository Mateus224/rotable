import QtQuick 2.0
import "../"

Rectangle {
    anchors.fill: parent
    color: "#00000000"

    MyOrderButton {
        id: buttonMyOrder
    }

    Rectangle {
        anchors.fill: parent
        anchors.topMargin: parent.height * 0.2
        anchors.leftMargin: parent.width * (1.0 - 0.805) / 2.0
        anchors.rightMargin: parent.width * (1.0 - 0.805) / 2.0
        anchors.bottomMargin: parent.height * (0.09125 + 0.10 + 0.125)

        color: "#3f494a"

        Rectangle {
                id:callwaiterbutton
            states:[
                State{
                    name: "DEFAULT"
                    PropertyChanges{target: buttonChange; gradient:clubcolorsblue}
                    PropertyChanges{target: callWaiterText; text:"Press to call the waiter"}
                },
                State{
                    name: "CALLWAITER"
                    PropertyChanges{target: buttonChange; gradient:clubcolorsred}
                    PropertyChanges{target: callWaiterText; text:"Waiter is called"}
                }

            ]

            anchors.fill: parent
            anchors.margins: parent.height * 0.02

            color: "#000000"
            Rectangle{
                id:buttonChange
                anchors.fill: parent
                anchors.margins: parent.height * 0.02
                //color: "#48A8C0"
                gradient: clubcolorsblue
                Text{
                    id:callWaiterText
                    text: "Press to call the waiter"
                    font.family: "FreeSans"
                    color: "#FFFFFF"
                    font.pointSize: 22
                    anchors.centerIn: parent
                    font.bold: true
                }
                MouseArea{
                    anchors.fill: parent
                    anchors.margins: parent.height * 0.02
                    onClicked:  {
                        if(callwaiterbutton.state!="CALLWAITER")
                        {
                            callwaiterbutton.state="CALLWAITER"
                            client.changeStateWaiterNeed(true)
                        }
                        else
                        {
                            callwaiterbutton.state="DEFAULT"
                            client.changeStateWaiterNeed(false)
                        }
                    }
                }

            }
        }
    }

    CategoryBar {
        id: categoryBar
    }
    Gradient {
        id: clubcolorsblue
        GradientStop { position: 0.0; color:"White" }//"#8EE2FE"}
        GradientStop { position: 0.66; color: "#48A8C0"}
    }
    Gradient {
        id: clubcolorsred
        GradientStop { position: 0.0; color:"White" }//"#8EE2FE"}
        GradientStop { position: 0.66; color: "red"}
    }
}

