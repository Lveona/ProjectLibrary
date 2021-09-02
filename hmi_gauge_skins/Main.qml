import QtQuick 2.8
//import QtQuick.Controls 1.0
import qmlEnums 1.0

import QtQuick3D 1.15
import QtQuick3D.Materials 1.15
import CacheSetter 1.0
import "./"

Item {
    id: rootMain
    visible: Manager.hmiScreenState
    width: 1920
    height: 720

    property int _HDKEY_DOWN: 0x20
    property int _HDKEY_UP:0x21
    property int _HDKEY_RIGHT:0x22
    property int _HDKEY_LEFT:0x23
    property int _HDKEY_OK:0x24
    property int _HDKEY_RETURN:5

    property int _KEY_ON: 0
    property int _KEY_OFF: 1
    property int _KEY_OUT: 2
    property int _KEY_OUT_OFF: 3

    //scene3D透明度
    property real scene3DOpacity: 0.0
    property bool scene3DVisible: false

    //判断D1，D2模式
    property bool panduanD1D2: false

    focus: true
    Keys.enabled: true
    Keys.onPressed: {
        if(event.key === Qt.Key_Up)
            Manager.key_pressed_released(_HDKEY_UP, _KEY_OFF)
        if(event.key === Qt.Key_Down)
            Manager.key_pressed_released(_HDKEY_DOWN, _KEY_OFF)
        if(event.key === Qt.Key_Left)
            Manager.key_pressed_released(_HDKEY_UP, _KEY_OUT_OFF)
        if(event.key === Qt.Key_Right)
            Manager.key_pressed_released(_HDKEY_DOWN, _KEY_OUT_OFF)
    }
    Keys.onReleased: {
        if(event.key === Qt.Key_1)
            Manager.key_pressed_released(_HDKEY_UP, _KEY_OUT_OFF)
        if(event.key === Qt.Key_2)
            Manager.key_pressed_released(_HDKEY_DOWN, _KEY_OUT_OFF)
    }

    property int navigationMapMod: InterconnectScreen.navigationMapMod //地图模式
    property var chargeConn: HomeScreen.chargeConn//chargeConnect
    property int isPowerMode: Manager.receiveCtrlPowerMode
    property int themeSetting: SettingScreen.themeSetting

    property bool adas3dVisible: {
        //navigationMapMod !== InterconnectScreenEnums.SMALL_MAP || chargeConn || isPowerMode !== ManagerEnums.QML_POWERMODE_D1 || themeSetting ===  SettingScreenEnums.SPORT
        (navigationMapMod !== InterconnectScreenEnums.SMALL_MAP)|| chargeConn || panduanD1D2 || (themeSetting ===  SettingScreenEnums.SPORT)
    }
    Rectangle {
        id: all_modelsItem
        z: 1
        width: parent.width
        height: parent.height
        color: "transparent"
        opacity: scene3DOpacity
        visible: !adas3dVisible

        Scene3D{
            id: all_models
            width:parent.width
            height:parent.height
            anchors.top: parent.top
            anchors.left: parent.left
        }
    }

    //3D入场动效
    SequentialAnimation{
        id: scene3DAllAnim_Srart
        NumberAnimation{ target: rootMain; duration: 1000; properties: "scene3DOpacity"; from: 0.0; to: 1.0}
        onStopped:{
            loader.item.handleEnterAnimOver() //入场最后动效
        }
    }

    //3D出场动效
    SequentialAnimation{
        id: scene3DAllAnim_End
        NumberAnimation{ target: rootMain; duration: 1000; properties: "scene3DOpacity"; from: 1.0; to: 0.0}
        onStarted: {
            if(loader.item.isThemeSetting){
                Manager.enterAnimStart = false;
            }
        }
        onStopped: {
            panduanD1D2 = true
        }
    }

    //3D入场动效
    function scene3DAllAnimStart(){
        panduanD1D2 = false
        scene3DAllAnim_Srart.start()
    }

    //3D入场动效停止
    function scene3DAllAnimStart_Stop(){
        scene3DAllAnim_Srart.complete()
    }

    //3D出场动效
    function scene3DAllAnimEnd(){
        panduanD1D2 = true
        scene3DAllAnim_End.start()
    }

    //3D出场动效停止
    function scene3DAllAnimEnd_Stop(){
        scene3DAllAnim_End.complete()
    }

    /***************************************************************加载字体***************************************************************/
    Timer{
        interval: 20
        running: true
        onTriggered: {
            console.log("gauge start load font")
            fontloaderCn.source = fontPath + "FZLanTingHeiS-R-GB.ttf"

        }
    }

    //不能合并
    //因为 themeBackIndex 是记忆状态  outAnimationState 是在动画结束时控制切换RCC的
    //如果在动画结束的时候记忆状态 那么在出场动画中 改变了出场动画索引
    property bool outAnimationState: false
    onOutAnimationStateChanged:{
        if(outAnimationState) {
            //SkinManager.changeskin(SettingScreen.themeSetting)
            SkinManager.changeskin(themeBackIndex)
        }
    }

    //全局变量用于 在进行主题动画时发生主题切换时不打断当前动画
    property bool themeAnimationRunning: false
    //全局变量用于 在进行主题动画时发生主题切换时 记忆当前要切换的主题坐标
    property int themeBackIndex: SettingScreenEnums.NONE

    //10 初始主题因初始主题可能不是有效的索引
    property int initThemeSetting: SettingScreen.themeSetting
    onInitThemeSettingChanged:{
        if(initThemeSetting > SettingScreenEnums.NONE &&
                initThemeSetting < SettingScreenEnums.MAXTHEM) {
            themeAnimationRunning = true;
            SkinManager.changeskin(initThemeSetting);
        }
    }

    Component.onCompleted: {
    }

    FontLoader{
        id: fontloaderCn
        onStatusChanged: {
            if(FontLoader.Ready == status){
                console.log("gauge finish load font CN")
                fontloaderEn.source = fontPath + "Eurostile_LT_Extended.ttf"
            }
        }
    }

    FontLoader{
        id: fontloaderEn
        onStatusChanged: {
            if(FontLoader.Ready == status){
                console.log("gauge finish load font EN")
                loader.source = Qt.binding(function(){ return SkinManager.currentSkin})
            }
        }
    }
    /***************************************************************************************************************************************/

    Loader{
        id: loader
        //source: SkinManager.currentSkin
        onLoaded: {
            console.log("gauge load rcc sucess.")
            //第一次加载后就不在执行了
            if(initThemeSetting === -99) {

            } else {
                initThemeSetting = -99;
                Manager.notify_cluster_manager("start");    //init
            }
        }
    }
}
