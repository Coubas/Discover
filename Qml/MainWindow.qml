import QtQuick
import QtQuick.Controls

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
