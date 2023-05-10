import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1

import TriangulationView 1.0

ApplicationWindow {
    id: root
    width: 640
    height: 640
    visible: true
    title: qsTr("Triangulation")

    header: Pane {
        palette.window: "#FAFAFA"
        height: 48
        padding: 4

        contentItem: RowLayout {
            Button {
                Layout.fillHeight: true
                palette.button: "#F0F0F0"
                text: "File"

                onClicked: menu.open()

                Menu {
                    id: menu
                    title: "File"

                    MenuItem {
                        text: "Load"

                        onTriggered: {
                            fileDialog.title = "Выберите файл для загрузки"
                            fileDialog.fileMode = FileDialog.OpenFile
                            fileDialog.isSave = false
                            fileDialog.open()
                        }
                    }

                    MenuItem {
                        text: "Save"

                        onTriggered: {
                            fileDialog.title = "Выберите файл для сохранения"
                            fileDialog.fileMode = FileDialog.SaveFile
                            fileDialog.isSave = true
                            fileDialog.open()
                        }
                    }

                    FileDialog {
                        id: fileDialog

                        property bool isSave: false

                        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)

                        onAccepted: {
                            if (isSave) {
                                core.saveToFile(file)
                            } else {
                                core.openFromFile(file)
                            }
                        }
                    }
                }
            }

            Button {
                Layout.fillHeight: true
                palette.button: "#F0F0F0"
                text: "Help"

                onClicked: {
                    helpDialog.open()
                }

                MessageDialog {
                    id: helpDialog
                    text: "Это программа позволяет динамически строить по заданным точкам на плоскасти триангуляцию Делоне\nКликайте на центральное поле чтобы поставить точку\nАвтор программы Карачев Данил 2023г"
                    buttons: MessageDialog.Ok
                }
            }

            Button {
                Layout.fillHeight: true
                palette.button: "#F0F0F0"
                text: "Clear"

                onClicked: core.clear()
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                Layout.fillHeight: true
                palette.button: "#F0F0F0"
                text: "Randomize"

                onClicked: core.randomizePoints(textField.text)
            }

            TextField {
                id: textField
                Layout.fillHeight: true
                Layout.preferredWidth: 200
                font.pixelSize: 16
                placeholderText: "Количество точек"
                inputMethodHints: Qt.ImhDigitsOnly
                horizontalAlignment: Text.AlignRight
            }
        }
    }

    Pane {
        anchors.fill: parent
        padding: 8

        contentItem: Rectangle {
            color: "#FAFAFA"

            TriangulationView {
                id: triangulationView
                anchors.fill: parent
                model: core

                MouseArea {
                    anchors.fill: parent

                    onClicked: triangulationView.model.addPoint(mouseX / triangulationView.width, mouseY / triangulationView.height)
                }
            }
        }
    }
}
