//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

import QtQuick
import QtQuick.Controls 2.0

TreeViewDelegate
{
    id: delegate
    contentItem:
            Loader
            {
                id: shapeLoader
                z:10
                source: getColumnType(model.column, hasChildren)

                // See in MapMarkerTreeItem.cpp -> ms_columns
                function getColumnType(col, children)
                {
                    switch(col)
                    {
                    case 0:
                        return "MarkerIsActiveColumnItem.qml"
                    case 3:
                        return children ? "MarkerIsLoopColumnItem.qml" : ""
                    default:
                        return "TextColumnItem.qml"
                    }
                }
            }

    background: Rectangle {
        id: rowBackground
        //anchors.fill: parent
        visible: isTreeNode
        width: delegate.parent.width
        height: delegate.height
        x: leftMargin * 0.5
        opacity: model.markerIsSelected ? 0.5 : 0
        color: Material.accent
    }

    Rectangle {
        id: content
        visible: mouseArea.drag.active
        color: "transparent"
        width: delegate.parent.width
        height: delegate.height
        border.color: Material.accent
        border.width: 2
        opacity: 0.2
        Drag.active: visible
        Drag.source: mouseArea
        Drag.hotSpot.x: width * 0.5
        Drag.hotSpot.y: height * 0.5
    }

    MouseArea
    {
        id: mouseArea
        width: parent.width
        height: parent.height

        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: (mouse) =>
        {
            if (mouse.button === Qt.LeftButton)
            {
                tracksManager.setPointSelected(markerId, !markerIsSelected)
                //doucleClickThreshold()
            }
            else if (mouse.button === Qt.RightButton)
            {
                contextMenu.popup()
            }
        }

        Timer{
            id:timer
            interval: 200
            onTriggered: tracksManager.setPointSelected(markerId, !markerIsSelected) // Single Click
        }

        function doucleClickThreshold() {
            if(timer.running)
            {
                mapBackend.locusPos = markerCoordinate // Double click
                timer.stop()
            }
            else
                timer.restart()
        }

        // Drag handling
        drag.target: content
        drag.axis: Drag.YAxis
        drag.onActiveChanged:
        {
            if (mouseArea.drag.active)
            {
                if(parent.expanded)
                {
                    treeView.collapseRecursively(row)
                }

                treeView.dragMarkerId = markerId;
            }
            else
            {
                content.Drag.drop();
                treeView.dragMarkerId = -1
            }
        }
    }

    DropArea
    {
        id: dropAreaTop
        width: parent.width
        height: parent.height * 0.25
        y: 0

        onExited: () =>
        {
            treeView.resetDragInfo()
        }
        onEntered: (drag) =>
        {
            var from = treeView.dragMarkerId
            var to = markerId

            if(treeView.model.isValidMove(from,to, false))
            {
                treeView.dragOveredRow = row
                treeView.dragOveredRowPart = "top"
            }
        }

        onDropped: (drop) =>
        {
            var from = treeView.dragMarkerId
            var to = markerId

            if(treeView.model.isValidMove(from,to, false))
            {
                treeView.model.moveItem(from, to, false)
            }

            treeView.resetDragInfo()
        }
    }

    DropArea
    {
        id: dropAreaMid
        width: parent.width
        height: parent.height * 0.5
        y: parent.height * 0.25

        onExited: () =>
        {
            expendTimer.stop()
            treeView.resetDragInfo()
        }
        onEntered: (drag) =>
        {
            var from = treeView.dragMarkerId
            var to = markerId

            if(treeView.model.isValidNewChild(from,to))
            {
                treeView.dragOveredRow = row
                treeView.dragOveredRowPart = "middle"
                expendTimer.restart()
            }
        }

        onDropped: (drop) =>
        {
            expendTimer.stop()

            var from = treeView.dragMarkerId
            var to = markerId

            if(treeView.model.isValidNewChild(from,to))
            {
                treeView.model.addItemAsChild(from,to)
            }

            treeView.resetDragInfo()
        }

        Timer{
            id: expendTimer
            interval: 500
            onTriggered: treeView.expand(row)
        }
    }

    DropArea
    {
        id: dropAreaBot
        width: parent.width
        height: parent.height * 0.25
        y: parent.height * 0.75

        onExited: () =>
        {
            treeView.resetDragInfo()
        }
        onEntered: (drag) =>
        {
            var from = treeView.dragMarkerId
            var to = markerId

            if(treeView.model.isValidMove(from,to, true))
            {
                treeView.dragOveredRow = row
                treeView.dragOveredRowPart = "bottom"
            }
        }

        onDropped: (drop) =>
        {
            var from = treeView.dragMarkerId
            var to = markerId

            if(treeView.model.isValidMove(from,to, true))
            {
                treeView.model.moveItem(from, to, true)
            }

            treeView.resetDragInfo()
        }
    }

    Rectangle {
        id: moveToptFeedback
        visible: isTreeNode
        color: Material.primary
        width: delegate.parent.width
        height: 2
        x: leftMargin * 0.5
        opacity: treeView.dragOveredRow === row && treeView.dragOveredRowPart === "top" ? 1 : 0
    }

    Rectangle {
        id: moveBotFeedback
        visible: isTreeNode
        color: Material.primary
        width: delegate.parent.width
        height: 2
        x: leftMargin * 0.5
        y: parent.height - height
        opacity: treeView.dragOveredRow === row && treeView.dragOveredRowPart === "bottom" ? 1 : 0
    }

    Rectangle {
        id: moveIntoFeedback
        visible: isTreeNode && treeView.dragOveredRow === row && treeView.dragOveredRowPart === "middle"
        width: delegate.parent.width
        height: delegate.height
        x: leftMargin * 0.5
        border.color: Material.primary
        border.width: 2
        color: "transparent"
        //color: Material.primary
        //opacity: treeView.dragOveredRow === row && treeView.dragOveredRowPart === "middle" ? 0.5 : 0
    }

    states:
    [
        State {
            name: "dragFeedback"
            when: mouseArea.drag.target.Drag.active
            ParentChange {
                target: mouseArea.drag.target
                parent: treeViewRoot
            }

            AnchorChanges {
                target: mouseArea.drag.target
                anchors.horizontalCenter: treeViewRoot.horizontalCenter
                anchors.verticalCenter: undefined
            }
        },

        State {
            name: "InActiveHierarchy"
            when: markerLinearIndexInActiveHierarchy === -1
            PropertyChanges {
                target: rowBackground
                opacity: model.markerIsSelected ? 0.5 : 0.2
                color: model.markerIsSelected ? Material.accent : "grey"
            }
        }
    ]

    Menu
    {
        id: contextMenu
        closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape
        MenuItem
        {
            text: "Center map"
            onTriggered: mapBackend.locusPos = markerCoordinate
        }
        MenuItem
        {
            text: "Rename"
            onTriggered: renamePopup.open()
        }
//        MenuItem
//        {
//            text: "Log Info"
//            onTriggered: console.log("Marker id: " + markerId + ", selected: " + markerIsSelected +
//                                     "\nType: " + markerType + ", Pos: " + markerCoordinate)
//        }
    }

    Popup {
        id: renamePopup
        modal: true
        focus: true
        onOpened: markerRenameInput.selectAll()
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        TextInput
        {
            id: markerRenameInput
            anchors.fill: parent
            text: markerName
            focus: true
            horizontalAlignment: Text.AlignHCenter
            selectionColor: Material.accent
            onAccepted:
            {
                markerName = text
                renamePopup.close()
            }
        }
    }
}
