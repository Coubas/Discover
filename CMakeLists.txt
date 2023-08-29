cmake_minimum_required(VERSION 3.16)

project(Discover VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core QuickWidgets Positioning Location)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    enable_language("RC")
    set(app_icon_resource_windows ${CMAKE_CURRENT_SOURCE_DIR}/Discover.rc)
endif()
#set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/Discover.rc")

qt_add_executable(Discover main.cpp ${app_icon_resource_windows})

include_directories(Map)
include_directories(Map/MapMarkers)
include_directories(Tracks)
include_directories(Qml)
include_directories(Image)
include_directories(Image/Icons)

qt_add_qml_module(Discover
    URI Discover
    VERSION 1.0
    SOURCES
        Map/MapHelper.h Map/MapHelper.cpp
        Map/MapBackend.h Map/MapBackend.cpp
        Map/VecGeoCoord2D.h Map/VecGeoCoord2D.cpp
        InputHandler.h InputHandler.cpp
        Map/MapMarkers/MapMarkerModel.h Map/MapMarkers/MapMarkerModel.cpp
        Map/MapMarkers/MapMarkerList.h Map/MapMarkers/MapMarkerList.cpp
        Map/MapMarkers/MapMarkerItem.h Map/MapMarkers/MapMarkerItem.cpp
        Tracks/TracksManager.h Tracks/TracksManager.cpp
        Tracks/Track.h Tracks/Track.cpp
        DiscoverMainWindow.h DiscoverMainWindow.cpp
    QML_FILES
        Qml/MainWindow.qml
        Qml/MainWindowContent.qml
        Qml/DiscoverMapView.qml
        Qml/MapMarkerBase.qml
        Qml/MapMarkerCursor.qml
        Qml/MapMarkerListViewItem.qml
        Qml/MapRouteBase.qml
        Qml/CursorMarkerShape.qml
        Qml/PinMarkerShape.qml
        Qml/CircleMarkerShape.qml
    RESOURCES
        qtquickcontrols2.conf
        qml.qrc
        settings.qrc
        images.qrc
        moto.ico
        Images/icons/arrival_flag.svg
        Images/Icons/arrival_flag_filled.svg
        Images/Icons/distance.svg
        Images/Icons/distance_filled.svg
        Images/Icons/explore.svg
        Images/Icons/explore_filled.svg
        Images/Icons/flag_circle.svg
        Images/Icons/flag_circle_filled.svg
        Images/Icons/flags.svg
        Images/Icons/flags_filled.svg
        Images/Icons/home_pin.svg
        Images/Icons/home_pin_filled.svg
        Images/Icons/location_home.svg
        Images/Icons/location_home_filled.svg
        Images/Icons/location_on.svg
        Images/Icons/location_on_filled.svg
        Images/Icons/location_searching.svg
        Images/Icons/location_searching_filled.svg
        Images/Icons/my_location.svg
        Images/Icons/my_location_filled.svg
        Images/Icons/person_pin.svg
        Images/Icons/person_pin_filled.svg
        Images/Icons/person_pin_circle.svg
        Images/Icons/person_pin_circle_filled.svg
        Images/Icons/push_pin.svg
        Images/Icons/push_pin_filled.svg
        SOURCES GPXExporter.h GPXExporter.cpp
)

qt_add_resources(Discover "qml"
    PREFIX "/qml"
    FILES
        Qml/MainWindow.qml
        Qml/MainWindowContent.qml
        Qml/DiscoverMapView.qml
        Qml/MapMarkerBase.qml
        Qml/MapMarkerCursor.qml
        Qml/MapMarkerListViewItem.qml
        Qml/MapRouteBase.qml
        Qml/CursorMarkerShape.qml
        Qml/PinMarkerShape.qml
        Qml/CircleMarkerShape.qml
)

qt_add_resources(Discover "settings"
    PREFIX "/"
    FILES qtquickcontrols2.conf
)

qt_add_resources(Discover "images"
    PREFIX "/icons"
    FILES
        moto.ico
        Images/icons/arrival_flag.svg
        Images/Icons/arrival_flag_filled.svg
        Images/Icons/distance.svg
        Images/Icons/distance_filled.svg
        Images/Icons/explore.svg
        Images/Icons/explore_filled.svg
        Images/Icons/flag_circle.svg
        Images/Icons/flag_circle_filled.svg
        Images/Icons/flags.svg
        Images/Icons/flags_filled.svg
        Images/Icons/home_pin.svg
        Images/Icons/home_pin_filled.svg
        Images/Icons/location_home.svg
        Images/Icons/location_home_filled.svg
        Images/Icons/location_on.svg
        Images/Icons/location_on_filled.svg
        Images/Icons/location_searching.svg
        Images/Icons/location_searching_filled.svg
        Images/Icons/my_location.svg
        Images/Icons/my_location_filled.svg
        Images/Icons/person_pin.svg
        Images/Icons/person_pin_filled.svg
        Images/Icons/person_pin_circle.svg
        Images/Icons/person_pin_circle_filled.svg
        Images/Icons/push_pin.svg
        Images/Icons/push_pin_filled.svg
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(Discover PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Discover
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(Discover
    PRIVATE Qt6::Core
    PRIVATE Qt6::QuickWidgets
    PRIVATE Qt6::Positioning
    PRIVATE Qt6::Location
    PRIVATE Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS Discover
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
