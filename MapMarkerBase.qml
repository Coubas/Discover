import QtQuick 2.0

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
    onClicked:
    {
        if (mouse.button === Qt.LeftButton)
        {
            tracksManager.setPointSelected(markerId, !markerIsSelected)
            markerIsSelected ? mouseArea.state = "selected" : mouseArea.state = ""
        }
        else if (mouse.button === Qt.RightButton)
        {
            tracksManager.removePointFromActiveTrack(markerId)
        }

        console.log("Marker clicked " + markerId + ", selected : " + markerIsSelected + ", state :" + mouseArea.state)
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
}
