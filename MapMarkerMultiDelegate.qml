import QtQuick 2.0

import QtPositioning 5.6
import QtLocation 5.6
import Qt.labs.qmlmodels

DelegateChooser
{
    id: mapMarkerDelegateChooser
    role: "markerType"

    DelegateChoice
    {
        id: cursorDelegate
        roleValue: "cursor"
        MapQuickItem
        {
            id: cursor
            anchorPoint.x: rectShape.width / 2
            anchorPoint.y:  rectShape.height / 2
            coordinate: markerCoordinate

            sourceItem:
                Rectangle
                {
                    id: rectShape
                    width: 25
                    height: 25
                    color: "blue"

                    MapMarkerBase
                    {
                        visualComponentId: rectShape
                    }
                }
        }
    }

    DelegateChoice
    {
        id: circleDelegate
        roleValue: "circle"
        MapCircle
        {
            id: circleShape
            center: markerCoordinate
            radius: 500.0
            color: "blue"
            border.width: 3

            MapMarkerBase
            {
                visualComponentId: circleShape
            }
        }
    }
}
