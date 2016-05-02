import QtQuick 2.0

Rectangle {
    id: t
    property string gameName: ""
    property int buttonMarginH: parent.parent.width  * 0.015
    property int buttonMarginV: parent.parent.height * 0.025
    property int buttonWidth:  (parent.parent.width  - buttonMarginH) / 5.01 - buttonMarginH
    property int buttonHeight: (parent.parent.height - buttonMarginV) / 3.01 - buttonMarginV
    width: buttonWidth
    height: buttonHeight

    Text{
        id:gameText
        anchors.fill: parent
        wrapMode: Text.Wrap
        font.family: "FreeSans"
        color: "#FFFFFFFF"
        font.bold: true
        font.pixelSize: parent.buttonHeight * 0.175
        anchors.centerIn: parent
        font.capitalization: Font.AllUppercase
        text: gameName
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

    }

}
