import QtQuick 2.8
import "../../Common/"
import qmlEnums 1.0
Item {
    id : incoming // 来电中
    width: 1920
    height: 720

    Image{
        x:1560
        y:185
        width: 93
        height: 93
        source: "icon_areaD_phone_head.png"
        visible:  phoneMode === PhoneDataObjectEnums.ECALL ||
                  phoneMode === PhoneDataObjectEnums.BCALL ||
                  phoneMode === PhoneDataObjectEnums.CCALL
    }

    Image {
        x: 1570
        y: 199
        width: 70
        height: 70
        source: "icon_areaD_phone.png"
        visible:  phoneMode === PhoneDataObjectEnums.BTPHONE
    }

    CustomText {
        id:phoneStatus
        x: 1579
        y: 297
        width: 55
        height: 27
        font.family:trLanguge("font")
        text: trLanguge("来电")
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

//    CustomText {
//        x:1496
//        y:380
//        width: 227
//        height: 23
//        text: phoneNumber
//        font.pixelSize: 28
//    }



    CustomText {
        x: 1414
        y: 404
        width: 170;
        height: 26;
        font.pixelSize: 28
        font.family:trLanguge("font")
        text: trLanguge("长按接听")
    }

    Image {
        x: 1482
        y: 400
        width: 34
        height: 34
        source: "icon_areaD_phone_green_small.png";
    }

    CustomText{
        x:1629
        y:404
        width: 170
        height: 26
        font.family:trLanguge("font")
        text: trLanguge("短按挂断")
        font.pixelSize: 28
    }

    Image{
        x: 1697
        y: 400
        width: 34
        height: 34
        source: "icon_areaD_phone_red_small.png"
    }
}
