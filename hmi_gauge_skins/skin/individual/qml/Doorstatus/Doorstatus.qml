import QtQuick 2.8
import "../Common/"
import qmlEnums 1.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0

Item {
    id: doorstatus
    width: 1920
    height: 720
    visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1

    property bool     hoodSts      : PopupScreen.popupDataObject.hood
    property bool     flDoorSts    : PopupScreen.popupDataObject.flDoor
    property bool     frDoorSts    : PopupScreen.popupDataObject.frDoor
    property bool     rlDoorSts    : PopupScreen.popupDataObject.rlDoor
    property bool     rrDoorSts    : PopupScreen.popupDataObject.rrDoor
    property bool     tailSts      : PopupScreen.popupDataObject.tail

    Loader{
        id: loaderDoorStatus
        active: true//doorstatus.visible
        sourceComponent: comDoorStatus
        onLoaded: {
            active = true
        }
    }

    Component{
        id: comDoorStatus
        Item{
            width: 201
            height: 297
            x:1505
            y:199
            Image{
                id :door_bg
                source: "areaD_dooropen.png"
                width: sourceSize.width
                height: sourceSize.height
            }
            Image{
                id :frontright
                source: "areaD_dooropen_red2.png"
                x: parent.x +135
                y: parent.y +69
                visible: frDoorSts
            }

            Image {
                id: backright
//                source: "areaD_dooropen_red3.png"
            }


            Image {
                id: backleft
//                source: "areaD_dooropen_red4.png"
            }

            Image {
                id: frontleft
                source: "areaD_dooropen_red1.png"
                x: 1468-parent.x
                y: parent.y+65
                visible: flDoorSts
            }

        }
    }
}
