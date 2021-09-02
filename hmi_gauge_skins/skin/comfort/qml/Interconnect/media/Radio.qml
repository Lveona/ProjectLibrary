import QtQuick 2.8
import "../../Common/"
import qmlEnums 1.0
Item {
    width: 1920
    height: 720
    //AM FM 无法区分
    CustomImage {
        x:1509
        y:180
        width: 186
        height: 186
        source:"icon_areaD_FM_cover_normal.png"
    }

    CustomText {
        id : radioFrequency
        y: 379
        x: 1523
        visible:  mediaPlayState !== MediaDataObjectEnums.SEARCHING
        width: 73
        height: 24
        font.pixelSize: 28
        text : mediaPlayState === MediaDataObjectEnums.PLAYING ?
                   frequency : "..." //意义不明确是上下切台吗
    }

    CustomText {
        //x:1621
        //y:380
        width: 61
        height: 22
        visible:  mediaPlayState !== MediaDataObjectEnums.SEARCHING
        font.pixelSize: 28
        text : "MHz";
        opacity: 0.5
        anchors.verticalCenter: radioFrequency.verticalCenter
        anchors.left: radioFrequency.right
        anchors.leftMargin: 25
    }

    CustomText {
        x:1548 //收音机搜台中
        y:378
        width : 108
        height: 28
        font.pixelSize: 28
        visible:  mediaPlayState === MediaDataObjectEnums.SEARCHING
        font.family:trLanguge("font")
        text: trLanguge("搜台中")
    }



    CustomImage {
        id: typeIcon
        x: 1552
        y: 420
        width: 30;
        height: 28;
        source:mediaTypeIcon
    }

    CustomText {
        //x: 1579
        //y: 425
        anchors.verticalCenter: typeIcon.verticalCenter
        anchors.left: typeIcon.right
        anchors.leftMargin: 2
        width: 61;
        height: 20;
        font.pixelSize: 20
        font.family:trLanguge("font")
        text: trLanguge("收音机") //  mediaType
        opacity: 0.3
    }
}
