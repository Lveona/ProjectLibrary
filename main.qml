import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1920
    height: 720

    Loader{
        id: progressBarLoader
        active: true
        source: "qrc:/CustomProgress.qml"
    }
}
