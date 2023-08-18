import QtQuick
import QtQuick.Controls

import Discover 1.0


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
                text:"New Track"
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
