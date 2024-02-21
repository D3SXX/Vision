

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

    Frame {
        id: frame
        x: 0
        y: 0
        width: 300
        height: 1080

        ListView {
            id: listView
            x: -12
            y: 92
            width: 300
            height: 976
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    spacing: 10
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                }
            }
        }
    }

    Frame {
        id: frame1
        x: 300
        y: 874
        width: 1620
        height: 206

        ProgressBar {
            id: progressBar
            x: -12
            y: -12
            width: 1620
            height: 206
            value: 0.5
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

            BorderImage {
                id: borderImage
                x: -12
                y: -12
                width: 500
                height: 494
                source: "qrc:/qtquickplugin/images/template_image.png"
            }
        }

        Frame {
            id: frame4
            x: 180
            y: 113
            width: 762
            height: 500

            Text {
                id: text3
                x: 69
                y: 67
                width: 600
                height: 69
                text: qsTr("Title")
                font.pixelSize: 30
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: text4
                x: 69
                y: 142
                width: 600
                height: 69
                text: qsTr("Title")
                font.pixelSize: 30
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }

        RoundButton {
            id: roundButton
            x: 804
            y: 728
            width: 77
            height: 76
            radius: 72
            text: "▶️"
            font.pointSize: 30
            display: AbstractButton.TextBesideIcon
            icon.cache: true
            icon.width: 26
            flat: false
        }

        Control {
            id: control
            x: 707
            y: 741
            width: 271
            height: 63
        }

        Text {
            id: text5
            x: 261
            y: 329
            width: 300
            height: 69
            text: qsTr("Title")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: text6
            x: 567
            y: 329
            width: 300
            height: 69
            text: qsTr("Title")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }

    Rectangle {
        id: rectangle1
        x: 0
        y: 0
        width: 300
        height: 96
        color: "#ffffff"

        Text {
            id: text1
            x: 8
            y: 8
            width: 284
            height: 80
            text: qsTr("Vision")
            font.pixelSize: 56
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: text2
            x: 190
            y: 65
            width: 55
            height: 17
            text: qsTr("Dev")
            font.pixelSize: 21
        }
    }
    states: [
        State {
            name: "clicked"
        }
    ]
}
