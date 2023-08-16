import QtQuick 2.0
import QtQuick


import QtQuick.Controls
import QtPositioning 5.6
import QtLocation 5.6
import Qt.labs.qmlmodels

import Tracks 1.0

MouseArea
{
    id: mouseArea
    property var visualComponentId
    anchors.fill: parent
    acceptedButtons: Qt.LeftButton | Qt.RightButton
    onClicked: (mouse) =>
    {
        if (mouse.button === Qt.LeftButton)
        {
            tracksManager.setPointSelected(markerId, !markerIsSelected)
            mouseArea.state = markerIsSelected ? "selected" : ""
        }
        else if (mouse.button === Qt.RightButton)
        {
            contextMenu.popup()
        }
    }

    Text
    {
        text: markerId
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    states:
    [
        State {
            name: "selected"
            PropertyChanges
            {
                target: mouseArea.visualComponentId
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
            text: "Log Info"
            onTriggered: console.log("Marker clicked " + markerId + ", selected : " + markerIsSelected + ", state :" + mouseArea.state)
        }
    }
}
