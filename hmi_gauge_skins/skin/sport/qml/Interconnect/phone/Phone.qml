import QtQuick 2.8
import "../../Common/"
import qmlEnums 1.0

Item {
    id : phone
    width: 1920
    height: 720

    //盖背景
//    Rectangle {
//        id : phonebg
//        x:1431
//        y:172
//        width: 400
//        height: 300
//        color: "black"
//        opacity: dialingLoader.visible ||
//                 incomingLoader.visible ||
//                 activeLoader.visible ? 1 :
//                hungUpLoader.opacity === 0 ? 0 : 1
//    }

    //9 QML 蓝牙电话

    //通话模式 BTPHONE ECALL BCALL CCALL
    property int phoneMode: InterconnectScreen.phoneDataObject.phoneMode //通话模式 蓝牙 or TBOXC TBOXB .......
    //通话状态
    property int phoneStatus: InterconnectScreen.phoneDataObject.phoneStatus //通话状态 通话中 or 拨号中 。。。。
    //联系人或电话号码
    property string displayName: InterconnectScreen.phoneDataObject.displayName;

    //电话号码   因新版UI不确定暂定
    //property string phoneNumber: InterconnectScreen.phoneDataObject.phoneNumber
    //通话时间
    property string elapseTime: InterconnectScreen.phoneDataObject.elapseTime
    //头像
    property string headImage : InterconnectScreen.phoneDataObject.headImage
    //电话挂断消失时间
    property int hungUpLoaderAnimationTime : 2000

    //电话是否 小地图在巡航状态下才有电话
    property bool bigPhoneLoaderActive: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
                                    && navigationMapMod === InterconnectScreenEnums.SMALL_MAP


    property bool minidPhoneLoaderActive: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
                                    && navigationMapMod !== InterconnectScreenEnums.SMALL_MAP

    Item {
        //小地图模式
        width: 1920
        height: 720
        visible: bigPhoneLoaderActive

        Loader{
            id: dialingLoader //拨号中
            active: bigPhoneLoaderActive
            source: "Dialing.qml"
            visible: phoneStatus === PhoneDataObjectEnums.DIALING
            onLoaded: {
                active = true
            }
        }

        Loader{
            id: incomingLoader //来电中
            active: bigPhoneLoaderActive
            source: "Incoming.qml"
            visible: phoneStatus === PhoneDataObjectEnums.INCOMING
            onLoaded: {
                active = true
            }
        }

        Loader{
            id: activeLoader //通话中
            active: bigPhoneLoaderActive
            source: "Active.qml"
            visible: phoneStatus === PhoneDataObjectEnums.ACTIVE
            onLoaded: {
                active = true
            }
        }

        Loader{
            id: hungUpLoader //挂断
            active: bigPhoneLoaderActive
            source: "HungUp.qml"
            visible: phoneStatus === PhoneDataObjectEnums.HUNG_UP
            onLoaded: {
                active = true
            }

            opacity: 1
            //挂断界面2S后消失
            onVisibleChanged:{
                if( hungUpLoader.visible == true) {
                    opacity = 1;
                    hungUpLoaderAnimation.restart();
                } else {
                    //防止在动画中被切换了状态 造成界面闪烁
                    hungUpLoaderAnimation.stop();
                }
            }
            NumberAnimation on opacity {
                running: false
                id : hungUpLoaderAnimation
                to : 0
                onStopped: {
                    hungUpLoader.opacity = 0;
                    InterconnectScreen.phoneDataObject.phoneMode = PhoneDataObjectEnums.NONE
                }
                duration : hungUpLoaderAnimationTime
            }
        }

    }

    //MiniD电话
    Item{
        visible: minidPhoneLoaderActive
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 61 //25底部距离 +36自己的高度

        Loader{
            id: dialingLoaderMinid //拨号中
            active: minidPhoneLoaderActive
            source: "DialingMinid.qml"
            visible: phoneStatus === PhoneDataObjectEnums.DIALING
            onLoaded: {
                active = true
            }
        }

        Loader{
            id: incomingLoaderMinid //来电中
            active: minidPhoneLoaderActive
            source: "IncomingMinid.qml"
            visible: phoneStatus === PhoneDataObjectEnums.INCOMING
            onLoaded: {
                active = true
            }
        }

        Loader{
            id: activeLoaderMiniD //通话中
            active: minidPhoneLoaderActive
            source: "ActiveMiniD.qml"
            visible: phoneStatus === PhoneDataObjectEnums.ACTIVE
            onLoaded: {
                active = true
            }
        }

        Loader{
            id: hungUpLoaderMinid //挂断
            active: minidPhoneLoaderActive
            source: "HungUpMinid.qml"
            visible: phoneStatus === PhoneDataObjectEnums.HUNG_UP
            onLoaded: {
                active = true
            }

            opacity: 1
            //挂断界面2S后消失
            onVisibleChanged:{
                if( hungUpLoaderMinid.visible == true) {
                    opacity = 1;
                    hungUpLoaderAnimationMinid.restart();
                } else {
                    //防止在动画中被切换了状态 造成界面闪烁
                    hungUpLoaderAnimationMinid.stop();
                }
            }
            NumberAnimation on opacity {
                running: false
                id : hungUpLoaderAnimationMinid
                to : 0
                onStopped: {
                    hungUpLoaderMinid.opacity = 0;
                    InterconnectScreen.phoneDataObject.phoneMode = PhoneDataObjectEnums.NONE
                }
                duration : hungUpLoaderAnimationTime
            }
        }
    }
}
