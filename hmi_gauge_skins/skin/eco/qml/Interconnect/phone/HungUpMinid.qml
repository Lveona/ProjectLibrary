import QtQuick 2.8
import "../../Common/"
import qmlEnums 1.0

Item {
    id : phoneMiniD
    width: 1920
    height: 36

    //蓝牙电话
    Item {
        anchors.centerIn: parent
        CustomImage {
            fillMode: Image.Stretch
            width: 54
            height: 29
            source: "icon_areaD_phone_red.png"
            anchors.right: phoneInfo.left
            anchors.rightMargin: 31
            anchors.top: phoneInfo.top
        }

        CustomText {
            id : phoneInfo
            anchors.centerIn: parent
            font.pixelSize: 36
            height: 34
            font.family:trLanguge("font")
            text : displayName + " - "+trLanguge("已挂断");
        }
    }
}
