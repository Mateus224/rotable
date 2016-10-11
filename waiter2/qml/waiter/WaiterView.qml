import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

RowLayout{
    id: mainLayout
    spacing: 15

    anchors.margins: margin
    anchors.fill: parent

    MenuLayout {
        id: menuLayout
    }
    OrderLayout {
        id: orderLayout
        spacing: 10
    }
}
