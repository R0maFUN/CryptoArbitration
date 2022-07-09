import QtQuick 2.5
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "." as Views

Item {
    id: root

    property string label: ""
    property alias text: textField.text

    signal editingFinished()

    implicitHeight: 40
    implicitWidth: labelRect.width + textField.width

    Base {
        id: base
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

        RowLayout {
            id: rowLayout
            anchors.fill: radiusRect

            spacing: 0

            Rectangle {
                id: labelRect

                Layout.fillHeight: true
                Layout.minimumWidth: 100
                Layout.maximumWidth: 140
                Layout.preferredWidth: t_metrics.tightBoundingRect.width + 10 + 10

                LinearGradient {
                    anchors.fill: labelRect
                    visible: !modelData.enabled
                    source: labelRect
                    start: Qt.point(0, 0)
                    end: Qt.point(labelRect.width, labelRect.height)
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: base.disabledGradientStart }
                        GradientStop { position: 1.0; color: base.disabledGradientEnd }
                    }
                }

                Views.Label {
                    id: _label

                    height: labelRect.height
                    anchors.left: labelRect
                    anchors.leftMargin: 10
                    x: 10

                    text: root.label
                    color: base.base50
                    verticalAlignment: Text.AlignVCenter
                }

                TextMetrics {
                    id:     t_metrics
                    font:   _label.font
                    text:   _label.text
                }
            }

            TextField {
                id: textField

                Layout.fillHeight: true
                Layout.minimumWidth: 100
                Layout.maximumWidth: 120

                validator: IntValidator {}
                //Layout.preferredWidth: t_metrics.tightBoundingRect.width

                style: TextFieldStyle {
                    textColor: base.base500
                    font: _label.font
                    background: Rectangle {
                        anchors.fill: textField
                        color: base.base100
                    }
                }

                onEditingFinished: root.editingFinished()
            }
        }
    }
}
