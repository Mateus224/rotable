import QtQuick 2.0
import QtMultimedia 5.0
import "componentCreation.js" as CreateComponent


Rectangle {
    id: appWindow
    width: 900; height: 600
    color:"#800000FF"

    TableButton{}

    TableGrid{}
    ListView {
        width: 200; height: 200

        model: myModel
        delegate: Rectangle {
            height: 25
            width: 100
            color: model.modelData.color
            Text { text: name }
        }
    }

}

