import QtQuick
import QtQuick.Controls
import hmi.AppView 1.0

Item {
    id: root
    x: AppView.screenState.x
    y: AppView.screenState.y
    z: AppView.screenState.z
    width: AppView.screenState.width
    height: AppView.screenState.height
    enabled: AppView.screenState.enabled
    visible: AppView.screenState.visible
    opacity: AppView.screenState.opacity

    Loader {
        id: headerContainer
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        sourceComponent: AppView.screenState.headerContainer
    }

    Loader {
        id: footerContainer
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        sourceComponent: AppView.screenState.footerContainer
    }

    Loader {
        id: leftContainer
        anchors {
            top: headerContainer.bottom
            left: parent.left
            bottom: footerContainer.top
        }
        sourceComponent: AppView.screenState.leftContainer
    }

    Loader {
        id: rightContainer
        anchors {
            top: headerContainer.bottom
            left: parent.right
            bottom: footerContainer.top
        }
        sourceComponent: AppView.screenState.rightContainer
    }

    Loader {
        id: centerContainer
        anchors {
            top: headerContainer.bottom
            left: rightContainer.right
            right: rightContainer.left
            bottom: footerContainer.top
        }
        sourceComponent: AppView.screenState.centerContainer
    }
}