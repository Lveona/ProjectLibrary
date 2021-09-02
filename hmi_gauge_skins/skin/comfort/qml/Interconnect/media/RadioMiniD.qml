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
        x:796
        y:663
        source: "mediaIcon/tab_radio_n_56x56.png"
    }

    CustomText {
        x:838
        y:668
        width: 40
        height: 23
        text:"FM"
        opacity: 0.4
    }

    CustomText {
        id:mediaFrequency
        x:931
        y:663
        height: 30
        font.pixelSize: 36
        font.family:trLanguge("font")
        text : {
            switch (mediaPlayState) {
                case MediaDataObjectEnums.PLAYING :
                    frequency;
                    break;
                case MediaDataObjectEnums.SEARCHING :
                    trLanguge("搜台中");
                    break;
                case MediaDataObjectEnums.SEEKING :
                    "...";
                    break;
                default:
                    "";
            }
        }
    }

    CustomText {
        visible: mediaPlayState !== MediaDataObjectEnums.SEARCHING
        width: 78
        height: 28
        text:"MHz"
        font.pixelSize: 36
        opacity: 0.5
        anchors.verticalCenter: mediaFrequency.verticalCenter
        anchors.left: mediaFrequency.right
        anchors.leftMargin: 21
    }
}
