import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Item {
    id: root

    implicitWidth: 110
    implicitHeight: button.height

    property alias text: buttonLabel.text

    signal clicked()

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
                root.clicked()
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
                id: buttonLabel
                Layout.fillWidth: true
                Layout.fillHeight: true

                color: base.base50
            }

//            Image {
//                id: arrowsIcon

//                height: 24
//                width: 24
//                Layout.rightMargin: 16
//                Layout.alignment: Qt.AlignRight

//                source: "qrc:/arrow-both-icon"

//                ColorOverlay {
//                    source: arrowsIcon
//                    anchors.fill: arrowsIcon
//                    color: base.base50
//                }
//            }
        }
    }
}
