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

import MapBackend 1.0

MapQuickItem
{
    id: cursor
    property string addName: "addName"
    anchorPoint.x: shape.width / 2
    anchorPoint.y:  shape.height / 2
    coordinate: mapBackend.cursorPos
    visible: mapBackend.cursorVisible
    property bool isSelected: state === "selected"

    sourceItem: CursorMarkerShape
    {
        id: shape

        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: (mouse) =>
            {
                /*if (mouse.button === Qt.LeftButton)
                {
                    cursor.state = cursor.isSelected ? "" : "selected"
                }
                else */if (mouse.button === Qt.RightButton)
                {
                    contextMenu.popup()
                }
            }
            drag
            {
                target: cursor
                axis: Drag.XAndYAxis
                onActiveChanged:
                {
                    if(!drag.active)
                    {
                        mapBackend.cursorPos = coordinate
                        inputHandler.cursorPosChanged(coordinate)

                        geoModel.updateQuery(coordinate)
                    }
                }
            }
        }

//        Text
//        {
//            text: "cursor"
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.horizontalCenter: parent.horizontalCenter
//        }
    }

    states:
    [
        State {
            name: "selected"
            PropertyChanges
            {
                target: shape
                color: Material.accent
            }
        }
    ]

    Menu
    {
        id: contextMenu
        closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape
        MenuItem
        {
            text: "Add marker ..."
            onTriggered:
            {
                //TODO
                switch (addType.currentValue) {
                case 0:
                    tracksManager.addPointToActiveTrack(cursor.addName, cursor.coordinate, insertShape.currentText)
                    break
                case 1:
                    tracksManager.addPointAfterFirstSelectedToActiveTrack(cursor.addName, cursor.coordinate, insertShape.currentText)
                    break
                case 2:
                    tracksManager.addPointAsChildOfFirstSelectedToActiveTrack(cursor.addName, cursor.coordinate, insertShape.currentText)
                    break;
                }
                mapBackend.cursorVisible = false
            }
        }

        ComboBox
        {
            id: addType
            textRole: "text"
            valueRole: "value"
            model: [
                {text: "at the end", value: 0},
                {text: "after first selected", value: 1},
                {text: "as child of first selected", value: 2}
            ]
        }

        ComboBox
        {
            id: insertShape
            model: ["pin", "circle"]
        }

        MenuItem
        {
            text: "Remove"
            onTriggered: mapBackend.cursorVisible = false
        }

        MenuItem
        {
            text: "Log Info"
            onTriggered: console.log("Marker clicked Cursor" + ", selected : " + cursor.isSelected + "\n Coordinate : " + cursor.coordinate)
        }
    }
}
