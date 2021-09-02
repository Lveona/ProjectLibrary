import QtQuick 2.8
import "../../Common/"
import qmlEnums 1.0

Item {
    id : phoneMiniD
    width: 1920
    height: 36

    //10 QML 小电话

    //通话模式
    //property int phoneMode: InterconnectScreen.phoneDataObject.phoneMode //通话模式 蓝牙 or TBOXC TBOXB .......
    //通话状态
    //property int phoneStatus: InterconnectScreen.phoneDataObject.phoneStatus //通话状态 通话中 or 拨号中 。。。。
    //联系人或电话号码
    //property string displayName: InterconnectScreen.phoneDataObject.displayName;
    //通话时间
    //property string elapseTime: InterconnectScreen.phoneDataObject.elapseTime


    //蓝牙电话
    Item {
        visible: InterconnectScreen.phoneDataObject.phoneMode !== PhoneDataObjectEnums.NONE
        anchors.centerIn: parent
        CustomImage {
            id : activeImage //通话中
            fillMode: Image.Stretch
            width: 34
            height: 34
            source: "icon_areaD_phone_green.png"
            anchors.right: phoneInfo.left
            anchors.rightMargin: 31
            anchors.top: phoneInfo.top
            visible: phoneStatus === PhoneDataObjectEnums.ACTIVE
        }

        CustomImage {
            id : incomingImage //来电中 拨号中
            fillMode: Image.Stretch
            width: 34
            height: 34
            source: "icon_areaD_phone_green.png"
            anchors.right: phoneInfo.left
            anchors.rightMargin: 31
            anchors.top: phoneInfo.top
            visible: phoneStatus === PhoneDataObjectEnums.DIALING ||
                     phoneStatus === PhoneDataObjectEnums.INCOMING
        }

        CustomImage {
            id: hungUpIamge //已挂断
            fillMode: Image.Stretch
            width: 54
            height: 29
            source: "icon_areaD_phone_red.png"
            anchors.right: phoneInfo.left
            anchors.rightMargin: 31
            anchors.top: phoneInfo.top
            visible: phoneStatus === PhoneDataObjectEnums.HUNG_UP
        }

        CustomText {
            id : phoneInfo
            anchors.centerIn: parent
            font.pixelSize: 36
            height: 34
            //text: "正在拨号给12 - 王小明"
            text : {
                switch(phoneStatus) {
                case PhoneDataObjectEnums.DIALING:
                    return "正在拨号给 - " + displayName;
                case PhoneDataObjectEnums.INCOMING: //来电中
                    return displayName + " - 来电中";
                case PhoneDataObjectEnums.ACTIVE: //通话中
                    return displayName + " - " + elapseTime ;
                case PhoneDataObjectEnums.HUNG_UP: //挂断
                    return displayName + " - 已挂断";
                default:
                    return "";
                }
            }
        }
    }
}
