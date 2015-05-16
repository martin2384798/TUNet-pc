import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

Dialog {
    id: user
    title: "Account setting"
    height: 240

    TextField {
        id: username
        width: parent.width
        height: 40
        placeholderText: "用户名/学号"
        floatingLabel: true
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: password
        width: parent.width
        height: 40
        placeholderText: "密码"
        floatingLabel: true
        input.echoMode: TextInput.Password
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
