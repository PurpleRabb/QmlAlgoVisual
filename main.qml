import QtQuick 2.2
import QtQuick.Window 2.15
import QtCharts 2.3
import "Utils.js" as Utils
import Sort 1.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Window {
    width: 800
    height: 480
    visible: true
    title: qsTr("Alog")


    MyChartView {
        id: chartView
        property var sort_values : Sort.values
        property var sortList : ["Buble", "Selection"]

        anchors.centerIn: parent
        spacing: 5
        height: 200
        barCount: 15
        maxValue: 150
        barWidth: 20
        barColor: "peachpuff"
        markedColor: "plum"

        values: Utils.getRandomValues(barCount,maxValue)

        onSort_valuesChanged: {
            if (Sort.values.length !== 0) {  //call getValue
                console.log(sort_values)
                chartView.updateValues(sort_values)
            }
        }

        Connections {
            target: Sort
            function onAlgoStatus(fromCppMsg) {
                let _msg = JSON.parse(fromCppMsg)
                for (let i=0; i < _msg.Marked.length; i++) {
                    chartView.setSelectedColor(_msg.Marked[i], chartView.markedColor);
                }
                for (let j=0; j < _msg.Restored.length; j++) {
                    chartView.setSelectedColor(_msg.Restored[j], chartView.barColor);
                }
            }
        }
    }

    RowLayout {
        anchors.top: chartView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 6

        ComboBox {
            id: comboBox
            model: chartView.sortList
            focus: true
            onActivated: {
                console.log(currentIndex)
                Sort.switchAlgo(currentIndex)
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
                chartView.refresh()
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
            border.color: "black"
            TextInput {
                anchors.centerIn: parent
                id: speedInput
                text: "300"
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

