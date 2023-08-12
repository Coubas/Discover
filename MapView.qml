import QtQuick

import QtLocation
import QtPositioning
import MapHelper 1.0
import MapBackend 1.0

Item
{
    MapBackend
    {
        id: mapData
        zoomLevel: map.zoomLevel
        locusPos: QtPositioning.coordinate(43.778958, 3.812109) // Le Pic Saint-Loup
    }

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
        anchors.fill: parent
        plugin: mapPlugin
        center: mapData.locusPos
        zoomLevel: 10
        //activeMapType: MapType.StreetMap
        activeMapType: supportedMapTypes[supportedMapTypes.length - 1]

        WheelHandler
        {
            id: wheel
            // workaround for QTBUG-87646 / QTBUG-112394 / QTBUG-112432:
            // Magic Mouse pretends to be a trackpad but doesn't work with PinchHandler
            // and we don't yet distinguish mice and trackpads on Wayland either
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                             ? PointerDevice.Mouse | PointerDevice.TouchPad
                             : PointerDevice.Mouse
            rotationScale: 1/120
            property: "zoomLevel"
            onWheel: (event) => {
                         //console.log("pos", event.x, event.y, "angleDelta", event.angleDelta.y, "zoom", map.zoomLevel);
                         var coord = map.toCoordinate(Qt.point(event.x, event.y));
                         var center = map.center;
                         //console.log("center: ", center,"mouse: ",coord);
                         mapData.onMapZoom(center, coord, event.angleDelta.y);
                     }
        }

        DragHandler
        {
            id: drag
            target: null
            onTranslationChanged: (delta) =>
                                  {
                                      map.pan(-delta.x, -delta.y)
                                      mapData.onMapDrag(map.center)
                                  }
        }

        MouseArea
        {
            id: mouseArea
            objectName: "mouseArea"
            anchors.fill: parent
            property geoCoordinate coord: map.toCoordinate(Qt.point(mouseX, mouseY));
            signal displayCurrentPos(geoCoordinate _coord);
            onClicked:
            {
                geoModel.query = coord;
                geoModel.update();

                displayCurrentPos(coord);
            }
        }
    }

    GeocodeModel
    {
        id: geoModel
        objectName: "geoModel"
        plugin: mapPlugin
        signal displayAdress(geoLocation _location);
        onLocationsChanged:
        {
            if(error)
            {
                console.log("Erreur GeocodeModel : " + error + " - " + errorString)
            }

            if (count>=1)
            {
                //console.log("Adresse : " + get(0).address.text + "\n" + get(0).coordinate)
                displayAdress(get(0).location)
            }
        }
    }
}
