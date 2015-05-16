import QtQuick 2.0
import Material 0.1
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

Item {
    View {
        elevation: 1

        anchors {
            fill: parent
            margins: units.dp(8)
        }

        Column {
            anchors.fill: parent

            ListItem.Subtitled {
                text: "流量统计"
                subText: "13.62GB"
                action: Icon {
                    anchors.centerIn: parent
                    name: "hardware/desktop_mac"
                    size: units.dp(28)
                }
            }

            ListItem.Subtitled {
                text: "登陆时长"
                subText: "44:21:11"
                action: Icon {
                    anchors.centerIn: parent
                    name: "device/access_alarm"
                    size: units.dp(28)
                }
            }

            ListItem.Subtitled {
                text: "余额"
                subText: "1.94RMB"
                secondaryItem: Button {
                    text: "充值"
                    elevation: 1
                    width: 32
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                action: Icon {
                    anchors.centerIn: parent
                    name: "awesome/uniF1C0"
                    size: units.dp(28)
                }
            }
        }
    }
}
