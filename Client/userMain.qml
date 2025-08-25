import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    width: 800
    height: 600
    visible: true
    color: "#121212" // 设置主窗口背景颜色

    // 搜索框
    Rectangle {
        id: searchInput
        x: 40
        y: 38
        width: 720
        height: 46
        radius: 23
        color: "#1e1e1e"
        border.color: "#cccccc"
        border.width: 1
        z: 1

        Row {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10
            Image {
                id: searchIcon
                source: "qrc:/searchIcon.png"
                width: 20
                height: 20
                fillMode: Image.PreserveAspectFit
            }

            TextInput {
                id: textInput
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - 40
                height: parent.height - 20
                text: qsTr("Search")
                font.pixelSize: 14
                color: "white" // 默认文字颜色为白色
                focus: false
                selectByMouse: true // 允许鼠标选择文本

                onActiveFocusChanged: {
                    if (activeFocus) {
                        searchInput.border.color = "#66aaff"
                        // 获得焦点时不改变文字颜色，保持白色
                        if (textInput.text === "Search") {
                            textInput.text = "" // 清空默认文本
                        }
                    } else {
                        searchInput.border.color = "#cccccc"
                        if (textInput.text === "") {
                            textInput.text = "Search" // 恢复默认文本
                        }
                    }
                }

                onTextChanged: {
                    // 确保输入的文字始终是白色
                    textInput.color = "white"
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.NoButton // 不拦截鼠标点击事件
            onEntered: {
                if (!textInput.activeFocus) {
                    searchInput.color = "#2a2a2a" // 悬浮变浅
                }
            }
            onExited: {
                if (!textInput.activeFocus) {
                    searchInput.color = "#1e1e1e" // 回到默认
                }
            }
            cursorShape: Qt.IBeamCursor // 鼠标悬停时显示文本光标
        }
    }

    // 左侧好友列表 + 添加好友按钮
    Column {
        x: root.width * 0.05
        y: root.height * 0.1 + 30
        width: root.width * 0.2
        spacing: 10

        // 好友列表
        Rectangle {
            id: friendList
            width: parent.width
            height: root.height * 0.7
            radius: 20
            color: "#1e1e1e"
            border.color: "#444444"
            border.width: 1

            ListView {
                anchors.fill: parent
                spacing: 10
                clip: true
                header: Item { height: 40 } // 顶部内边距

                model: ListModel {
                    ListElement { friendName: "Alice" }
                    ListElement { friendName: "Bob" }
                    ListElement { friendName: "Charlie" }
                }

                delegate: Rectangle {
                    id: friendItem
                    width: parent.width * 0.9
                    height: 50
                    radius: 15
                    color: "#2b2b2b"
                    anchors.horizontalCenter: parent.horizontalCenter

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onEntered: friendItem.color = "#3c3c3c"
                        onExited: friendItem.color = "#2b2b2b"
                    }

                    Row {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 10

                        Image {
                            source: "userIcon.png"
                            width: 30
                            height: 30
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: friendName
                            font.pixelSize: 14
                            color: "#ffffff"
                        }

                        Image {
                            source: "statusIcon.png"
                            width: 16
                            height: 16
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                        }
                    }
                }
            }
        }

        // 添加好友按钮
        Rectangle {
            id: addFriendButton
            width: parent.width
            height: 50
            radius: 15
            color: "#2b2b2b"
            border.color: "#444444"
            border.width: 1

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true
                onEntered: addFriendButton.color = "#3c3c3c"
                onExited: addFriendButton.color = "#2b2b2b"
                onClicked: {
                    // 点击事件逻辑
                    console.log("添加好友按钮被点击")
                }
            }

            Row {
                anchors.centerIn: parent
                spacing: 10
                Image {
                    source: "qrc:/addIcon.png"
                    width: 20
                    height: 20
                    fillMode: Image.PreserveAspectFit
                }
                Text {
                    text: "添加好友"
                    font.pixelSize: 14
                    color: "#ffffff"
                }
            }
        }
    }
}
