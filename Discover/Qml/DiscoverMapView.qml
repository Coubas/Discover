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
//    Button
//    {
//        text: "Test Button"
//        z:100
//        width: 200
//        anchors.right: parent.right
//        anchors.rightMargin: 5
//        onClicked: (mouse) =>
//                   {
//                   }
//    }

    function updateRouteQuery(/*travelMode, pathMode*/)
    {
        routeQuery.clearWaypoints();
//        for (var i = 0; i < tracksManager.activeTrackWaypoints.length; i++)
//        {
//           var coord = tracksManager.activeTrackWaypoints[i]
//           routeQuery.addWaypoint(coord)
//        }
        var waypoints = tracksManager.treeTrackWaypoints
        for (var i = 0; i < waypoints.length; i++)
        {
           var coord = waypoints[i]
           routeQuery.addWaypoint(coord)
        }
//        routeQuery.travelModes = travelMode
//        routeQuery.routeOptimizations = pathMode
//        routeQuery.setFeatureWeight(RouteQuery.HighwayFeature, RouteQuery.DisallowFeatureWeight)
//        routeQuery.numberAlternativeRoutes = 3
        routeModel.update()
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
                tracksManager.removeSelectedPointsFromActiveTrack()
            }
        }

        Shortcut
        {
            sequence: StandardKey.Cancel
            onActivated:
            {
                mapBackend.cursorVisible = false
            }
        }

        MapItemView
        {
            id: mapRoutes
            model: routeModel
            delegate: MapRouteBase {}
        }

        MapItemView
        {
            id: mapMarkers
            model: tracksManager.treeTrack.treeModel.listModel
            delegate: MapMarkerBase{}
        }
    }

    MapMarkerCursor
    {
        id: cursor
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

    RouteModel
    {
        id: routeModel
        plugin: mapPlugin
        autoUpdate: false
        query: routeQuery

        onQueryChanged: console.log("New Query...")
        onRoutesChanged:
        {
            console.log("Number of route computed: " + count)
            var r = get(0)
            console.log("Routes CHanged..." +  "Dist :" + r.distance + " travel time: " + r.travelTime)
        }

        onStatusChanged:
        {
            if (status == RouteModel.Ready)
            {
                switch (count) {
                case 0:
                    // technically not an error
                    console.log("Route conputed with no points, something might be wrong :/")
                    break
                case 1:
                    console.log("Route computed !")
                    break
                }
            }
            else if (status == RouteModel.Error)
            {
                console.log("Error during route computation : " + errorString)
            }
            else if (status == routeModel.Loading)
            {
                console.log("Computing route...")
            }
        }
    }

    RouteQuery
    {
        id: routeQuery
    }
}