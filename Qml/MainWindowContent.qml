import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.0
import QtLocation
import Qt.labs.qmlmodels

import Discover 1.0
import MapMarker 1.0

Rectangle
{
    id: rectangle1
    width: 1920
    height: 1080
    anchors.fill: parent
    opacity: 1
    visible: true

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        rows: 2
        columns: 2

        Item {
            id: trackTree
            width: 350
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.rowSpan: 2
            Layout.columnSpan: 1

            ColumnLayout {
                id: columnLayout
                anchors.fill: parent

                Item {
                    id: trackName
                    Layout.fillWidth: true
                    height: 50
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                    Rectangle
                    {
                        anchors.fill: parent
                        color: "transparent"
//                        border.color: "yellow"
//                        border.width: 2

                        TextInput
                        {
                            anchors.fill: parent
                            text: tracksManager.activeTrackName
                            font.pixelSize: 30
                            horizontalAlignment: Text.AlignHCenter
                            onEditingFinished:
                            {
                                trackName.focus = false
                                tracksManager.activeTrackName = text
                            }
                        }
                    }
                }

                Item
                {
                    id: treeViewRoot
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                    Rectangle
                    {
                        anchors.fill: parent
                        color: "transparent"
//                        border.color: "red"
//                        border.width: 2

//                        ListView {
//                            id: listView
//                            width: parent.width
//                            height: parent.height
//                            interactive: false
//                            property int dragItemIndex: -1
//                            model: MapMarkerModel
//                            {
//                                list: tracksManager.activeTrack.points
//                            }
//                            delegate: MapMarkerListViewItem {}
//                        }

                        TreeView {
                            id: treeView
                            anchors.fill: parent
                            interactive: false
                            property int dragMarkerId: -1
                            model: tracksManager.treeTrack.treeModel
                            delegate: MapMarkerTreeViewDelegate{}
                            Component.onCompleted: expandRecursively()
                        }
                    }
                }

                Item {
                    id: pathManagement
                    Layout.fillWidth: true
                    height: 250
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                    Rectangle
                    {
                        anchors.fill: parent
                        color: "transparent"
//                        border.color: "green"
//                        border.width: 2
                        ColumnLayout
                        {
                            anchors.fill: parent

//                            RowLayout
//                            {
//                                width: parent.width
//                                Text
//                                {
//                                    text: "Travel Mode: "
//                                }
//                                ComboBox
//                                {
//                                    id: travelModeSetting
//                                    width: parent.width
//                                    textRole: "text"
//                                    valueRole: "value"
//                                    model: ListModel
//                                    {
//                                        ListElement { text: "Car"; value: RouteQuery.CarTravel }
//                                        ListElement { text: "Pedestrian"; value: RouteQuery.PedestrianTravel }
//                                        ListElement { text: "Bicycle"; value: RouteQuery.BicycleTravel }
//                                        ListElement { text: "Public"; value: RouteQuery.PublicTransitTravel }
//                                        ListElement { text: "Truck"; value: RouteQuery.TruckTravel }
//                                    }
//                                }
//                            }

//                            RowLayout
//                            {
//                                width: parent.width
//                                Text
//                                {
//                                    text: "Path Mode: "
//                                }
//                                ComboBox
//                                {
//                                    id: pathModeSetting
//                                    width: parent.width
//                                    textRole: "text"
//                                    valueRole: "value"
//                                    model: ListModel
//                                    {
//                                        ListElement { text: "Shortest"; value: RouteQuery.ShortestRoute }
//                                        ListElement { text: "Fastest"; value: RouteQuery.FastestRoute }
//                                        ListElement { text: "MostEconomic"; value: RouteQuery.MostEconomicRoute }
//                                        ListElement { text: "MostScenic"; value: RouteQuery.MostScenicRoute }
//                                    }
//                                }
//                            }

                            Button
                            {
                                Layout.alignment: Qt.AlignCenter
                                text: "Compute path"
                                //onClicked: mapView.updateRouteQuery(travelModeSetting.currentValue, pathModeSetting.currentValue)
                                onClicked: mapView.updateRouteQuery()
                            }
                        }
                    }
                }
            }
        }

        Item {
            id: item1
            width: 200
            height: 400
            Layout.fillHeight: true
            Layout.fillWidth: true

            DiscoverMapView
            {
                id: mapView
                objectName: "mapView"
                anchors.fill: parent
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
