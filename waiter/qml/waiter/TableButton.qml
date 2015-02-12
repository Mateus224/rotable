import QtQuick 2.0
import "componentCreation.js" as CreateComponent


// http://qt-project.org/doc/qt-5/qtquick-statesanimations-animations.html
// http://qt-project.org/doc/qt-5/qtquick-modelviewsdata-modelview.html


Rectangle{

    id: tableWindow

     width: 200; height: 500
     color:"#80000000"

     TestQml{

     }

    ListModel {
        id: nameModel
        ListElement { name: "Table"
                      cost: 0 }

    }
    Component {
        id: nameDelegate
        Text {
            text: name+" "+cost
            font.pixelSize: 24
        }
    }

    ListView {
        anchors.fill: parent
        clip: true
        model: nameModel
        delegate: nameDelegate
        header: bannercomponent
        footer: Rectangle {
            width: parent.width; height: 30;
            gradient: clubcolors
        }
        highlight: Rectangle {
            width: parent.width
            color: "lightgray"
            radius: 5

        }
        MouseArea{
            anchors.fill: parent
            onClicked:  CreateComponent.createCategory(tableWindow,0);
        }
    }

    Component {     //instantiated when header is processed
        id: bannercomponent
        Rectangle {
            id: banner
            width: parent.width; height: 50
            gradient: clubcolors
            border {color: "#9EDDF2"; width: 2}
            Text {
                anchors.centerIn: parent
                text: "Tables"
                font.pixelSize: 32
            }
        }
    }
    Gradient {
        id: clubcolors
        GradientStop { position: 0.0; color: "#8EE2FE"}
        GradientStop { position: 0.66; color: "#7ED2EE"}
    }
}
