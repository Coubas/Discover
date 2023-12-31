//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

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
            width: 400
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.rowSpan: 2
            Layout.columnSpan: 1

            ColumnLayout {
                id: columnLayout
                anchors.fill: parent
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop

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
                            id: trackNameInput
                            anchors.fill: parent
                            text: tracksManager.activeTrackName
                            font.pixelSize: 30
                            horizontalAlignment: Text.AlignHCenter
                            onEditingFinished:
                            {
                                trackNameInput.focus = false
                                tracksManager.activeTrackName = text
                            }

                            property string placeholderText: "Track name..."

                            Text {
                                text: trackNameInput.placeholderText
                                color: "#aaa"
                                font.pixelSize: 30
                                horizontalAlignment: Text.AlignHCenter
                                visible: !trackNameInput.text
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

                    TreeView {
                        id: treeView
                        anchors.fill: parent
                        //interactive: false
                        clip: true
                        boundsBehavior: Flickable.StopAtBounds
                        property int dragMarkerId: -1
                        property int dragOveredRow: -1
                        property var dragOveredRowPart: "none"
                        model: tracksManager.activeTrack.treeModel
                        delegate: MapMarkerTreeViewDelegate{}
                        Component.onCompleted: expandRecursively()

                        function resetDragInfo()
                        {
                            dragOveredRow = -1
                            dragOveredRowPart = "none"
                        }

                        ScrollBar.vertical: ScrollBar
                        {
                            policy: ScrollBar.AsNeeded
                            wheelEnabled: true
                        }

                        ScrollBar.horizontal: ScrollBar
                        {
                            policy: ScrollBar.AsNeeded
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

                            RowLayout
                            {
                                Layout.alignment: Qt.AlignCenter
                                Button
                                {
                                    Layout.alignment: Qt.AlignCenter
                                    text: "Compute path"
                                    highlighted: true
                                    Material.background: Material.primary
                                    //onClicked: mapView.updateRouteQuery(travelModeSetting.currentValue, pathModeSetting.currentValue)
                                    onClicked: mapView.updateRouteQuery()
                                }

                                Button
                                {
                                    Layout.alignment: Qt.AlignCenter
                                    text: "X"
                                    highlighted: true
                                    Material.background: Material.primary
                                    onClicked: mapView.clearRouteQuery()
                                }
                            }

                            RowLayout
                            {
                                Text {
                                    id: labelTrackLength
                                    text: qsTr("Track Length : ")
                                    font.pixelSize: 14
                                    Layout.fillHeight: false
                                }

                                Text {
                                    id: trackLength
                                    text: qsTr("---")
                                    font.pixelSize: 14
                                    Layout.rightMargin: 100
                                }
                            }

                            RowLayout
                            {
                                Text {
                                    id: labelTrackDuration
                                    text: qsTr("Track Duration : ")
                                    font.pixelSize: 14
                                    Layout.fillHeight: false
                                }

                                Text {
                                    id: trackDuration
                                    text: qsTr("---")
                                    font.pixelSize: 14
                                    Layout.rightMargin: 100
                                }
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
