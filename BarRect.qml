import QtQuick 2.0


Rectangle {
    property int _barWidth

    anchors.bottom: parent.bottom
    width: _barWidth
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

    Component.onCompleted: {
        Px = x;
        Py = y
    }

}

