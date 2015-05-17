import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

ListItem.Subtitled {
    visible: true
    text: "未知设备"
    subText: "16.68MB"
    secondaryItem: Button {
        text: "断开"
        elevation: 1
        width: 32
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    action: Icon {
        anchors.centerIn: parent
        name: "awesome/laptop"
        size: units.dp(28)
    }

    Dialog {
        id: info
        title: "Detailed Information"
        height: 400
        TextField {
            width: parent.width
            placeholderText: "设备名称"
            floatingLabel: true
        }
        ListItem.Subtitled {
            height: 40
            margins: units.dp(2)
            text: "上线时间"
            subText: "05月13日 17:56"
        }
        ListItem.Subtitled {
            height: 40
            margins: units.dp(2)
            text: "IP地址"
            subText: "59.66.133.25"
        }
        ListItem.Subtitled {
            height: 40
            margins: units.dp(2)
            text: "MAC地址"
            subText: "未提交"
        }
        ListItem.Subtitled {
            height: 40
            margins: units.dp(2)
            text: "流量统计"
            subText: "3.50MB"
        }
    }

    onClicked: info.show()
}
