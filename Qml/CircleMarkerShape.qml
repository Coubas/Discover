import QtQuick 2.0
import Qt5Compat.GraphicalEffects
import QtQuick.Controls 2.0

Image
{
    width: mapMarker.shapeWidth
    height: mapMarker.shapeHeight

    property bool filled: false
    property color color: Material.accent
    property var anchorX: width * 0.5
    property var anchorY: height * 0.5
    source:
    {
        if(filled)
        {
            "qrc:/icons/Images/Icons/circle_filled.png"
        }
        else
        {
            "qrc:/icons/Images/Icons/circle.png"
        }
    }

    ColorOverlay
    {
        anchors.fill: parent
        source: parent
        color: parent.color
    }
}

