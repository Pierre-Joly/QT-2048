import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Window {
    id: root
    y: 0
    width: 480
    height: 690
    maximumHeight: 690
    maximumWidth: 480
    minimumHeight: 690
    minimumWidth: 480
    visible: true
    color: "#faf8ef"
    title: qsTr("2048")

    Rectangle {
        id: grille
        x: 32
        y: 235
        width: 420
        height: 420
        color: "#bbada0"
        radius: 8
        border {
            color: "#bbada0"
            width: 0
        }

        focus: true

        Keys.onPressed: {
            switch (event.key) {
                case Qt.Key_Up:
                    vueObjet.up();
                    break;
                case Qt.Key_Down:
                    vueObjet.down();
                    break;
                case Qt.Key_Left:
                    vueObjet.left();
                    break;
                case Qt.Key_Right:
                    vueObjet.right();
                    break;
            }
        }

        Grid {
            id: grid
            x: 10
            y: 10
            width: 400
            height: 400
            layer.enabled: false
            spacing: 0
            rows: 4
            columns: 4

            Repeater {
                model: 16
                Rectangle {
                    id: tile
                    width: 100
                    height: 100
                    color: vueObjet.color[index]
                    radius: 8
                    scale: 0.9
                    Text {
                        id: tileText         
                        font.family: "Clear Sans Bold"
                        color: "#1B1B1B"
                        font.bold: true
                        font.pixelSize: 40
                        text: vueObjet.number[index]  
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }

    Rectangle {
        id: rectangle2
        x: 332
        y: 30
        width: 120
        height: 70
        color: "#b2a08b"
        radius: 8

        Text {
            id: bestScoreText
            x: 0
            y: 0
            width: 120
            height: 35
            color: "#ede3d8"
            text: qsTr("Highscore")
            font.family: "Clear Sans Bold"
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: bestScoreValue
            x: 0
            y: 35
            width: 120
            height: 35
            color: "#ffffff"
            text: vueObjet.highScoreQML
            font.family: "Arial Black"
            font.pixelSize: 20
            anchors.centerIn: parent
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenterOffset: 18
            anchors.horizontalCenterOffset: 0
        }
    }



    Rectangle {
        x: 188
        y: 30
        width: 120
        height: 70
        color: "#b2a08b"
        radius: 8

        Text {
            id: scoreText
            x: 0
            y: 0
            width: 120
            height: 35
            color: "#ede3d8"
            text: qsTr("Score")
            font.family: "Clear Sans Bold"
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: scoreValue
            x: 0
            y: 35
            width: 120
            height: 35
            color: "#ffffff"
            text: vueObjet.scoreQML
            font.family: "Arial Black"
            font.pixelSize: 20
            anchors.centerIn: parent
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenterOffset: 18
            anchors.horizontalCenterOffset: 0
        }
    }

    Rectangle {
        x: 188
        y: 120
        width: 120
        height: 40
        color: "#f2734f"
        radius: 8

        Text {
            x: 0
            y: 120
            width: 120
            height: 40
            color: "#ffffff"
            text: "New"
            font.family: "Arial Black"
            font.pixelSize: 20
            anchors.centerIn: parent
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 0
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                vueObjet.restart()
            }
        }
    }

    Rectangle {
        x: 332
        y: 120
        width: 120
        height: 40
        color: "#f2734f"
        radius: 8

        Text {
            x: 0
            y: 120
            width: 120
            height: 40
            color: "#ffffff"
            text: "Undo"
            font.family: "Arial Black"
            font.pixelSize: 20
            anchors.centerIn: parent
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 0
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                vueObjet.undo()
            }
        }

    }

    Rectangle {
        id: rectangle1
        x: 32
        y: 30
        width: 130
        height: 130
        color: "#ebcc71"
        radius: 8
    }
    Text {
        id: titre
        x: 48
        y: 75
        width: 99
        height: 41
        color: "#ffffff"
        text: qsTr("2048")
        font.family: "Clear Sans Bold"
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
    }
}
