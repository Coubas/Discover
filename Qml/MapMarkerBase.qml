import QtQuick 2.0
import QtQuick


import QtQuick.Controls
import QtPositioning 5.6
import QtLocation 5.6
import Qt.labs.qmlmodels

import Tracks 1.0

MapQuickItem
{
    id: cursor
    anchorPoint.x: shapeLoader.width / 2
    anchorPoint.y:  shapeLoader.height / 2
    coordinate: markerCoordinate

    sourceItem:
        Item
        {
            id: mapMarker
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
                    if (mouse.button === Qt.LeftButton)
                    {
                        tracksManager.setPointSelected(markerId, !markerIsSelected)
                        mapMarker.state = markerIsSelected ? "selected" : ""
                    }
                    else if (mouse.button === Qt.RightButton)
                    {
                        contextMenu.popup()
                    }
                }
            }

            Text
            {
                text: markerId
                anchors.verticalCenter: shapeLoader.verticalCenter
                anchors.horizontalCenter: shapeLoader.horizontalCenter
            }

            states:
            [
                State {
                    name: "selected"
                    PropertyChanges
                    {
                        target: shapeLoader.item
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
                    text: "Remove"
                    onTriggered: tracksManager.removePointFromActiveTrack(markerId)
                }
                MenuItem
                {
                    text: "Change index to " + changeIdSlider.value
                    enabled: changeIdSlider.value != markerId
                    onTriggered: tracksManager.changePointIndexFromActiveTrack(markerId, changeIdSlider.value)
                    //onTriggered: console.log("changePointIndexFromActiveTrack("+markerId+", "+changeIdSlider.value+")")
                }
                Slider
                {
                    id: changeIdSlider
                    from: 0
                    value: markerId+1
                    to: tracksManager.activeTrackSize - 1
                    snapMode: Slider.SnapAlways
                    stepSize: 1
                    leftPadding: 25
                }
                MenuItem
                {
                    text: "Log Info"
                    onTriggered: console.log("Marker clicked " + markerId + ", selected : " + markerIsSelected + ", state :" + mapMarker.state + "\nType : " + markerType)
                }
            }
        }
}
