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
                //console.log("onSort_valuesChanged");
                barSeries.clear()
                barSeries.append(name.text,sort_values) //call getValue
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

            function refresh() {
                barSeries.clear()
                barSeries.values = Utils.getRandomValues(barCategories.count,barSeries.maxValue)
                barSeries.append(name.text, values);
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
                Sort.values = barSeries.values //setValue
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

