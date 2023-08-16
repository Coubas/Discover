import QtQuick
import QtQuick 2.0

import Qt.labs.qmlmodels
import QtLocation
import QtPositioning
import MapHelper 1.0
import MapBackend 1.0
import MapMarker 1.0
import Inputs 1.0
import Tracks 1.0

Item
{
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
            signal mapZoomed(geoCoordinate _centerCoord, geoCoordinate _mouseCoord, int _zoomFactor)
            onWheel: (event) => {
                         //console.log("pos", event.x, event.y, "angleDelta", event.angleDelta.y, "zoom", map.zoomLevel);
                         var coord = map.toCoordinate(Qt.point(event.x, event.y));
                         var center = map.center;
                         mapZoomed(center, coord, event.angleDelta.y);
                     }
        }

        DragHandler
        {
            id: dragHandler
            objectName: "dragHandler"
            target: null
            signal mapDraged(geoCoordinate _coord)
            onTranslationChanged: (delta) =>
                                  {
                                      map.pan(-delta.x, -delta.y)
                                      mapDraged(map.center)
                                  }
        }

        MouseArea
        {
            id: mapMouseArea
            objectName: "mouseArea"
            anchors.fill: parent
            property geoCoordinate coord: map.toCoordinate(Qt.point(mouseX, mouseY));
            signal mapClicked(geoCoordinate _coord);
            onClicked:
            {
                geoModel.query = coord;
                geoModel.update();

                mapClicked(coord);
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
            delegate: MapMarkerMultiDelegate{}
        }
    }

    GeocodeModel
    {
        id: geoModel
        objectName: "geoModel"
        plugin: mapPlugin
        signal cursorGeolocComputed(geoLocation _location);
        onLocationsChanged:
        {
            if(error)
            {
                console.log("Erreur GeocodeModel : " + error + " - " + errorString)
            }

            if (count>=1)
            {
                //console.log("Adresse : " + get(0).address.text + "\n" + get(0).coordinate)
                cursorGeolocComputed(get(0).location)
            }
        }
    }
}
