import QtQuick 2.0
import Qt5Compat.GraphicalEffects
import QtQuick.Controls 2.0

Image
{
    width: mapMarker.shapeWidth
    height: mapMarker.shapeHeight

    property bool filled: false
    property color color: Material.accent
    property double anchorX: width * 0.5
    property double anchorY: height
    source:
    {
        if(filled)
        {
            "qrc:/icons/Images/Icons/location_on_filled.svg"
        }
        else
        {
            "qrc:/icons/Images/Icons/location_on.svg"
        }
    }

    ColorOverlay
    {
        anchors.fill: parent
        source: parent
        color: parent.color
    }
}
