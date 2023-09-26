//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

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

//    MouseArea
//    {
//        id: routeMouseArea
//        anchors.fill: route
//        acceptedButtons: Qt.LeftButton | Qt.RightButton
//        onClicked: (mouse) =>
//                   {
//                       if (mouse.button === Qt.LeftButton)
//                       {
//                           //tracksManager.setPointSelected(markerId, !markerIsSelected)
//                       }
//                       else if (mouse.button === Qt.RightButton)
//                       {
//                           routeContextMenu.popup()
//                       }
//                   }

//        Rectangle
//        {
//            anchors.fill: parent
//            color: "red"
//        }
//    }

//    Menu
//    {
//        id: routeContextMenu
//        closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape
//        MenuItem
//        {
//            text: "This is a useless context menu"
//            //                            onTriggered: tracksManager.removePointFromActiveTrack(markerId)
//        }
//    }
}
