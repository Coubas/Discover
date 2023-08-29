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
                if (mouse.button === Qt.LeftButton)
                {
                    cursor.state = cursor.isSelected ? "" : "selected"
                }
                else if (mouse.button === Qt.RightButton)
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
                color: "red"
            }
        }
    ]

    Menu
    {
        id: contextMenu
        closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape
        MenuItem
        {
            text: "Add marker at " + insertIdSlider.value
            onTriggered:
            {
                tracksManager.addPointToActiveTrack(cursor.coordinate, insertShape.currentText, insertIdSlider.value)
                mapBackend.cursorVisible = false
            }
        }

        Slider
        {
            id: insertIdSlider
            from: 0
            to: tracksManager.activeTrackSize
            value: tracksManager.activeTrackSize
            snapMode: Slider.SnapAlways
            stepSize: 1
            leftPadding: 25
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
