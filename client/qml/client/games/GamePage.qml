import QtQuick 2.0
import "SpinTheBottle/"
import ".."

Rectangle {
    id:gamePage

    property int stateChangeDuration: 100
    anchors.fill: parent
    color: "#00000000"
    state: "DEFAULT"

    Rectangle {
        id: categoryTitle

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: parent.height * 0.1
        width: parent.width //* 0.33333
        height: parent.height * 0.05
        gradient: clubcolorsrevers
        Gradient {
            id: clubcolorsrevers
            GradientStop { position: 0.0; color:"#8EE2FE"}//"#8EE2FE"}
            GradientStop { position: 0.90; color: "#000000"}
        }
    }

    Rectangle {
        anchors.fill: parent
        anchors.topMargin: parent.height * 0.2
        anchors.leftMargin: parent.width * (1.0 - 0.805) / 2.0
        anchors.rightMargin: parent.width * (1.0 - 0.805) / 2.0
        anchors.bottomMargin: parent.height * (0.09125 + 0.10 + 0.125)
        color: "#3f494a"


        Rectangle {
            id:gridGamePage
            anchors.fill: parent
            anchors.margins: parent.height * 0.02


            color: "#000000"
            Grid {

                function color(row,column) {
                    if (column === 2) {
                      return "#f9a8d8";
                    } else if ((column === 0 || column === 3) && (row % 2) === 0) {
                      return "#8772c0";
                    } else if ((column === 1 || column === 4) && (row % 2) === 1) {
                      return "#8772c0";
                    } else if ((column === 1 || column === 4) && (row % 2) === 0) {
                      return "#0798d1";
                    } else if ((column === 0 || column === 3) && (row % 2) === 1) {
                      return "#0798d1";
                    }// "#0798d1"
                }

                columns: 5
                rows: 3
                spacing: parent.width  * 0.015
                anchors.topMargin: parent.height * 0.025
                anchors.leftMargin: parent.width  * 0.015
                anchors.fill: parent

                EmptyGridRect{
                    color:parent.color(0,0)
                    gameName:"Spin the Bottle"
                    property int _center: 1
                    MouseArea{
                        onClicked: {

                        }
                    }
                }
                EmptyGridRect{
                    id:tete
                    color:parent.color(0,1)
                }
                EmptyGridRect{
                    id:b
                   color: parent.color(0,2)
                }
                EmptyGridRect{
                    id:a
                    color: parent.color(0,3)
                }
                EmptyGridRect{
                    id:c
                    color: parent.color(0,4)
                }
                EmptyGridRect{
                    color: parent.color(1,0)
                }
                EmptyGridRect{
                    color: parent.color(1,1)
                }
                EmptyGridRect{
                   color: parent.color(1,2)
                }
                EmptyGridRect{
                    color: parent.color(1,3)
                }
                EmptyGridRect{
                    color: parent.color(1,4)
                }
                EmptyGridRect{
                    color: parent.color(2,0)
                }
                EmptyGridRect{
                   color: parent.color(2,1)
                }
                EmptyGridRect{
                   color: parent.color(2,2)
                }
                EmptyGridRect{
                    color: parent.color(2,3)
                }
                EmptyGridRect{
                    color: parent.color(2,4)
                }
            }
        }
    }

    CategoryBar {
        id: categoryBar
    }
    Queue{
        id:queue
        visible: true

    }
    SpinBottle{
        id:spinTheBottle
        visible: false

        Behavior on x {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on y {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on width {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on height {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on z {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
    }

    states: [
        State {
            name: "DEFAULT"
            PropertyChanges { target: spinTheBottle; visible: false }
            PropertyChanges { target: queue; visible: true }
            PropertyChanges { target: spinTheBottle; z: 0 }
            PropertyChanges { target: tete; z: 0 }
            PropertyChanges { target: spinTheBottle; width: Math.min(mainScreen.height, mainScreen.width) }
            PropertyChanges { target: spinTheBottle; height: Math.min(mainScreen.height, mainScreen.width) }
            //PropertyChanges { target: spinTheBottle; z: 1 }
        },
        State {
            name: "SPINTHEBOTTLE"
            PropertyChanges { target: spinTheBottle; visible: true }
            PropertyChanges { target: queue; visible: false }
            PropertyChanges { target: spinTheBottle; z: 1 }
            PropertyChanges { target: tete; z: 1 }
            PropertyChanges { target: spinTheBottle; width: Math.min(mainScreen.height, mainScreen.width) }
            PropertyChanges { target: spinTheBottle; height: Math.min(mainScreen.height, mainScreen.width) }
        }
    ]
}




