import QtQuick 2.0

Component {
    id : barRect
    Rectangle {
        anchors.bottom: parent.bottom
        width: 20
        height: Value
        border.width: 1
        border.color: 'black'
        color: BarColor

        Text {
            id: name
            anchors.centerIn: parent
            text: Value
        }

        Behavior on height {PropertyAnimation {duration: 100} }

    }
}
