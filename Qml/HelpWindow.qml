//Copyright 2023 Lauryl Escoubas
//
//This file is part of Discover.
//
//Discover is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//Discover is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Discover 1.0

import MapMarker 1.0


Window
{
    width: 1280
    height: 720
    visible: true
    onClosing: helpWindowLoader.active = false

    TabBar {
        id: subjects
        width: 300
        height: parent.height

        contentItem: ListView {
            width: parent.width
            model: subjects.contentModel
            currentIndex: subjects.currentIndex

            spacing: subjects.spacing
            orientation: ListView.Vertical   // <<-- VERTICAL
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.AutoFlickIfNeeded
            snapMode: ListView.SnapToItem

            highlightMoveDuration: 0
            highlightRangeMode: ListView.ApplyRange
            preferredHighlightBegin: 40
            preferredHighlightEnd: height - 40
        }

        TabButton {
            width: parent.width
            text: qsTr("How to create new point ?")
        }
        TabButton {
            width: parent.width
            text: qsTr("How to manage points in my track ?")
        }
        TabButton {
            width: parent.width
            text: qsTr("How to export my track ?")
        }
    }

    StackLayout
    {
        x: subjects.width
        width: parent.width - subjects.width
        currentIndex: subjects.currentIndex
        Item {
            id: createPointTab
            Text
            {
                textFormat: Text.RichText
                text: '<p>To <strong>add </strong>new points to your track you have to use the <span style="color:#3498db">cursor</span>.<br />
                      Click anywhere on the map to place the cursor, you can see on the bottom the information relative to its position. You can also drag and drop it.</p>

                      <p>When you&#39;re satisfied with the position, right click on the cursor to show the context menu.<br />
                      The add marker button will, by default, add a point at the end of the track.</p>

                      <p>There is a few different ways to <strong>add </strong>a marker tho :</p>

                      <ul>
                          <li><span style="color:#9b59b6">Add at the end</span> : it will add the point as the last position of the track at the root of the hierarchy.</li>
                          <li><span style="color:#9b59b6">Add after selected</span> : it will add the point just after the first selected point, at the same depth in the hierarchy.</li>
                          <li><span style="color:#9b59b6">Add as child of selected</span> :&nbsp;it will add the point as last child of the first selected point in the track.</li>
                      </ul>

                      <p>&nbsp;</p>

                      <p>To <strong>remove </strong>a point :</p>

                      <ul>
                          <li>Right click on it&#39;s marker on the map and select &quot;Remove&quot;.</li>
                          <li>Right click on the point in the list of points and select &quot;Remove&quot;.</li>
                          <li>Select it, click it on the map or on the list and press the delete key.</li>
                      </ul>'
            }
        }
        Item {
            id: managePointsTab
            Text
            {
                textFormat: Text.RichText
                text: '<p>On the left of the screen you can see the <strong>list of point composing your track</strong>.<br />
                      They are organised as a tree : each point can have other points as children.<br />
                      This way you should be able to organise your track as you want.</p>

                      <p>In the list you can see a few information about each points :</p>

                      <ul>
                          <li>a checkbox to <span style="color:#9b59b6">enable or disable</span> the point.

                          <ul>
                              <li><em>a disabled poitn won&#39;t be visible on the map, will disable its children and they&nbsp;won&#39;t be exported in the .gpx file.</em></li>
                          </ul>
                          </li>
                          <li>the <span style="color:#9b59b6">ID </span>corresponding to the number of the markers diplayed in the map.</li>
                          <li>the <span style="color:#9b59b6">name </span>of the point, set up to the city where it was created.</li>
                          <li>if the point have children a <span style="color:#9b59b6">little indicator</span> will be visible on the begin of the line to toggle the visibility of the children.</li>
                          <li>the button at the end of the line is here if the point have children and is used to control if the point is treated as a <span style="color:#9b59b6">loop point</span> on not.
                          <ul>
                              <li><em>if a point is a loop point the track will pass twice through it, once while following the order of the points, and an other time after passing through all of its children.</em></li>
                          </ul>
                          </li>
                      </ul>

                      <p>You can right click any point to :</p>

                      <ul>
                          <li><strong>remove </strong>it</li>
                          <li><strong>rename </strong>it</li>
                      </ul>

                      <p>It&#39;s also possible to reorganise the points of you track.<br />
                      To do that you can drag and drop any of them.<br />
                      While draggin a point you should see indicator to visualise where you&#39;re about to move it.</p>

                      <p>A poitn can be move anywhere in the hiererchy, you can move it to a new parent or all the way up to the hierarchy root.<br />
                      If you drop it on another point it will add it draggin as a child.</p>

                      <p>&nbsp;</p>

                      <p>On the map view you can see the markers corresponding to the <strong>active</strong> <strong>points&nbsp;</strong>present on the list.<br />
                      Any off those markers can by drag and dropped to <span style="color:#3498db">change its position</span>.</p>'
            }
        }
        Item {
            id: exportTab
            Text
            {
                textFormat: Text.RichText
                onLinkActivated: Qt.openUrlExternally(link)
                text: '<p>When you&#39;re done with the edition of you track you can <strong>export </strong>it as a <span style="color:#9b59b6">.gpx</span> file.</p>

                      <p>To do so just go to the <span style="color:#9b59b6">File </span>menu on the top of the window and select &quot;<span style="color:#9b59b6">Export track as GPX</span>&quot;.<br />
                      Choose where you want to create the file and that&#39;s it.</p>

                      <p>The exported file will contain the list of active points composing your path. Exaclty the one you can visualise when you click the <span style="color:#9b59b6">compute path </span>button.<br />
                      Note that the <span style="color:#9b59b6">loop points</span> will be exported twice, once before their children and once after, to create loops.</p>

                      <p>Once you have your .gpx file use it with you favorite GPS application to follow the track you&#39;ve just created.<br />
                      <a href="https://osmand.net/">OsmAnd</a>&nbsp;is a good choice for exemple.</p>

                      <p>Enjoy the ride !</p>'
            }
        }
    }
}
