import QtQuick
import QtQuick.Controls 2.0

TreeViewDelegate
{
    id: delegate
    Rectangle {
        id: content
        color: "red"
        visible: mouseArea.drag.active
        opacity: 0.2
        width: parent.width
        height: 50
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
        //onClicked: tracksManager.setPointSelected(markerId, !markerIsSelected)
        //onDoubleClicked: mapBackend.locusPos = markerCoordinate

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
            if (mouseArea.drag.active) {
                console.log("dragStarted ind: " + row)
                if(parent.expanded)
                {
                    treeView.collapseRecursively(row)
                }

                treeView.dragMarkerId = markerId;
            }
            //content.Drag.drop();
        }
    }

    DropArea
    {
        id: dropArea
        width: parent.width
        height: parent.height

        onExited: console.log("exited " + row)
        onEntered: (drag) =>
        {
            var from = treeView.dragMarkerId
            var to = markerId //mouseArea.DelegateModel.itemsRow

           if(from !== to)
           {
               console.log("drag from " + from + " to " + to)
               treeView.model.moveItem(from,to)
           }
        }

        onDropped: (drop) =>
        {
           treeView.dragMarkerId = -1
        }

        Rectangle {
            color: "blue"
            opacity: treeView.dragMarkerId > -1 ? 0.2 : 0
            anchors.fill: parent
        }
    }

    states:
    [
        State {
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
        }
    ]

    contentItem:
//        Row {
//            leftPadding: 0
//            rightPadding: 0
//            spacing: 0
            Loader
            {
                id: shapeLoader
                source: getShape(model.column)

                function getShape(t)
                {
                    switch(t)
                    {
                    case 0:
                        return "CheckboxColumnItem.qml"
                    default:
                        return "TextColumnItem.qml"
                    }
                }
            }
//        }

    background: Rectangle {
        anchors.fill: parent
        opacity: model.markerIsSelected ? 0.5 : 0
        color: Material.accent
    }
}
