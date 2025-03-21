import QtQuick
import "Utils.js" as Utils

ListView {
    id: view
    property var values: []
    property int barCount: 0
    property int maxValue: 0
    property int barWidth: 20
    property string barColor: "red"
    property string markedColor: "blue"
    z: 0

    leftMargin: spacing
    width: (barCount) * (barWidth + spacing) - spacing + 2 * leftMargin
    orientation: Qt.Horizontal
    layoutDirection: Qt.LeftToRight

    model: ListModel {
        id: model
    }
    delegate: BarRect{ _barWidth: barWidth}

    Component.onCompleted: {
        for(let i = 0; i < values.length; i++) {
            model.append({BarColor:barColor, Value:values[i],Px:0,Py:0})
        }
    }

    function setSelectedColor(_index,_color) {
        if (_index < 0 || _index >= barCount)
            return
        model.get(_index).BarColor = _color
    }

    function setSelectedValue(_index,_value) {
        if (_index < 0 || _index >= barCount)
            return
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
            item.BarColor = barColor
        }
    }

    function refresh() {
        values = Utils.getRandomValues(barCount,maxValue)
        updateValues(values)
        setDefaultColor()
    }

    function clear() {
        model.clear()
    }

    function getRecPos(i) {
        if (i >= 0) {
            let item = model.get(i)
            return [item.Px,item.Py]
        }
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
