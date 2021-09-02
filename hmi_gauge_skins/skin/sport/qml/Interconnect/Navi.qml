import QtQuick 2.8
import "../Common/"
import qmlEnums 1.0
Item {
    id: navi
    width: 1920
    height: 720

    property int mediaPlayState: InterconnectScreen.mediaDataObject.playState;

    //D
    CustomImage {
        id: nav_loading_small_bg
        x:1370
        y:176
        width: 466
        height: 341
        opacity: 0.1
        source: "Navi/NAV_D_LOADING_BG.png"
        visible: navigationMapMod === InterconnectScreenEnums.SMALL_MAP
                 && (navigationStatus === InterconnectScreenEnums.CRUISE_STATE ?
                 mediaPlayState !== MediaDataObjectEnums.PLAYING
                 && mediaPlayState !== MediaDataObjectEnums.PAUSE ? true : false :true)
    }

    CustomImage {
        id:nav_loading_small
        x:1581
        y:296
        width: 44
        height: 44
        source: "Navi/Nav_loading_small.png"
        visible: nav_loading_small_bg.visible
        NumberAnimation {
            running: nav_loading_small.visible
            loops: Animation.Infinite
            target: nav_loading_small
            from: 0
            to: 360
            property: "rotation"
            duration: 1000
        }
    }

    //地图模式 加载中
    CustomImage {
        id:nav_loading_bg
        source: "Navi/NAV_LOADING_BG.png"
        visible: navigationMapMod !== InterconnectScreenEnums.SMALL_MAP
                 && navigationProjection === InterconnectScreenEnums.NAVI_NO_READY
    }
//    CustomImage {
//        id:mask_top
//        source: "Navi/mask_top.png"
//        visible: navigationMapMod !== InterconnectScreenEnums.SMALL_MAP
//                 && navigationProjection === InterconnectScreenEnums.NAVI_NO_READY
//    }
    CustomImage {
        id:nav_loading
        x:914
        y:310
        width: 92
        height: 92
        source: "Navi/Nav_loading.png"
        visible: nav_loading_bg.visible
        NumberAnimation {
            running: nav_loading.visible
            loops: Animation.Infinite
            target: nav_loading
            from: 0
            to: 360
            property: "rotation"
            duration: 1000
        }
    }

    //地图模式 加载完成

}
