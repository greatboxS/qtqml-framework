import QtQuick

Window {
    id: root
    property string name: "Demo app"
    property var application
    width: 450
    height: 450
    visible: true

    Text {
        text: "Hello form Demo app"
    }

    Component.onCompleted: {
        console.log("On Demo app completed")
    }
}