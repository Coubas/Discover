import QtQuick
import QtQuick 2.0

import Qt.labs.qmlmodels
import QtQuick.Controls
import QtLocation
import QtPositioning

import MapHelper 1.0
import MapBackend 1.0
import MapMarker 1.0
import Inputs 1.0
import Tracks 1.0

MapRoute
{
    id: route
    route: routeData
    line.color: Material.primary
    line.width: 5
    //smooth: true
    opacity: 0.8

    MouseArea
    {
        id: routeMouseArea
        anchors.fill: route
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: (mouse) =>
                   {
                       if (mouse.button === Qt.LeftButton)
                       {
                           //tracksManager.setPointSelected(markerId, !markerIsSelected)
                       }
                       else if (mouse.button === Qt.RightButton)
                       {
                           routeContextMenu.popup()
                       }
                   }
    }

    Menu
    {
        id: routeContextMenu
        closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape
        MenuItem
        {
            text: "This is a useless context menu"
            //                            onTriggered: tracksManager.removePointFromActiveTrack(markerId)
        }
    }
}
