import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Item {
    id: root

    property bool isActive: false
    implicitWidth: 170
    implicitHeight: button.height + (isActive ? listView.height : 0)

    property var listModel: null

    function show() {
        isActive = true
    }

    function hide() {
        isActive = false
    }

    function toggle() {
        if (isActive)
            hide()
        else
            show()
    }

    Base {
        id: base
    }

    Behavior on implicitHeight {
        NumberAnimation { duration: 200 }
    }

    Rectangle {
        id: radiusRect

        anchors.fill: root

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Item {
                width: radiusRect.width
                height: radiusRect.height
                Rectangle {
                    anchors.centerIn: parent
                    width: radiusRect.width
                    height: radiusRect.height
                    radius: 10
                }
            }
        }

        MouseArea {
            anchors.fill: button
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onClicked: {
                focus = true
                root.toggle()
            }
        }

        Rectangle {
            id: buttonBackground
            anchors.fill: button

            LinearGradient {
                anchors.fill: buttonBackground
                source: buttonBackground
                start: Qt.point(0, 0)
                end: Qt.point(buttonBackground.width, buttonBackground.height)
                gradient: Gradient {
                    GradientStop { position: 0.0; color: base.primaryGradientStart }
                    GradientStop { position: 1.0; color: base.primaryGradientEnd }
                }
            }
        }

        RowLayout {
            id: button

            anchors {
                left: parent.left
                top: parent.top
                right: parent.right
            }

            height: 40

            Label {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.leftMargin: 16

                text: qsTr("Exchanges")
                color: base.base50
            }

            Image {
                id: arrowsIcon

                height: 24
                width: 24
                Layout.rightMargin: 16
                Layout.alignment: Qt.AlignRight

                source: "qrc:/arrow-both-icon"

                ColorOverlay {
                    source: arrowsIcon
                    anchors.fill: arrowsIcon
                    color: base.base50
                }
            }
        }

        ListView {
            id: listView
            anchors {
                left: parent.left
                top: button.bottom
                right: parent.right
            }

            property int itemHeight: 40

            clip: true
            height: count > 5 ? itemHeight * 5 : itemHeight * count
            boundsBehavior: Flickable.StopAtBounds

            model: root.listModel

            delegate: Item {

                height: listView.itemHeight
                width: listView.width

                Rectangle {
                    id: exchangeRowBackground
                    anchors.fill: labelWithIcon

                    LinearGradient {
                        anchors.fill: exchangeRowBackground
                        visible: modelData.enabled
                        source: exchangeRowBackground
                        start: Qt.point(0, 0)
                        end: Qt.point(exchangeRowBackground.width, exchangeRowBackground.height)
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: base.primaryGradientStart }
                            GradientStop { position: 1.0; color: base.primaryGradientEnd }
                        }
                    }

                    LinearGradient {
                        anchors.fill: exchangeRowBackground
                        visible: !modelData.enabled
                        source: exchangeRowBackground
                        start: Qt.point(0, 0)
                        end: Qt.point(exchangeRowBackground.width, exchangeRowBackground.height)
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: base.disabledGradientStart }
                            GradientStop { position: 1.0; color: base.disabledGradientEnd }
                        }
                    }
                }

                RowLayout {
                    id: labelWithIcon

                    anchors.fill: parent

                    //height: 40

                    Image {
                        id: exchangeIcon

                        height: 24
                        width: 24
                        Layout.leftMargin: 16

                        source: "qrc:/binance-icon"
                    }

                    Label {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.rightMargin: 16

                        text: modelData.label
                        color: modelData.enabled ? base.base50 : base.base600
                    }
                }

                MouseArea {
                    anchors.fill: labelWithIcon
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    visible: root.isActive

                    onClicked: modelData.toggleEnabled()
                }
            }
        }
    }
}
