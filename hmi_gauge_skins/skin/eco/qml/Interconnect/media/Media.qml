import QtQuick 2.8
import "../../Common/"
import qmlEnums 1.0
Item {
    id: media
    width: 1920
    height: 720

    CustomImage {
        x : 1509
        y : 180
        width: 182
        height: width
        fillMode: Image.Stretch
        source: mediaCover//"icon_areaD_music_cover1.png"
        CustomImage { //暂停
            visible: mediaPlayState === MediaDataObjectEnums.PAUSE
            anchors.centerIn: parent
            source:"icon_areaD_music_pause.png"
        }

        CustomImage { //流媒体加载中
            id:music_loading
            visible: mediaPlayState === MediaDataObjectEnums.STREAMING_LOADING
            anchors.centerIn: parent
            source:"icon_areaD_music_loading.png"

            NumberAnimation {
                running: music_loading.visible
                loops: Animation.Infinite
                target: music_loading
                from: 0
                to: 360
                property: "rotation"
                duration: 1000
            }
        }
    }

    CustomAutoScollText{
        x: 1486
        y: 379
        width: 226;
        height: 29;
        txtInfo.font.pixelSize: 28
        txtInfo.text: mediaPlayState === MediaDataObjectEnums.PLAYERROR ?  errorString :  mediaTitle + "-" + mediaArtist
        animScroll.paused: mediaPlayState === MediaDataObjectEnums.PAUSE
    }

    CustomImage {
        id: typeIcon
        x: 1542
        y: 425
        width: 26;
        height: 24;
        source:mediaTypeIcon
    }

    CustomText {
        //x: 1579
        //y: 425
        anchors.verticalCenter: typeIcon.verticalCenter
        anchors.left: typeIcon.right
        anchors.leftMargin: 2
        height: 22;
        font.pixelSize: 20
        text:mediaType
        opacity: 0.3
    }
}
