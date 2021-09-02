import QtQuick 2.8
import "../Common/"
import qmlEnums 1.0
import "./phone"
Item {
    id: interconnect
    width: 1920
    height: 720
    visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1

    //3 导航互联 QML
    property int navigationMapMod: InterconnectScreen.navigationMapMod //地图模式
    //CRUISE_STATE 巡航状态 NAVIGATION_STATE 导航状态 ROAD_CROSSING_ENLARGED_STATE 路口放大图
    property int navigationStatus: InterconnectScreen.navigationStatus //小地图下模式
    property int navigationProjection: InterconnectScreen.navigationProjection //导航 Ready
    property var doorWarning   : HomeScreen.doorWarning   //车门报警

    Component.onCompleted: {
    }

    Loader{
        active: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
        source: "Navi.qml"
        visible: (InterconnectScreen.phoneDataObject.phoneMode === PhoneDataObjectEnums.NONE)&&navigationProjection === InterconnectScreenEnums.NAVI_NO_READY&&!doorWarning
        onLoaded: {
            active = true
        }
    }

    Loader{
        id: mediaLoader
        active: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
        source: "media/Multimedia.qml"
        visible: (InterconnectScreen.phoneDataObject.phoneMode === PhoneDataObjectEnums.NONE)&&!doorWarning
        onLoaded: {
            active = true
        }
    }

    //电话优先级高于媒体待处理
    Loader{
        id: phoneLoader
        active: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
        source: "phone/Phone.qml"
        visible: (InterconnectScreen.phoneDataObject.phoneMode !== PhoneDataObjectEnums.NONE)&&!doorWarning
        onLoaded: {
            active = true
        }
    }
}
