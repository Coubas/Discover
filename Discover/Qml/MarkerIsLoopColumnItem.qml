import QtQuick.Controls 2.0

CheckBox
{
    checked: model.markerIsLoop
    onToggled: model.markerIsLoop = checked
}
