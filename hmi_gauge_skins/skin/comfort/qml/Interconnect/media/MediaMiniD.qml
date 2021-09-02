import QtQuick 2.8
import "../../Common/"
import qmlEnums 1.0

Item {
    id : radioMiniD
    width: 1920
    height: 720

    CustomImage{
        width: 30
        height: 28
//        x:739
//        y:665
        source: "icon_areaD_TBT_music.png"

        anchors.verticalCenter: mediaInfoMinid.verticalCenter
        anchors.right: mediaInfoMinid.left
        anchors.rightMargin: 22
    }

    CustomAutoScollText {
        id:mediaInfoMinid
        x:791
        y:661
        width: 391
        height: 35
        txtInfo.text : mediaPlayState === MediaDataObjectEnums.PLAYERROR ?  errorString :  mediaTitle + "-" + mediaArtist
        txtInfo.font.pixelSize: 36
    }

    CustomImage {
        id:music_loading_small
        anchors.verticalCenter: mediaInfoMinid.verticalCenter
        anchors.left: mediaInfoMinid.right
        anchors.leftMargin: 17
        source: "Icon_miniD_loading.png"
        visible: mediaPlayState == MediaDataObjectEnums.STREAMING_LOADING
        NumberAnimation {
            running: music_loading_small.visible
            loops: Animation.Infinite
            target: music_loading_small
            from: 0
            to: 360
            property: "rotation"
            duration: 1000
        }
    }
}
