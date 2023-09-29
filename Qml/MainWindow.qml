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


ApplicationWindow
{
    id: mainWindow
    visible: true
    width: 1920
    height: 1080

    menuBar: MainMenuBar {}

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
