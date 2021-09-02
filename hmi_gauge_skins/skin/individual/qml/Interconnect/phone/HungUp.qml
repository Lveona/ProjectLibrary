import QtQuick 2.8
import "../../Common/"

Item {
    id : hungup //挂断
    width: 1920
    height: 720

    Image {
        x: 1554
        y: 226
        width: 102
        height: 45
        source: "icon_areaD_phone_red.png"
    }

    CustomText {
        id:phoneStatus
        x: 1566
        y: 297
        width: 81
        height: 27
        font.family:trLanguge("font")
        text: trLanguge("已挂断");
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

    CustomText {
        x: 1568
        y: 407
        width: 84;
        height: 27;
        font.pixelSize: 28
        font.family:trLanguge("font")
        text: trLanguge("短按挂断")
    }
}
