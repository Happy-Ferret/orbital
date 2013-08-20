/*
 * Copyright 2013 Giulio Camuffo <giuliocamuffo@gmail.com>
 *
 * This file is part of Orbital
 *
 * Orbital is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Orbital is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Orbital.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.1
import Orbital 1.0

Element {
    id: taskbar

    Layout.preferredWidth: 200
    Layout.preferredHeight: 32
    Layout.fillWidth: true
    Layout.fillHeight: true

    width: Layout.preferredWidth
    height: Layout.preferredHeight

    contentItem: StyleItem {
        anchors.fill: parent
        component: style.taskBarBackground

        Layout {
            spacing: 5
            anchors.fill: parent

            Repeater {
                model: Client.windows

                TaskBarItem {
                    window: modelData
                    taskBar: taskbar
                }
            }
        }
    }
}
