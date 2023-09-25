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
        if(markerIsLoop)
        {
            if(filled)
            {
                "qrc:/icons/Images/Icons/loopPin_filled.png"
            }
            else
            {
                "qrc:/icons/Images/Icons/loopPin.png"
            }
        }
        else if(filled)
        {
            "qrc:/icons/Images/Icons/pin_filled.png"
        }
        else
        {
            "qrc:/icons/Images/Icons/pin.png"
        }
    }

    ColorOverlay
    {
        anchors.fill: parent
        source: parent
        color: parent.color
    }
}
