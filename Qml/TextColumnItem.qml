import QtQuick 2.0

Text
{
    anchors.verticalCenter: isTreeNode ? parent.verticalCenter : 0
    text: model.display
}
