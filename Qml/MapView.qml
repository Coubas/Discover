import QtQuick
import QtQuick 2.0

import Qt.labs.qmlmodels
import QtQuick.Controls
import QtLocation
import QtPositioning

import MapHelper 1.0
import MapBackend 1.0
import MapMarker 1.0
import Inputs 1.0
import Tracks 1.0

Item
{
//    ComboBox
//    {
//        z:100
//        width: 200
//        anchors.right: parent.right
//        anchors.rightMargin: 5
//        model: map.supportedMapTypes
//        textRole:"name"
//        currentIndex: map.supportedMapTypes.length - 1
//        onCurrentIndexChanged: map.activeMapType = map.supportedMapTypes[currentIndex]
//        delegate: ItemDelegate
//        {
//            text: map.supportedMapTypes[index].name
//        }
//    }

    Plugin {
        id: mapPlugin
        name: "osm"
        locales: "fr_FR"
        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "http://a.tile.openstreetmap.fr/osmfr/"
        }
    }

    Map
    {
        id: map
        objectName: "map"
        anchors.fill: parent
        plugin: mapPlugin
        center: mapBackend.locusPos
        zoomLevel: 10
        //activeMapType: MapType.StreetMap
        activeMapType: supportedMapTypes[supportedMapTypes.length - 1]
        Component.onCompleted: addMapItem(cursor)

        WheelHandler
        {
            id: wheelHandler
            objectName: "wheelHandler"
            // workaround for QTBUG-87646 / QTBUG-112394 / QTBUG-112432:
            // Magic Mouse pretends to be a trackpad but doesn't work with PinchHandler
            // and we don't yet distinguish mice and trackpads on Wayland either
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                             ? PointerDevice.Mouse | PointerDevice.TouchPad
                             : PointerDevice.Mouse
            rotationScale: 1/120
            property: "zoomLevel"
            onWheel: (event) => {
                        //console.log("pos", event.x, event.y, "angleDelta", event.angleDelta.y, "zoom", map.zoomLevel)
                        var coord = map.toCoordinate(Qt.point(event.x, event.y))
                        var center = map.center
                        inputHandler.onMapZoomed(center, coord, event.angleDelta.y)
                     }
        }

        DragHandler
        {
            id: dragHandler
            objectName: "dragHandler"
            target: null
            onTranslationChanged: (delta) =>
                                  {
                                      map.pan(-delta.x, -delta.y)
                                      inputHandler.onMapDraged(map.center)
                                  }
        }

        MouseArea
        {
            id: mapMouseArea
            objectName: "mouseArea"
            anchors.fill: parent
            property geoCoordinate coord: map.toCoordinate(Qt.point(mouseX, mouseY));
            onClicked:
            {
                geoModel.updateQuery(coord)

                inputHandler.onMapClicked(coord)
            }
        }

        Shortcut
        {
            sequence: StandardKey.Delete
            onActivated:
            {
                console.log("DeletePressed")
                tracksManager.removeSelectedPointsFromActiveTrack()
            }
        }

        MapItemView
        {
            id: mapMarkers
            model: MapMarkerModel
            {
                list: tracksManager.activeTrack.points
            }
            delegate: MapMarkerBase{}
        }
    }

    GeocodeModel
    {
        id: geoModel
        objectName: "geoModel"
        plugin: mapPlugin
        onLocationsChanged:
        {
            if(error)
            {
                console.log("Erreur GeocodeModel : " + error + " - " + errorString)
            }

            if (count>=1)
            {
                //console.log("Adresse : " + get(0).address.text + "\n" + get(0).coordinate)
                inputHandler.onCursorGeolocComputed(get(0).location)
            }
        }

        function updateQuery(coord)
        {
            query = coord
            update()
        }
    }

    MapMarkerCursor
    {
        id: cursor
    }
}
