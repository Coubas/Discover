import QtQuick 2.0
import QtQuick.Controls 2.0

CheckBox
{
    checked: model.markerIsActive
    onToggled: model.markerIsActive = checked
    width: 5
}
