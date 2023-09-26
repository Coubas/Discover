import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Discover 1.0

import MapMarker 1.0


ApplicationWindow
{
    id: mainWindow
    visible: true
    width: 1920
    height: 1080

    menuBar: MenuBar
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
                text:"Export active track to GPX"
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
    }

    Popup {
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

//    header: ToolBar
//    {
//        // ...
//    }

//    footer: TabBar
//    {
//        // ...
//    }

    MainWindowContent {}
}
