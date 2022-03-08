import QtQuick 2.0
import QtQuick.Window 2.3
import QtCharts 2.3
import "Utils.js" as Utils
import Sort 1.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3

Window {
    width: 800
    height: 480
    visible: true
    title: qsTr("Alog")

    MCanvas {
        id: mCanvas
        width: 800
        height: 480
    }


    MyChartView {
        id: chartView
        property var sort_values : Sort.values
        property var sortList : Sort.sortlist

        anchors.centerIn: parent
        spacing: 5
        height: 300
        barCount: 15
        maxValue: 200
        barWidth: 30
        barColor: "peachpuff"
        markedColor: "plum"
        property var temp : 0

        values: Utils.getRandomValues(barCount,maxValue)

        onSort_valuesChanged: {
            if (Sort.values.length !== 0) {  //call getValue
                console.log(sort_values)
                chartView.updateValues(sort_values)
            }
        }

        Connections {
            target: Sort
            onAlgoStatus: function onAlgoStatus(fromCppMsg) {
                let _msg = JSON.parse(fromCppMsg)
                for (let i=0; i < _msg.Marked.length; i++) {
                    chartView.setSelectedColor(_msg.Marked[i], chartView.markedColor);
                }
                for (let j=0; j < _msg.Restored.length; j++) {
                    chartView.setSelectedColor(_msg.Restored[j], chartView.barColor);
                }
                if (_msg.Swaped[0] >=0 && _msg.Swaped[1] >= 0) {
                    let _index1 = _msg.Swaped[0]
                    let _index2 = _msg.Swaped[1]
                    let _interval = (_index2 - _index1)
                    console.log("swapIndex  ",_index1,_index2);
                    let arrowLength = 25
                    let _x = chartView.x + (_index1 + 1) * chartView.spacing + (_index1 + 0.5) * chartView.barWidth
                    let _y = chartView.y + arrowLength
                    let _endX = chartView.x + (_index2+1) * chartView.spacing + (_index2 + 0.5) * chartView.barWidth
                    //fromx,fromy,tox,toy,spacing,barWidth,interval,arrowLength
                    mCanvas.drawArrowLineFromXtoY(_x,_y,_endX,_y,chartView.spacing,chartView.barWidth,_interval,arrowLength)
                }
            }
        }
    }

    RowLayout {
        anchors.top: chartView.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 3

        ComboBox {
            id: comboBox
            model: ListModel {
                id: model
            }

            focus: true
            onActivated: {
                console.log(currentIndex)
                Sort.switchAlgo(chartView.sortList[currentIndex])
                chartView.refresh()
            }
            Component.onCompleted: {
                let len = chartView.sortList.length
                for (let i = 0; i < len; i++) {
                    model.append({text:chartView.sortList[i]})
                }
                currentIndex = 0;
            }
        }

        Button {
            text: qsTr("Sort")
            onClicked: {
                Sort.values = chartView.values //setValue
                Sort.speed = speedInput.text
                Sort.doAlgo(comboBox.currentIndex)
            }
        }

        Button {
            text: qsTr("Reset")
            id: btnReset
            onClicked: {
                Sort.reset() //先停止，再刷新
                mCanvas.clear()
                chartView.refresh()
            }
        }

        Label {
            id: label
            text: "speed: "
        }

        Rectangle {
            width: 50
            height: btnReset.height
            color: "lightgrey"
            border.color: "black"
            TextInput {
                anchors.centerIn: parent
                id: speedInput
                text: "500"
                maximumLength: 5
            }
        }
    }


    /* ChartView {
        width: parent.width * 0.8
        height: parent.height * 0.8
        theme: ChartView.ChartThemeBrownSand
        antialiasing: true
        id: chartView
        anchors.centerIn: parent

        property var sortList : ["Buble", "Selection"]
        property var sort_values : Sort.values //call getValue

        onSort_valuesChanged: {
            if (Sort.values.length !== 0) {  //call getValue
                valueSet.values = sort_values
            }
        }

        BarSeries {
            id: barSeries
            property int maxValue: 100
            property var values: []

            axisX: BarCategoryAxis {
                id: barCategories
                categories: ['1','2','3','4','5','6','7','8',
                            '9','10','11','12','13','14','15',
                            '16','17','18','19','20']
            }

            Text {
                id: name
                text: qsTr("Sort")
            }

            axisY: ValuesAxis {
                id: valueAxis
                max: barSeries.maxValue + 10
            }

            BarSet {
                id: valueSet
                label: comboBox.textAt(comboBox.currentIndex)
                values: Utils.getRandomValues(barCategories.count,barSeries.maxValue)
                borderColor: "white"

            }

            function refresh() {
                valueSet.values = Utils.getRandomValues(barCategories.count,barSeries.maxValue)
            }

            Component.onCompleted: {
                console.log("barCategories.count:"+barCategories.count)
                refresh()
            }
        }
    } */

    /*RowLayout {
        anchors.top: chartView.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        ComboBox {
            id: comboBox
            model: chartView.sortList

            onActivated: {
                console.log(currentIndex)
                Sort.switchAlgo(currentIndex)
            }
        }

        Button {
            text: qsTr("Sort")
            onClicked: {
                Sort.values = valueSet.values //setValue
                Sort.speed = speedInput.text
                Sort.doAlgo(comboBox.currentIndex)
            }
        }

        Button {
            text: qsTr("Reset")
            id: btnReset
            onClicked: {
                barSeries.refresh()
                Sort.reset()
            }
        }

        Label {
            id: label
            text: "speed:  "
        }

        Rectangle {
            width: 50
            height: btnReset.height
            color: "lightgrey"
            anchors.left:  label.right
            border.color: "black"
            TextInput {
                anchors.centerIn: parent
                id: speedInput
                text: "100"
                maximumLength: 5
            }
        }
    }*/

}

