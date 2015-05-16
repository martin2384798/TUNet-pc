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
            ConnectionSingle {
                id: connect1
            }
            ConnectionSingle {
                id: connect2
            }
            ConnectionSingle {
                id: connect3
            }
        }
    }
}
