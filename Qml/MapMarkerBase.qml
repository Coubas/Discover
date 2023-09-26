//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

import QtQuick 2.0
import QtQuick


import QtQuick.Controls
import QtPositioning 5.6
import QtLocation 5.6
import Qt.labs.qmlmodels

import Tracks 1.0

MapQuickItem
{
    id: marker
    anchorPoint.x: shapeLoader.item.anchorX
    anchorPoint.y:  shapeLoader.item.anchorY
    coordinate: markerCoordinate

    sourceItem:
        Item
        {
            id: mapMarker
            property int shapeWidth: 45
            property int shapeHeight: 45
            Loader
            {
                id: shapeLoader
                source: getShape(markerType)

                function getShape(t)
                {
                    switch(t)
                    {
                    case "cursor":
                        return "CursorMarkerShape.qml"
                    case "pin":
                        return "PinMarkerShape.qml"
                    case "circle":
                        return "CircleMarkerShape.qml"
                    default:
                        return "PinMarkerShape.qml"
                    }
                }
            }


            MouseArea
            {
                id: mouseArea
                anchors.fill: shapeLoader
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: (mouse) =>
                {
//                    console.log("Click on marker " + markerId + " " + markerCoordinate)
                    if (mouse.button === Qt.LeftButton)
                    {
                        tracksManager.setPointSelected(markerId, !markerIsSelected)
                    }
                    else if (mouse.button === Qt.RightButton)
                    {
                        contextMenu.popup()
                    }
                }

                drag
                {
                    target: marker
                    axis: Drag.XAndYAxis
                    onActiveChanged:
                    {
                        if(!drag.active)
                        {
                            tracksManager.setPointCoordinate(markerId, coordinate)
                        }
                    }
                }
            }

            Text
            {
                text: markerLinearIndexInActiveHierarchy
                font.pointSize: mapMarker.shapeWidth * 0.3
                font.bold: true
                color: markerIsSelected ? Material.primary : "white"

                anchors.verticalCenter: shapeLoader.verticalCenter
                anchors.horizontalCenter: shapeLoader.horizontalCenter
            }

            Text
            {
                text: markerLinearIndexInActiveHierarchy
                font.pointSize: mapMarker.shapeWidth * 0.25
                font.bold: true
                color: markerIsSelected ? "white" : Material.primary

                anchors.verticalCenter: shapeLoader.verticalCenter
                anchors.horizontalCenter: shapeLoader.horizontalCenter
            }

            state: markerIsSelected ? "selected" : ""
            states:
            [
                State {
                    name: "selected"
                    PropertyChanges
                    {
                        target: shapeLoader.item
                        filled: true
                    }
                }
            ]

            Menu
            {
                id: contextMenu
                closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape
                MenuItem
                {
                    text: "Remove"
                    onTriggered: tracksManager.removePointFromActiveTrack(markerId)
                }
//                MenuItem
//                {
//                    text: "Log Info"
//                    onTriggered: console.log("Marker id: " + markerId + ", selected: " + markerIsSelected + ", state:" + mapMarker.state +
//                                             "\nType: " + markerType + ", Pos: " + markerCoordinate + ", active: " + markerIsActive + ", loop: " + markerIsLoop)
//                }
            }
        }
}
