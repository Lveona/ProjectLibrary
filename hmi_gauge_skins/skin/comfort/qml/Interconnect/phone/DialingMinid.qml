import QtQuick 2.8
import "../../Common/"
import qmlEnums 1.0

Item {
    id : phoneMiniD
    width: 1920
    height: 36

    Item { //拨号中
        anchors.centerIn: parent

        CustomImage {
            fillMode: Image.Stretch
            width: 34
            height: 34
            source: "icon_areaD_phone_green.png"
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
            text : trLangugeDayDisPop("正在拨号给 XXX",displayName);
        }
    }
}
