import QtQuick.Controls 2.0

CheckBox
{
    checked: model.markerIsActive
    onToggled: model.markerIsActive = checked
}
