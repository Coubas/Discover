import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls 2.0

import Discover 1.0

Rectangle
{
    anchors.fill: parent
    opacity: 1
    visible: true
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Item {
            id: item1
            width: 200
            height: 400
            Layout.fillHeight: true
            Layout.fillWidth: true

            MapView
            {
                objectName: "mapView"
                anchors.fill: parent
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        Rectangle {
            id: rectangle
            width: 0
            height: 0
            visible: true
            color: "#ffffff"
            radius: 0
            Layout.minimumHeight: 100
            Layout.topMargin: 0
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            Layout.fillHeight: false
            Layout.fillWidth: true
            clip: false
            Layout.preferredWidth: -1

            ColumnLayout {
                id: columnLayout1
                visible: true
                anchors.fill: parent
                layoutDirection: Qt.LeftToRight
                spacing: 2

                RowLayout {
                    id: rowLayout
                    width: 100
                    height: 100
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    layoutDirection: Qt.LeftToRight
                    spacing: 5

                    Text {
                        id: labelClickLat
                        text: qsTr("Latitude : ")
                        font.pixelSize: 14
                        Layout.fillHeight: false
                    }

                    Text {
                        id: clickLat
                        objectName: "clickLat"
                        text: qsTr("---")
                        font.pixelSize: 14
                        Layout.rightMargin: 100
                    }

                    Text {
                        id: labelClickLon
                        text: qsTr("Longitude : ")
                        font.pixelSize: 14
                    }

                    Text {
                        id: clickLon
                        objectName: "clickLon"
                        text: qsTr("---")
                        font.pixelSize: 14
                    }
                }

                RowLayout {
                    id: rowLayout1
                    width: 0
                    height: 0
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Text {
                        id: labelClickAdress
                        text: qsTr("Adress : ")
                        font.pixelSize: 14
                    }

                    Text {
                        id: clickAdress
                        objectName: "clickAdress"
                        text: qsTr("---")
                        font.pixelSize: 14
                    }
                }
            }
        }
    }
}
