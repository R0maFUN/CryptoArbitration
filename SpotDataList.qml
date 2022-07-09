import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Item {
    id: root

    property var spotDataStorageViewModel: null

    Base {
        id: base
    }

    Rectangle
    {
        id: listHeaderBackground
        anchors.fill: listHeader

        color: base.base700
    }

    DropShadow {
        anchors.fill: listHeaderBackground
        horizontalOffset: 0
        verticalOffset: 4
        radius: 8
        samples: 17
        color: base.shadowColor
        source: listHeaderBackground
    }

    RowLayout {
        id: listHeader
        width: listView.width
        height: 40

        property color textColor: base.white

        anchors.top: root.top

        Label {
            Layout.minimumWidth: 60
            Layout.maximumWidth: 60
            Layout.preferredWidth: 60
            Layout.fillHeight: true
            Layout.leftMargin: 20

            text: "#"
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            horizontalAlignment: Text.AlignRight
            color: listHeader.textColor
        }

        Label {
            Layout.minimumWidth: 120
            Layout.maximumWidth: 160
            Layout.preferredWidth: 130
            Layout.fillWidth: true
            Layout.leftMargin: 24
            Layout.fillHeight: true

            text: qsTr("Base coin")
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            horizontalAlignment: Text.AlignLeft
            color: listHeader.textColor
        }

        Label {
            Layout.minimumWidth: 120
            Layout.maximumWidth: 160
            Layout.preferredWidth: 130
            Layout.leftMargin: 16
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: qsTr("Quote coin")
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            horizontalAlignment: Text.AlignLeft
            color: listHeader.textColor
        }

        Label {
            Layout.minimumWidth: 100
            Layout.maximumWidth: 160
            Layout.preferredWidth: 140
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: qsTr("Max Price")
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            horizontalAlignment: Text.AlignRight
            color: listHeader.textColor
        }

        Label {
            Layout.minimumWidth: 100
            Layout.maximumWidth: 160
            Layout.preferredWidth: 140
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: qsTr("Min Price")
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            horizontalAlignment: Text.AlignRight
            color: listHeader.textColor
        }

        Label {
            Layout.minimumWidth: 100
            Layout.maximumWidth: 160
            Layout.preferredWidth: 140
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: qsTr("Spread %")
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            color: listHeader.textColor
        }

        Item {
            Layout.fillWidth: true
        }
    }

    ListView
    {
        id: listView
        anchors {
            left: root.left
            right: root.right
            top: listHeader.bottom
            bottom: root.bottom
        }
        clip: true

        model: spotDataStorageViewModel ? spotDataStorageViewModel.items : null

        delegate: SpotDataListItem
        {
            viewModel: modelData
            currentIndex: index

            width: listView.width
            height: implicitHeight
        }

        Component.onCompleted: console.log("model: " + model + " , size = " + model.rowCount())
    }
}
