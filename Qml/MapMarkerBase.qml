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
                text: markerId
                font.pointSize: 24
                color: "red"

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
                MenuItem
                {
                    text: "Log Info"
                    onTriggered: console.log("Marker id: " + markerId + ", selected: " + markerIsSelected + ", state:" + mapMarker.state +
                                             "\nType: " + markerType + ", Pos: " + markerCoordinate)
                }
            }
        }
}
