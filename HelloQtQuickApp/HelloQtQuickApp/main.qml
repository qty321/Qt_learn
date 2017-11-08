import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    visible: true
    width: 320
    height: 480

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello Qt Quick App 11111111")
        anchors.centerIn: parent
    }
}
