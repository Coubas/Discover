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
