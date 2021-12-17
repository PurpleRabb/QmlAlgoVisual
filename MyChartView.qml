import QtQuick 2.0
import "Utils.js" as Utils

ListView {
    id: view
    property var values: []
    orientation: Qt.Horizontal
    layoutDirection: Qt.LeftToRight
    spacing: 3

    model: ListModel {
        id: model
    }
    delegate: BarRect{}

    Component.onCompleted: {
        for(let i = 0; i < values.length; i++) {
            model.append({BarColor:"red", Value:values[i]})
        }
    }

    function setSelectedColor(_index,_color) {
        model.get(_index).BarColor = _color
    }

    function setSelectedValue(_index,_value) {
        let item = model.get(_index)
        item.Value = _value
        item.height = _value
    }

    function updateValues(_values) {
        for(let i = 0; i < _values.length; i++) {
            let item = model.get(i)
            item.Value = _values[i]
            item.height = _values[i]
        }
    }

    function setDefaultColor() {
        for(let i = 0; i < model.count; i++) {
            let item = model.get(i)
            item.BarColor = "red"
        }
    }

    function refresh() {
        values = Utils.getRandomValues(15,100)
        updateValues(values)
        setDefaultColor()
    }

    function clear() {
        model.clear()
    }


    //画边框
    Rectangle {
        z: -2
        anchors.fill: view
        color: "white"
        border.width: 1
        border.color: "black"

        // 使用矩形覆盖上层Rectangle的边框
        Rectangle {
            z: -1
            color: parent.color
            border.width: 0
            anchors.fill: parent
            // 使用Margin来确定是否显示边框
            anchors.leftMargin: 1
            anchors.topMargin: 1
            anchors.rightMargin: 1
            anchors.bottomMargin: 0
        }
    }
}
