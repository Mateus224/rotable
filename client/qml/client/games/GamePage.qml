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
                    infoString: "<h1>FLASCHENDREHEN:</h1>
                                 <b>auf wenn die Flsche zeigt nimmt ein Schluck aus der Bierflasche bzw. vom seinen Drink</b>"
                    id_: 0
                }
                EmptyGridRect{
                    id_: 1
                    gameName:"Big Kings Cup"
                    infoString:"<h1>Spielregeln Kings Cup:</h1>
<b>2</b> steht für dich. Wenn ein Spieler eine 2 zieht (egal, welche Farbe), dann kann er einen anderen Spieler aussuchen, der dann trinken muss. Die gewählte Person muss so lange trinken, wie es zu Beginn des Spiels ausgemacht wurde.
<blockquote></blockquote>
<b>3</b> steht für mich. Wenn ein Spieler eine 3 zieht, muss er oder sie selbst trinken.
<blockquote></blockquote>
<b>4</b> steht für Boden. Wenn ein Spieler eine 4 zieht, müssen sich alle nach unten beugen und den Boden so schnell wie möglich berühren. Der Letzte, der den Boden berührt, trinkt.
<blockquote></blockquote>
<b>5</b> steht für Jungs. Wenn ein Spieler eine 5 zieht, müssen alle Männer am Tisch trinken.
<blockquote></blockquote>
<b>6</b> steht für Mädels. Wenn ein Spieler eine 6 zieht, müssen alle Mädels am Tisch trinken.
<blockquote></blockquote>
<b>7</b> steht für Himmel. Wenn ein Spieler eine 7 zieht, müssen alle am Tisch ihre Hände so schnell wie möglich in die Luft heben. Der Letzte muss trinken.
<blockquote></blockquote>
<b>8</b> steht für Partner. Wenn ein Spieler eine 8 zieht, muss er eine andere Person am Tisch aussuchen, die immer trinken muss, wenn die erste Person trinkt, und umgekehrt. Das geht so lange weiter, bis jemand anderes eine 8 zieht. Wenn einer der Spieler vergisst, zu trinken, wenn sein oder ihr “Partner” trinkt, dann muss er einen zusätzlichen Strafschluck machen.
<blockquote></blockquote>
<b>9</b> steht für Reim. Wenn ein Spieler eine 9 zieht, dann muss er ein Wort aussuchen und es laut sagen, wie “Ratte”. Im Uhrzeigersinn muss dann jeder Spieler ein Wort sagen, das sich darauf reimt, wie z.B. Platte, Matte, Debatte usw. und man muss es in unter 5 Sekunden sagen. Das geht so lange um den Tisch herum, bis einem Spieler kein Reimwort mehr einfällt. Der Spieler trinkt.
<blockquote></blockquote>
<b>10</b> steht für “Ich habe noch nie…”. Wenn ein Spieler eine 10 zieht, müssen alle am Tisch drei Finger hochhalten. Beginnend mit der Person, die die Karte gezogen hat, muss jeder einen Satz mit “Ich habe noch nie…” beginnen und dann etwas sagen, was er/sie noch nie gemacht hat. Wenn andere Spieler am Tisch diese Sache schon einmal gemacht haben, senken sie einen Finger. Das geht weiter um den Tisch herum. Die erste Person oder Personen mit keinen Fingern mehr in der Luft muss trinken.
<blockquote></blockquote>
<b>Bube</b> steht für Regel. Wenn ein Spieler einen Buben zieht, dann kann er eine Regel aufstellen, die das ganze Spiel hindurch befolgt werden muss. Die Regel könnte sein, dass niemand fluchen darf, dass es verboten ist, auf die Toilette zu gehen, oder dass niemand jemand anderen beim Vornamen nennen darf. Jeder Spieler, der die Regel bricht, muss einen Strafschluck machen. Lies untenstehend mehr zu beliebten Regeln.
<blockquote></blockquote>
<b>Dame</b> steht für Fragesteller. Wenn ein Spieler eine Dame zieht, wird er oder sie Fragesteller. Bis ein anderer Spieler eine Dame zieht, können alle auf die Fragen des Fragestellers nur mit einer Gegenfrage antworten. Wenn zum Beispiel Thomas der Fragesteller ist und Simon fragt: “Wie spät ist es?”, dann müsste Simon antworten: “Ist es 2 Uhr?” Wenn Simon nicht mit einer Frage antwortet, muss er trinken.
<blockquote></blockquote>
<b>König</b> steht für King's Cup. Wenn ein Spieler einen König zieht, muss er sein Getränk in den Becher in der Mitte vom Tisch leeren. Wenn der vierte König gezogen wird, muss derjenige Spieler die Mischung im Becher austrinken und signalisiert damit das Ende des Spiels. Wenn ihr mit einer Dose spielt, könnte ein König bedeuten, dass du dein derzeitiges Getränk austrinken musst oder ihr könntet eine andere Regel erfinden.
<blockquote></blockquote>
<b>Ass</b> steht für Wasserfall. Wenn ein Spieler ein Ass zieht, müssen alle am Tisch einen Zug aus ihrem Getränk nehmen, beginnend mit dem Spieler, der die Karte gezogen hat. Jeder Spieler darf erst zu trinken beginnen, wenn die Person zu seiner Rechten begonnen hat, zu trinken und darf erst aufhören, wenn die Person zur Rechten aufgehört hat, zu trinken. Wenn du also links von dem Spieler sitzt, der die Karte gezogen hat, dann darfst du nicht aufhören zu trinken, bis alle am Tisch damit aufgehört haben."
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




