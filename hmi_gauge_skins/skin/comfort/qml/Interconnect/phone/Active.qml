import QtQuick 2.8
import "../../Common/"

Item {
    id : active //通话中
    width: 1920
    height: 720

    Image {
        x: 1566
        y: 199
        width: 78
        height: 78
        source: "icon_areaD_phone_green.png"
    }

    CustomText {
        x: 1572
        y: 299
        width: 75
        height: 23
        text: elapseTime
        font.pixelSize: 28
        opacity: 0.3
    }

    CustomText {
        x:1546
        y:341
        width: 123
        height: 24
        font.family:trLanguge("font")
        text: displayName
        font.pixelSize: 28
    }

    Image {
        x: 1615
        y: 401
        width: 34
        height: 34
        source: "icon_areaD_phone_red_small.png";
    }

    CustomText {
        x: 1577
        y: 405
        width: 115;
        height: 26;
        font.pixelSize: 28
        font.family:trLanguge("font")
        text: trLanguge("短按    挂断")
    }
}
