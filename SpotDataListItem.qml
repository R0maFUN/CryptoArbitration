import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Item {
    id: root

    property var viewModel: null
    property int currentIndex: 0

    property bool isActive: exchanges.visible
    property color textColor: isActive ? base.black : base.white

    implicitHeight: fields.height + (exchanges.visible ? exchanges.contentHeight + exchangesHeader.height : 0)

    function toggleExchanges() {
        exchanges.visible = !exchanges.visible
    }

    Behavior on implicitHeight {
        NumberAnimation { duration: 200 }
    }

    Base {
        id: base
    }

    MouseArea
    {
        id: mouseArea
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            focus = true
            toggleExchanges()
        }
    }

    Rectangle
    {
        id: fieldsBackground
        anchors.fill: fields
        z: 10

        color: isActive ? base.base300 : mouseArea.containsMouse ? base.base500 : base.base600
    }

    InnerShadow {
        anchors.fill: fieldsBackground
        z: fieldsBackground.z
        horizontalOffset: 0
        verticalOffset: 4
        radius: 8
        samples: 17
        color: base.shadowColor
        source: fieldsBackground
    }

    RowLayout
    {
        id: fields

        height: 64
        spacing: 10
        z: fieldsBackground.z

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        Image {
            id: favoriteIcon
            height: 24
            width: 24

            Layout.minimumWidth: 24
            Layout.maximumWidth: 24
            Layout.leftMargin: 20


            source: "star-icon-inactive"

            ColorOverlay {
                source: favoriteIcon
                anchors.fill: favoriteIcon
                color: base.base100
            }
        }

        Label {
            id: pairId

            Layout.minimumWidth: 30
            Layout.maximumWidth: 30
            Layout.preferredWidth: 30
            Layout.fillHeight: true

            text: root.currentIndex
            color: isActive ? base.base500 : base.base300
            font.weight: Font.Light
        }

        RowLayout {
            id: baseCoin

            Layout.minimumWidth: 120
            Layout.maximumWidth: 160
            Layout.preferredWidth: 130
            Layout.fillWidth: true
            Layout.leftMargin: 16
            spacing: 10

            Item {
                height: 24
                width: 24
                Image {
                    id: baseCoinIcon
                    height: 24
                    width: 24
                    sourceSize.width: 24
                    sourceSize.height: 24
                    verticalAlignment: Qt.AlignVCenter

                    source: (viewModel ? viewModel.baseCoinSymbol.toLowerCase() : "") + "-icon"
                    onStatusChanged: {
                        if (status == Image.Error)
                            source = "default-icon"
                    }

                    //source: "https://cryptoicons.org/api/icon/" + (viewModel ? viewModel.baseCoinSymbol.toLowerCase() : "") + "/24"
                }

                DropShadow {
                    anchors.fill: baseCoinIcon
                    horizontalOffset: 2
                    verticalOffset: 2
                    radius: 8
                    samples: 17
                    color: base.shadowColor
                    source: baseCoinIcon
                }
            }

            Column {
                spacing: 0

                Layout.fillWidth: true

                Label {
                    width: baseCoin.width - 24
                    horizontalAlignment: Text.AlignLeft

                    text: {
                        const str = viewModel ? viewModel.baseCoinId : ""
                        return str.charAt(0).toUpperCase() + str.slice(1)
                    }

                    wrapMode: Text.WordWrap
                    color: textColor
                }

                Label {
                    horizontalAlignment: Text.AlignLeft

                    text: viewModel ? viewModel.baseCoinSymbol : ""
                    font.weight: Font.ExtraLight
                    color: isActive ? textColor : base.base100
                    font.pixelSize: 14
                }
            }
        }

        RowLayout {
            id: quoteCoin

            Layout.minimumWidth: 120
            Layout.maximumWidth: 160
            Layout.preferredWidth: 130
            Layout.leftMargin: 16
            spacing: 10

            Item {
                height: 24
                width: 24
                Image {
                    id: quoteCoinIcon
                    height: 24
                    width: 24
                    sourceSize.width: 24
                    sourceSize.height: 24
                    Layout.maximumWidth: 24
                    Layout.preferredWidth: 24

                    source: (viewModel ? viewModel.quoteCoinSymbol.toLowerCase() : "") + "-icon"
                    //source: "http://cryptoicons.org/api/icon/" + (viewModel ? viewModel.quoteCoinSymbol : "") + "/24"
                }

                DropShadow {
                    anchors.fill: quoteCoinIcon
                    horizontalOffset: 2
                    verticalOffset: 2
                    radius: 8
                    samples: 17
                    color: base.shadowColor
                    source: quoteCoinIcon
                }
            }

            Column {
                spacing: 0
                Layout.fillWidth: true

                Label {
                    horizontalAlignment: Text.AlignLeft

                    text: {
                        const str = viewModel ? viewModel.quoteCoinId : ""
                        return str.charAt(0).toUpperCase() + str.slice(1)
                    }
                    color: textColor
                }

                Label {
                    horizontalAlignment: Text.AlignLeft

                    text: viewModel ? viewModel.quoteCoinSymbol : ""
                    font.weight: Font.ExtraLight
                    font.pixelSize: 14
                    color: isActive ? textColor : base.base100
                }
            }
        }

        Label {
            id: maxPrice

            Layout.minimumWidth: 100
            Layout.maximumWidth: 160
            Layout.preferredWidth: 140
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: viewModel ? viewModel.maxPrice : ""
            horizontalAlignment: Text.AlignRight
            font.weight: Font.Light
            color: textColor
        }

        Label {
            id: minPrice

            Layout.minimumWidth: 100
            Layout.maximumWidth: 160
            Layout.preferredWidth: 140
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: viewModel ? viewModel.minPrice : ""
            horizontalAlignment: Text.AlignRight
            font.weight: Font.Light
            color: textColor
        }

        Label {
            id: spread

            Layout.minimumWidth: 100
            Layout.maximumWidth: 160
            Layout.preferredWidth: 140
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: viewModel ? viewModel.spread + "%" : ""
            font.weight: Font.Light
            color: textColor
        }

        Item {
            Layout.fillWidth: true
        }
    }

    Rectangle
    {
        id: exchangesHeaderBackground
        anchors.fill: exchangesHeader
        z: fieldsBackground.z - 1

        color: isActive ? base.base500 : "transparent"
    }

    InnerShadow {
        anchors.fill: exchangesHeaderBackground
        z: exchangesHeaderBackground.z
        horizontalOffset: 0
        verticalOffset: 4
        radius: 8
        samples: 17
        color: base.shadowColor
        source: exchangesHeaderBackground
    }

    RowLayout
    {
        id: exchangesHeader

        visible: exchanges.visible

        spacing: 0
        width: exchanges.width
        height: 40
        anchors.top: fields.bottom
        z: exchangesHeaderBackground.z

        Item {
            Layout.minimumWidth: 24
            Layout.maximumWidth: 24
            Layout.preferredWidth: 24
            Layout.leftMargin: 20
        }

        Label {
            Layout.minimumWidth: 120
            Layout.maximumWidth: 160
            Layout.preferredWidth: 130
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin: 24

            text: qsTr("Exchange")
            color: textColor
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            horizontalAlignment: Text.AlignLeft
        }

        Label {
            Layout.minimumWidth: 120
            Layout.maximumWidth: 160
            Layout.preferredWidth: 130
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: qsTr("Price")
            color: textColor
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            horizontalAlignment: Text.AlignLeft
        }

        Label {
            Layout.minimumWidth: 160
            Layout.maximumWidth: 220
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: qsTr("Price Usd")
            color: textColor
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            horizontalAlignment: Text.AlignRight
        }

        Label {
            Layout.minimumWidth: 160
            Layout.maximumWidth: 220
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: qsTr("Volume $(24h)")
            color: textColor
            font.weight: Font.DemiBold
            font.pixelSize: base.h3size
            horizontalAlignment: Text.AlignRight
        }

        Item {
            Layout.fillWidth: true
        }
    }

    ListView {
        id: exchanges

        visible: false

        //anchors.leftMargin: 32
        //anchors.rightMargin: 16
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: exchangesHeader.bottom
        anchors.bottom: parent.bottom

        model: viewModel ? viewModel.items : null

        delegate: Item
        {
            height: 64
            width: exchanges.width

            Rectangle
            {
                id: exchangeFieldsBackground
                anchors.fill: exchangeFields

                color: isActive ? base.base300 : "transparent"
            }

            InnerShadow {
                anchors.fill: exchangeFieldsBackground
                horizontalOffset: 0
                verticalOffset: 4
                radius: 8
                samples: 17
                color: base.shadowColor
                source: exchangeFieldsBackground
            }

            RowLayout {
                id: exchangeFields

                anchors.fill: parent
                spacing: 0

                Image {
                    id: exchangeFavoriteIcon
                    height: 24
                    width: 24

                    Layout.minimumWidth: 24
                    Layout.maximumWidth: 24
                    Layout.leftMargin: 20

                    source: "star-icon-active"
                    ColorOverlay {
                        source: exchangeFavoriteIcon
                        anchors.fill: exchangeFavoriteIcon
                        color: base.base100
                    }
                }

                Label {
                    id: serviceName

                    Layout.minimumWidth: 120
                    Layout.maximumWidth: 160
                    Layout.preferredWidth: 130
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.leftMargin: 24

                    text: modelData.service.name
                    color: textColor
                    horizontalAlignment: Text.AlignLeft

                    MouseArea {
                        anchors.fill: serviceName
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: console.log("clicked, url = " + modelData.service.url)
                    }
                }

                Label {
                    id: price

                    Layout.minimumWidth: 120
                    Layout.maximumWidth: 160
                    Layout.preferredWidth: 130
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    text: modelData.price
                    font.weight: Font.Light
                    color: textColor
                    horizontalAlignment: Text.AlignLeft
                }

                Label {
                    id: priceUsd

                    Layout.minimumWidth: 160
                    Layout.maximumWidth: 220
                    Layout.preferredWidth: 200
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    text: modelData.priceUsd + "$"
                    font.weight: Font.Light
                    color: textColor
                    horizontalAlignment: Text.AlignRight
                }

                Label {
                    id: volume

                    Layout.minimumWidth: 160
                    Layout.maximumWidth: 220
                    Layout.preferredWidth: 200
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    text: modelData.volumeUsd24Hr
                    font.weight: Font.Light
                    color: textColor
                    horizontalAlignment: Text.AlignRight
                }

                Item {
                    Layout.fillWidth: true
                }
            }
        }
    }
}
