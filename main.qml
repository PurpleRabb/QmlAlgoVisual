import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts
import "Utils.js" as Utils
import Sort 1.0
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Alog")

    ChartView {
        width: 400
        height: 300
        theme: ChartView.ChartThemeBrownSand
        antialiasing: true
        id: chartView
        anchors.centerIn: parent

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
                categories: ['1','2','3','4','5','6','7','8','9','10']
            }

            Text {
                id: name
                text: qsTr("Sort")
            }

            axisY: ValuesAxis {
                id: valueAxis
                max: barSeries.maxValue
            }

            BarSet {
                id: valueSet
                label: name.text
                values: Utils.getRandomValues(barCategories.count,barSeries.maxValue)
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
        Button {
            text: qsTr("Sort")
            onClicked: {
                Sort.values = valueSet.values //setValue
                Sort.speed = speedInput.text
                Sort.doAlgo(0)
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

