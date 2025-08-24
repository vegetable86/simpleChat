import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: "QQ version_1.0"

    Button{
        text: "click me"
        anchors.centerIn: parent
        onClicked: console.log("被点击")
    }
}
