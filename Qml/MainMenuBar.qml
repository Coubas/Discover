//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Discover 1.0

import MapMarker 1.0


MenuBar
{
    Menu
    {
        title: "File"
        MenuItem
        {
            text:"Save active track"
            onTriggered: tracksManager.saveActiveTrackToFile()
        }

        MenuItem
        {
            text:"Load track"
            onTriggered: tracksManager.loadActiveTrackFromFile()
        }

        MenuItem
        {
            text:"Export track as GPX"
            onTriggered: tracksManager.exportActiveTrackToGPX()
        }
    }

    Menu
    {
        title: "Edit"
        MenuItem
        {
            text:"Remove All Markers"
            onTriggered: removeAllPopup.open()
        }
    }

    Menu
    {
        title: "?"
        MenuItem
        {
            text:"How to ..."
            onTriggered: helpWindowLoader.active = true

            Loader {
                id: helpWindowLoader
                active: false
                sourceComponent:
                    HelpWindow {}
            }
        }

        MenuItem
        {
            text:"About Discover"
            onTriggered: aboutPopup.open()
        }
    }

    Popup
    {
        id: removeAllPopup
        modal: true
        focus: true
        width:  500
        height: 150
        x: mainWindow.width * 0.5 - width * 0.5
        y: mainWindow.height * 0.35 - height * 0.5
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        ColumnLayout
        {
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }

            Text
            {
                text: "Are you sure you want to remove all the points ?"
            }
            RowLayout
            {
                Layout.alignment: Qt.AlignCenter | Qt.AlignHCenter
                Button
                {
                    text: "Yes"
                    onClicked:
                    {
                        tracksManager.removeAllPointsFromActiveTrack()
                        removeAllPopup.close()
                    }
                }
                Button
                {
                    text: "No"
                    onClicked: removeAllPopup.close()
                }
            }
        }
    }

    Popup
    {
        id: aboutPopup
        modal: true
        focus: true
        x: mainWindow.width * 0.5 - width * 0.5
        y: mainWindow.height * 0.35 - height * 0.5
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        RowLayout
        {
            Layout.alignment: Qt.AlignCenter | Qt.AlignLeft
            Image
            {
                source: "qrc:/icons/moto.ico"
            }
            Text
            {
                text: "Discover 1.0"
                font.bold: true
                font.pointSize: 30
            }
            ColumnLayout
            {
                Text
                {
                    text: "Copyright 2023 Lauryl Escoubas"
                    font.pointSize: 12
                }
                Text
                {
                    font.italic: true
                    font.pointSize: 8
                    text: "Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.\nDiscover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.\nYou should have received a copy of the GNU General Public License along with Discover. If not, see <https://www.gnu.org/licenses/>."
                }
            }
        }
    }
}


