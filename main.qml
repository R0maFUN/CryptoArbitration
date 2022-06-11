import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    //property var viewModel

    Button
    {
        id: testButton
        width: 100
        height: 40
        text: "test"

        onClicked: viewModel.testViewModel.testTest()
    }
}
