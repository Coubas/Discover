//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

import QtQuick 2.0
import Qt5Compat.GraphicalEffects
import QtQuick.Controls 2.0

Image
{
    width: 40
    height: 40

    property bool filled: false
    property color color: "black"
    property var anchorX: width * 0.5
    property var anchorY: height * 0.5
    source:
    {
//        if(filled)
//        {
//            "qrc:/icons/Images/Icons/my_location_filled.svg"
//        }
//        else
        {
            "qrc:/icons/Images/Icons/cursor.png"
        }
    }

    ColorOverlay
    {
        anchors.fill: parent
        source: parent
        color: parent.color
    }
}
