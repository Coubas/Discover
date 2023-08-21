import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.0

import Discover 1.0
import MapMarker 1.0

Item
{
    id: row
    x: 5
    height: 40
    width: parent?.width

    Text
    {
        id: text
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent?.left
        text: markerId + ": " + markerCoordinate + "\n type: " + markerType + " selected: " + markerIsSelected
    }

    Button
    {
        z: mouseArea.z + 1
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent?.right
        text: "X"
        onClicked: tracksManager.removePointFromActiveTrack(markerId)
    }

    Rectangle
    {
        id: hilight
        z: text.z - 1
        anchors.fill: parent
        color: markerIsSelected ? Material.accentColor : "transparent"
        border.color: Material.accentColor
        border.width: listView.dragItemIndex === index ? 1 : 0
    }

    Rectangle {
        id: content
        Drag.active: mouseArea.drag.active
        Drag.source: mouseArea
        Drag.hotSpot.x: row.width * 0.5
        Drag.hotSpot.y: row.height * 0.5
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        //onClicked: tracksManager.setPointSelected(markerId, !markerIsSelected)
        //onDoubleClicked: mapBackend.locusPos = markerCoordinate
        Timer{
            id:timer
            interval: 200
            onTriggered: tracksManager.setPointSelected(markerId, !markerIsSelected) // Single Click
        }
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: (mouse) =>
        {
            if (mouse.button === Qt.LeftButton)
            {
                doucleClickThreshold()
            }
            else if (mouse.button === Qt.RightButton)
            {
                contextMenu.popup()
            }
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
            if (mouseArea.drag.active) {
                listView.dragItemIndex = index;
            }
            content.Drag.drop();
        }
    }

    DropArea {
        id: dropArea
        anchors.fill: parent

        onEntered: (drag) =>
        {
            var from = listView.dragItemIndex
            var to = mouseArea.DelegateModel.itemsIndex

            listView.model.list.moveItem(
                    listView.dragItemIndex,
                    mouseArea.DelegateModel.itemsIndex)
            listView.dragItemIndex = to
        }

        onDropped: listView.dragItemIndex = -1
    }

    states:
    [
        State {
            when: mouseArea.drag.target.Drag.active
            ParentChange {
                target: mouseArea.drag.target
                parent: listViewRoot
            }

            AnchorChanges {
                target: mouseArea.drag.target
                anchors.horizontalCenter: undefined
                anchors.verticalCenter: undefined
            }
        }
    ]

    Menu
    {
        id: contextMenu
        closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape
        MenuItem
        {
            text: "Center map on " + markerId
            onTriggered: mapBackend.locusPos = markerCoordinate
        }
        MenuItem
        {
            text: "Log Info"
            onTriggered: console.log("Marker id: " + markerId + ", selected: " + markerIsSelected +
                                     "\nType: " + markerType + ", Pos: " + markerCoordinate)
        }
    }
}
