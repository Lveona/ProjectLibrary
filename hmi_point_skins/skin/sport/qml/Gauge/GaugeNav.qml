import QtQuick 2.0
import qmlEnums 1.0
import "./../Common/"

Item {
    width: 1920
    height: 720

    CustomText {
        x:17
        y:583
        width:165
        height:52
        text:Math.floor(digitSpeedAnim)
        font.pixelSize: 70
    }

    CustomText {
        x:198
        y:614
        width: 94
        height: 24
        opacity: 0.6
        color: "#e3e3e3"
        text:"km/h"
        font.pixelSize: 30
    }

    CustomText {
        x:1616
        y:619
        width: 125
        height: 17
        opacity: 0.6
        color: "#e3e3e3"
        text:"PWR(%)"
        font.pixelSize: 24
    }

    CustomText {
        x:1736
        y:585
        width:167
        height:52
        text:Math.floor(powerAnim)
        font.pixelSize: 70
    }
}
