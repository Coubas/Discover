import QtQuick 2.0
import QtQuick.Controls 2.0

CheckBox
{
    checked: getValue(parent.toCheck)
    onToggled: setValue(parent.toCheck)
    width: 5

    function getValue(t)
    {
        switch(t)
        {
        case "active":
            return model.markerIsActive
        case "loop":
            return model.markerIsLoop
        }
    }

    function setValue(t)
    {
        switch(t)
        {
        case "active":
            model.markerIsActive = checked
            break
        case "loop":
            model.markerIsLoop = checked
            break
        }
    }
}
