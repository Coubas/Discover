//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

import QtQuick.Controls 2.0
import Qt5Compat.GraphicalEffects
import QtQuick

//CheckBox
//{
//    checked: model.markerIsLoop
//    onToggled: model.markerIsLoop = checked
//}

Button
{
    onClicked: model.markerIsLoop = !model.markerIsLoop
    ToolTip.text: "If setup as a loop the path will circle to this node after passing through all of its childs."
    ToolTip.visible: hovered
    ToolTip.delay: 1000

    Image
    {
        fillMode: Image.PreserveAspectFit
        height: parent.height * 0.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        source:
        {
            if(model.markerIsLoop)
            {
                "qrc:/icons/Images/Icons/loop.png"
            }
            else
            {
                "qrc:/icons/Images/Icons/arrowRight.png"
            }
        }

        ColorOverlay
        {
            anchors.fill: parent
            source: parent
            color: Material.primary
        }
    }
}
