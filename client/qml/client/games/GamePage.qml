import QtQuick 2.4
import "SpinTheBottle/"
import "BigKingsCup/"
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
            property int colapsed_

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
                    id: game0
                    color:parent.color(0,0)
                    gameName:"Spin the Bottle"
                    infoString: "<h1>FLASCHENDREHEN</h1><blockquote></blockquote>
                                 <h2>Anforderungen:</h2>Jeder Spieler benötigt ein Alkoholisches Getränk<blockquote></blockquote>
                                 <h2>Spielregeln:</h2> auf wenn die Flsche zeigt nimmt ein Schluck aus der Bierflasche bzw. vom seinen Drink"
                    id_: 0
                }
                EmptyGridRect{
                    id_: 1
                    gameName:"Big Kings Cup"
                    infoString:"<h1>Spielregeln Kings Cup</h1><blockquote></blockquote>
                                <h2>Anforderungen:</h2> Jeder Spieler benötigt ein Alkoholisches Getränk. Zusätzlich wird in die Mitte
                                des tisches ein 6 cl Glas mit Vodka gestellt.<blockquote></blockquote>
                                <h2>Spielregeln:</h2> Jeder Spieler zieht eine Karte im Uhrzeigersinn. Bei jeder Karte wird eine Aufgabe gestellt.
                                Derjenige der den dritten König zieht hat das Spiel verloren und ext den 6 cl Vodka."
                    color:parent.color(0,1)
                }
                EmptyGridRect{
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
        /*Behavior on width {
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
        }*/
        Behavior on z {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
    }

    BigKingsCup{
        id: bigKingsCup
        visible: false
    }

    states: [
        State {
            name: "DEFAULT"
            PropertyChanges { target: game0; state: "COLLAPSED" }
            PropertyChanges { target: spinTheBottle; visible: false }
            PropertyChanges { target: queue; visible: true }
            PropertyChanges { target: spinTheBottle; z: 0 }
            PropertyChanges { target: spinTheBottle; width: Math.min(mainScreen.height, mainScreen.width) }
            PropertyChanges { target: spinTheBottle; height: Math.min(mainScreen.height, mainScreen.width) }

        },
        State {
            name: "SPINTHEBOTTLE"
            PropertyChanges { target: spinTheBottle; visible: true }
            PropertyChanges { target: queue; visible: false }
            PropertyChanges { target: spinTheBottle; z: 1 }
            PropertyChanges { target: spinTheBottle; width: Math.min(mainScreen.height, mainScreen.width) }
            PropertyChanges { target: spinTheBottle; height: Math.min(mainScreen.height, mainScreen.width) }
        },
        State {
            name: "BIGKINGSCUP"
            PropertyChanges { target: bigKingsCup; visible: true }
            PropertyChanges { target: queue; visible: false }
            PropertyChanges { target: bigKingsCup; z: 1 }
            PropertyChanges { target: bigKingsCup; width: Math.min(mainScreen.height, mainScreen.width) }
            PropertyChanges { target: bigKingsCup; height: Math.min(mainScreen.height, mainScreen.width) }
        }
    ]
}




