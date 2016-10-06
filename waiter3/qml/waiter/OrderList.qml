import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ListView {

    id: orderList

    width: parent.width * 0.35

    spacing: 10

    model: orderboard

    delegate: OrderListElement {}
}
