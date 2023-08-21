cmake_minimum_required(VERSION 3.16)

project(Discover VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core QuickWidgets Positioning)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appDiscover
    main.cpp
)

include_directories(Map)
include_directories(Map/MapMarkers)
include_directories(Tracks)
include_directories(Qml)

qt_add_qml_module(appDiscover
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
        Qml/MapView.qml
        Qml/MapMarkerBase.qml
        Qml/MapMarkerCursor.qml
        Qml/MapMarkerListViewItem.qml
        Qml/CursorMarkerShape.qml
        Qml/PinMarkerShape.qml
        Qml/CircleMarkerShape.qml
    RESOURCES
        qtquickcontrols2.conf
        qml.qrc
        settings.qrc
)

qt_add_resources(appDiscover "qml"
    PREFIX "/qml"
    FILES
        Qml/MainWindow.qml
        Qml/MainWindowContent.qml
        Qml/MapView.qml
        Qml/MapMarkerBase.qml
        Qml/MapMarkerCursor.qml
        Qml/MapMarkerListViewItem.qml
        Qml/CursorMarkerShape.qml
        Qml/PinMarkerShape.qml
        Qml/CircleMarkerShape.qml
)

qt_add_resources(appDiscover "settings"
    PREFIX "/"
    FILES qtquickcontrols2.conf
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appDiscover PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appDiscover
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appDiscover
    PRIVATE Qt6::Core
    PRIVATE Qt6::QuickWidgets
    PRIVATE Qt6::Positioning
    PRIVATE Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appDiscover
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
