/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.5
import QtQuick.Controls 6.5
import Vision
import QtMultimedia

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Text {
        id: label
        text: qsTr("Hello Vision")
        font.family: Constants.font.family
        anchors.topMargin: 45
        anchors.horizontalCenter: parent.horizontalCenter

        SequentialAnimation {
            id: animation

            ColorAnimation {
                id: colorAnimation1
                target: rectangle
                property: "color"
                to: "#2294c6"
                from: Constants.backgroundColor
            }

            ColorAnimation {
                id: colorAnimation2
                target: rectangle
                property: "color"
                to: Constants.backgroundColor
                from: "#2294c6"
            }
        }
    }

    Frame {
        id: frame
        x: 0
        y: 0
        width: 300
        height: 1080
    }

    Frame {
        id: frame1
        x: 300
        y: 874
        width: 1620
        height: 206

        TextField {
            id: textField
            x: 546
            y: 71
            text: "Controls"
            placeholderText: qsTr("Text Field")
        }
    }

    Frame {
        id: frame2
        x: 300
        y: 0
        width: 1620
        height: 875

        Frame {
            id: frame3
            x: 942
            y: 113
            width: 500
            height: 500
        }

        Frame {
            id: frame4
            x: 181
            y: 113
            width: 761
            height: 500
        }
    }
    states: [
        State {
            name: "clicked"

            PropertyChanges {
                target: label
                text: qsTr("Button Checked")
            }
        }
    ]
}
