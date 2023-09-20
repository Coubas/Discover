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
            else
            {
                console.log("dragStopped ind: " + row)
                content.Drag.drop();
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
        }
        onEntered: (drag) =>
        {
           var from = treeView.dragMarkerId
           var to = markerId

           if(from !== to)
           {
               console.log("Entered " + to + " top")
           }
        }

        onDropped: (drop) =>
        {
                       console.log("Dropped " + markerId + " top")
           var from = treeView.dragMarkerId
           var to = markerId

           if(from !== to)
           {
                treeView.model.moveItem(from, to, false)
           }
           treeView.dragMarkerId = -1
        }

        Rectangle {
            color: "green"
            //opacity: treeView.dragMarkerId > -1 ? 0.2 : 0
            opacity: parent.containsDrag ? 1 : 0.2
            anchors.fill: parent
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
            //console.log("exited " + row)
        }
        onEntered: (drag) =>
        {
            var from = treeView.dragMarkerId
            var to = markerId

           if(from !== to)
           {
                console.log("Entered " + to + " middle")
                expendTimer.restart()
                //treeView.model.moveItem(from,to)
           }
        }

        onDropped: (drop) =>
        {
                       console.log("Dropped " + markerId + " middle")

            expendTimer.stop()

            var from = treeView.dragMarkerId
            var to = markerId

            if(from !== to)
            {
                treeView.model.addItemAsChild(from,to)
            }
            treeView.dragMarkerId = -1
        }

        Rectangle {
            color: "blue"
            //opacity: treeView.dragMarkerId > -1 ? 0.2 : 0
            opacity: parent.containsDrag ? 1 : 0.2
            anchors.fill: parent
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
        }
        onEntered: (drag) =>
        {
            var from = treeView.dragMarkerId
            var to = markerId

            if(from !== to)
            {
                console.log("Entered " + to + " bottom")
            }
        }

        onDropped: (drop) =>
        {
                       console.log("Dropped " + markerId + " bottom")
           var from = treeView.dragMarkerId
           var to = markerId

           if(from !== to)
           {
                treeView.model.moveItem(from, to, true)
           }
           treeView.dragMarkerId = -1
        }

        Rectangle {
            color: "yellow"
            //opacity: treeView.dragMarkerId > -1 ? 0.2 : 0
            opacity: parent.containsDrag ? 1 : 0.2
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
