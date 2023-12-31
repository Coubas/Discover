cmake_minimum_required(VERSION 3.16)

## To deploy
## in QT commandline window, cd to the exe directory then
## windeployqt Discover.exe

project(Discover VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core QuickWidgets Positioning Location QuickControls2)
#find_package(Qt6 REQUIRED COMPONENTS Test)

qt_standard_project_setup(REQUIRES 6.5)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    enable_language("RC")
    set(app_icon_resource_windows ${CMAKE_CURRENT_SOURCE_DIR}/Discover.rc)
endif()
#set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/Discover.rc")

qt_add_executable(Discover main.cpp ${app_icon_resource_windows})

include_directories(Map)
#Copyright 2023 Lauryl Escoubas
#
#This file is part of Discover.
#
#Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

include_directories(Map/MapMarkers)
include_directories(Tracks)
include_directories(Qml)
include_directories(Image)
include_directories(Image/Icons)

qt_add_qml_module(Discover
    URI Discover
    VERSION 1.0
    SOURCES
        DiscoverMainWindow.h DiscoverMainWindow.cpp
        GPXExporter.h GPXExporter.cpp
        InputHandler.h InputHandler.cpp
        Map/MapBackend.h Map/MapBackend.cpp
        Map/MapHelper.h Map/MapHelper.cpp
        Map/MapMarkers/MapMarkerTreeItem.h Map/MapMarkers/MapMarkerTreeItem.cpp
        Map/MapMarkers/MapMarkerTreeListModel.h Map/MapMarkers/MapMarkerTreeListModel.cpp
        Map/MapMarkers/MapMarkerTreeModel.h Map/MapMarkers/MapMarkerTreeModel.cpp
        Map/MapMarkers/VisitorReturnEnum.h
        Map/VecGeoCoord2D.h Map/VecGeoCoord2D.cpp
        Tracks/TracksManager.h Tracks/TracksManager.cpp
        Tracks/TreeTrack.h Tracks/TreeTrack.cpp
    RESOURCES
        images.qrc
        qml.qrc
        qtquickcontrols2.conf
        settings.qrc
)

qt_add_resources(Discover "qml"
    PREFIX "/qml"
    FILES
        Qml/CircleMarkerShape.qml
        Qml/CursorMarkerShape.qml
        Qml/DiscoverMapView.qml
        Qml/HelpWindow.qml
        Qml/MainMenuBar.qml
        Qml/MainWindow.qml
        Qml/MainWindowContent.qml
        Qml/MapMarkerBase.qml
        Qml/MapMarkerCursor.qml
        Qml/MapMarkerTreeViewDelegate.qml
        Qml/MapRouteBase.qml
        Qml/MarkerIsActiveColumnItem.qml
        Qml/MarkerIsLoopColumnItem.qml
        Qml/PinMarkerShape.qml
        Qml/TextColumnItem.qml
)

qt_add_resources(Discover "settings"
    PREFIX "/"
    FILES qtquickcontrols2.conf
)

qt_add_resources(Discover "images"
    PREFIX "/icons"
    FILES
        Images/Icons/addPin.png
        Images/Icons/arrowRight.png
        Images/Icons/circle.png
        Images/Icons/circle_filled.png
        Images/Icons/cursor.png
        Images/Icons/loop.png
        Images/Icons/loopPin.png
        Images/Icons/loopPin_filled.png
        Images/Icons/pin.png
        Images/Icons/pin_filled.png
        moto.ico
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
#    PRIVATE Qt6::Test
)

include(GNUInstallDirs)
install(TARGETS Discover
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
