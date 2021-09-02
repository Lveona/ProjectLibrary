import QtQuick 2.8
import "../../Common/"

Item {
    id : dialing //拨号中
    width: 1920
    height: 720

    Image {
        x: 1570
        y: 199
        width: 70
        height: 70
        source: "icon_areaD_phone.png"
    }

    CustomText {
        id:phoneStatus
        x: 1564
        y: 297
        width: 81
        height: 27
        font.family:trLanguge("font")
        text: trLanguge("拨号中")
        font.pixelSize: 28
        opacity: 0.3
    }

    CustomText {
        x:1548
        y:343
        width: 123
        height: 24
        font.family:trLanguge("font")
        text: displayName
        font.pixelSize: 28

    }

    Image {
        x: 1522
        y: 409
        width: 44
        height: 23
        source: "icon_areaD_phone_red.png";
    }

    CustomText {
        x: 1577
        y: 405
        width: 115;
        height: 26;
        font.pixelSize: 28
        font.family:trLanguge("font")
        text: trLanguge("短按挂断")
        opacity: 0.3

    }
}
