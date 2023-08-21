import QtQuick 2.0
import Qt5Compat.GraphicalEffects
import QtQuick.Controls 2.0

Image
{
    property bool filled: false
    property color color: Material.accent
    property var anchorX: width * 0.5
    property var anchorY: height * 0.5
    source:
    {
        if(filled)
        {
            "qrc:/icons/Images/Icons/location_searching_filled.svg"
        }
        else
        {
            "qrc:/icons/Images/Icons/location_searching.svg"
        }
    }

    ColorOverlay
    {
        anchors.fill: parent
        source: parent
        color: parent.color
    }
}

