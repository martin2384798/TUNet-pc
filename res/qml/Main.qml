import QtQuick 2.2
import Material 0.1
import Material.ListItems 0.1 as ListItem

ApplicationWindow {
    id: demo
    visible: true
    width: 400
    height: 500
    theme {
        accentColor: "#009688"
    }

    property var components: [
            "Account",
            "Connection"
    ]

    property var componentLabels: [
            "账户信息",
            "在线状态"
    ]

    property int selectedComponent: 0

    User {
        id: user
    }

    About {
        id: about
    }

    initialPage: Page {
        title: "fangy14"
        actions: [
            Action {
                iconName: "awesome/user"
                name: "Account"
                onTriggered: user.show()
            },
            Action {
                iconName: "awesome/cog"
                name: "Settings"
            },
            Action {
                iconName: "awesome/bug"
                name: "Bug"
            },
            Action {
                iconName: "awesome/group"
                name: "About"
                onTriggered: about.show()
            }
        ]

        Sidebar {
            id: sidebar
            width: 100
            Column {
                width: parent.width
                Repeater {
                    model: 2
                    delegate: ListItem.Standard {
                        text: componentLabels[modelData]
                        selected: modelData == selectedComponent
                        onClicked: selectedComponent = modelData
                    }
                }
            }
        }

        Flickable {
            id: flickable
            anchors {
                left: sidebar.right
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            clip: true
            contentHeight: Math.max(example.implicitHeight + 40, height)
            Loader {
                id: example
                anchors.fill: parent
                // selectedComponent will always be valid, as it defaults to the first component
                source: Qt.resolvedUrl("%.qml").arg(components[selectedComponent].replace(" ", ""))
            }
        }

        Scrollbar {
            flickableItem: flickable
        }

    }
}
