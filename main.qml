import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: root
    width: 1100
    height: 700
    visible: true
    title: qsTr("Hello World")
    color: base.base600

    property var spotDataStorageViewModel: viewModel ? viewModel.spotData : null

    Base {
        id: base
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            console.log("base mouse area pressed")
            focus = true
        }
    }

    PrimaryButton {
        id: updateButton
        text: qsTr("Update")

        x: 10

        onClicked: {
            if (spotDataStorageViewModel)
                spotDataStorageViewModel.update()
        }
    }

//    PrimaryButton {
//        id: sortButton
//        text: qsTr("Sort")

//        anchors.left: updateButton.right
//        anchors.leftMargin: 10

//        onClicked: {
//            if (spotDataStorageViewModel)
//                spotDataStorageViewModel.sort()
//        }
//    }

//    DropDownCombobox {
//        id: exchangesCombobox

//        anchors.top: sortButton.bottom
//        anchors.topMargin: 10
//        x: 10

//        z: 1

//        listModel: viewModel ? viewModel.settings.services : null
//    }

//    TextFieldWithLabel {
//        anchors.top: sortButton.bottom
//        anchors.topMargin: 10
//        anchors.left: exchangesCombobox.right
//        anchors.leftMargin: 10

//        label: qsTr("Min Volume")
//        text: viewModel ? viewModel.settings.minVolume : null

//        onEditingFinished: {
//            if (viewModel)
//                viewModel.settings.minVolume = text
//        }
//    }

//    RowLayout
//    {
//        anchors {
//            left: parent.left
//            right: parent.right
//            top: sortButton.bottom
//            bottom: parent.bottom

//            topMargin: 60
//        }

//        SpotDataList
//        {
//            id: spotData

//            Layout.maximumWidth: 1200
//            Layout.minimumWidth: 800
//            Layout.fillWidth: true
//            Layout.fillHeight: true

//            spotDataStorageViewModel: root.spotDataStorageViewModel ?? null
//        }
//    }
}
