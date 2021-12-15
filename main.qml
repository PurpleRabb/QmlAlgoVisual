import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts
import "Utils.js" as Utils
import Sort 1.0
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 800
    height: 480
    visible: true
    title: qsTr("Alog")

    ChartView {
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
                label: name.text
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
    }

    RowLayout {
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
    }

}

