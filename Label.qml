import QtQuick 2.0

Text {
    id: root

    Base {
        id: base
    }

    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter

    font.pixelSize: base.h2size
    font.family: "SF Pro Display"
}
