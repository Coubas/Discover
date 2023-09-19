import QtQuick 2.0
import QtQuick.Controls 2.0

CheckBox
{
    anchors.verticalCenter: parent.verticalCenter
    checked: model.markerIsActive
    onToggled: model.markerIsActive = checked
}
