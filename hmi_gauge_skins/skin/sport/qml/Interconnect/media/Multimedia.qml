import QtQuick 2.8
import "../../Common/"
import qmlEnums 1.0
Item {
    id: media
    width: 1920
    height: 720

    property int mediaMode: 0
    property int mediaVisibleState: InterconnectScreen.mediaDataObject.mediaVisibleState;
    property int mediaPlayState: InterconnectScreen.mediaDataObject.playState;

    property string mediaCover: InterconnectScreen.mediaDataObject.imageUri//"icon_areaD_music_cover_normal.png";
    property string mediaTitle: InterconnectScreen.mediaDataObject.title;
    property string mediaArtist: InterconnectScreen.mediaDataObject.artist;
    property string mediaType: titleStringSource[InterconnectScreen.mediaDataObject.sourceType];
    property string mediaTypeIcon: titleIconSource[InterconnectScreen.mediaDataObject.sourceType];
    property string errorString: InterconnectScreen.mediaDataObject.errorString;
    property string frequency: InterconnectScreen.mediaDataObject.frequency;
    //6 媒体 QML
    property var titleStringSource: [
        //文言
        "",trLanguge("USB音频"),trLanguge("蓝牙音乐"),"FM"+trLanguge("收音机"),"AM"+trLanguge("收音机"),
         trLanguge("AI电台"),trLanguge("QQ音乐"),trLanguge("喜马拉雅听书"),trLanguge("喜马拉雅广播"),trLanguge("新闻资讯")
    ]

    property var titleIconSource: [
        "",
        "mediaIcon/tab_USB_n_56x56.png",
        "mediaIcon/tab_bluetooth_music_n_56x56.png",
        "mediaIcon/tab_radio_n_56x56.png",
        "mediaIcon/tab_radio_n_56x56.png",
        "mediaIcon/tab_AI radio_station_n_56x56.png",
        "mediaIcon/tab_QQmusic_n_56x56.png",
        "mediaIcon/tab_audiobook_n_56x56.png",
        "mediaIcon/tab_audiobook_n_56x56.png",//缺
        "mediaIcon/tab_news_n_56x56.png"
    ]

    Component.onCompleted: {
    }

    //    enum qmlMediaPlayState {
    //        PLAYING = 0,//播放中 收音机收音中
    //        PAUSE, //暂停
    //        STOPPED,//停止
    //        SEARCHING,//收音机搜台中
    //        SEEKING, //  收音机上下切台
    //        STREAMING_LOADING,//流媒体加载中
    //        STREAMING_LOADED,//流媒体加载完毕
    //        PLAYERROR //错误   收音机没有
    //    };


//    //显示状态设置
//    property string mediaVisibleState: InterconnectScreen.mediaDataObject.mediaVisibleState;
//    //标题的ICon地址
//    property string sourceIcon: InterconnectScreen.mediaDataObject.sourceIcon;
//    //标题名
//    property string sourceTitle: InterconnectScreen.mediaDataObject.sourceTitle;
//    //歌名项目名称
//    property string title: InterconnectScreen.mediaDataObject.title;
//    //作者歌手名
//    property string artist: InterconnectScreen.mediaDataObject.artist;
//    //播放状态
//    property string playState: InterconnectScreen.mediaDataObject.playState;
//     //封面
//    property string imageUri: InterconnectScreen.mediaDataObject.imageUri;


    //不在 路口放大图 不在 导航状态 多媒体才显示 且巡航状态下 多媒体要播放或 暂停才可以
    property bool bigDMultimediaVisible:  navigationMapMod === InterconnectScreenEnums.SMALL_MAP
                                    && navigationStatus !== InterconnectScreenEnums.NAVIGATION_STATE
                                    && navigationStatus !== InterconnectScreenEnums.ROAD_CROSSING_ENLARGED_STATE
                                    && (navigationStatus === InterconnectScreenEnums.CRUISE_STATE
                                    ? mediaPlayState === MediaDataObjectEnums.PLAYING
                                    || mediaPlayState === MediaDataObjectEnums.PAUSE
                                    ? true : false : true)

    Loader{
        active: bigDMultimediaVisible && mediaVisibleState === MediaDataObjectEnums.RADIOSHOW

        source: "Radio.qml"
        visible: bigDMultimediaVisible && mediaVisibleState === MediaDataObjectEnums.RADIOSHOW
        onLoaded:{
            active = true;
        }
    }

    Loader{
        active: navigationMapMod !== InterconnectScreenEnums.SMALL_MAP &&
                mediaVisibleState === MediaDataObjectEnums.RADIOSHOW
        source: "RadioMiniD.qml"
        visible: navigationMapMod !== InterconnectScreenEnums.SMALL_MAP &&
                 mediaVisibleState === MediaDataObjectEnums.RADIOSHOW
        onLoaded:{
            active = true;
        }
    }

    Loader{
        active: bigDMultimediaVisible && mediaVisibleState === MediaDataObjectEnums.MEDIASHOW
        source: "Media.qml"
        visible: bigDMultimediaVisible && mediaVisibleState === MediaDataObjectEnums.MEDIASHOW

        onLoaded:{
            active = true;
        }
    }

    Loader{
        active: navigationMapMod !== InterconnectScreenEnums.SMALL_MAP &&
                mediaVisibleState === MediaDataObjectEnums.MEDIASHOW
        source: "MediaMiniD.qml"
        visible: navigationMapMod !== InterconnectScreenEnums.SMALL_MAP &&
                 mediaVisibleState === MediaDataObjectEnums.MEDIASHOW
        onLoaded:{
            active = true;
        }
    }

}
