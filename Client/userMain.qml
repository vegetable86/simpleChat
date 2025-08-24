import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: "QQ version_1.0" + " username: " + infoMap.userName

    ListView {

        x: root.width * 0.05
        y: root.height* 0.05

        width: root.width * 0.2
        height: root.height

        model: userModel

        delegate: Rectangle {
            height: 40
            width: parent.width * 0.9
            color: "red"
            Text {
                anchors.centerIn: parent
                text: friendName
            }
        }
    }

    // Button{
    //     text: "click me"
    //     anchors.centerIn: parent
    //     onClicked: console.log("被点击")
    // }
}
