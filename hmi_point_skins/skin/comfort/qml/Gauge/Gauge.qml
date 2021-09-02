import QtQuick 2.8
//import QtQuick.Controls 1.4
import qmlEnums 1.0
import "./../Common/"

Item {
    id: gauge
    width: 1920
    height: 720
    visible: !Manager.isCharging

    property real powerMode: Manager.receiveCtrlPowerMode

    property real autoCheckState: GaugeScreen.autoCheckState
    property var digitSpeed: GaugeScreen.digitSpeedValue
    property real digitSpeedAnim: 0
    property real digitSpeedAnimTime: 0
    property real digitSpeedAnim_dial: 0
    property real digitSpeedAnimTime_dial: 0
    property real digitSpeed_dial: 0
    property real power: GaugeScreen.powerValue
    property real powerAnim: 0
    property real powerAnimTime: 0
    property string txtSpeed: "0"

    //仪表模式 0 常规 1 地图 其他待定
    property int meterMode: Manager.navigationMapMod

    //入场动效
    function gaugeAnim_start(){
        root.opacity = 1;
        handleEnterAnimOver();
        //停止出场动效
        normalLoader.item.powerDiaAnimEnd_Stop()
        normalLoader.item.speedDiaAnimEnd_Stop()
        normalLoader.item.numberAnimEnd_Stop()

        //入场动效
        normalLoader.item.speedDiaAnimStart();
        normalLoader.item.powerDiaAnimStart();
        normalLoader.item.numberAnimStart();
        telltalesEnterAnim();
    }

    //出场动效
    function gaugeAnim_end(){
        //停止入场动效
        normalLoader.item.speedDiaAnimStart_Stop()
        normalLoader.item.powerDiaAnimStart_Stop()
        normalLoader.item.numberAnimStart_Stop()

        //出场动效
        normalLoader.item.speedDiaAnimEnd();
        normalLoader.item.powerDiaAnimEnd();
        normalLoader.item.numberAnimEnd();
        telltalesOutAnim();
    }
    function naviIn(){
        navLoader.item.naviShow();
    }
    function naviOut(){
        navLoader.item.naviHide();
    }
    onPowerModeChanged: {
        if(powerMode === ManagerEnums.QML_POWERMODE_D1){
            if(normalLoader.item){
                console.log("------------", normalLoader.item)
                if(Manager.navigationMapMod ===  ManagerEnums.SMALL_MAP){
                    gaugeAnim_start()
                    //telltalesAnimEnter()
                }
            }
        }else if(powerMode === ManagerEnums.QML_POWERMODE_D2){
            console.log("===============", normalLoader.item)
//            gaugeAnim_end()
        }
    }

    onAutoCheckStateChanged: {
        // 自检开始
        if(autoCheckState === 1){
            beSpeedAnim.enabled = false;
            bePowerAnim.enabled = false;
            speedAutocheckAnim.restart()
            speedAutocheckAnim_dial.start()
            powerAutocheckAnim.restart()
        }else{
            if(speedAutocheckAnim.running){
                //打断
                speedAutocheckAnim_dial.complete()
                speedAutocheckAnim.complete()
            }
            if(powerAutocheckAnim.running){
                //打断
                powerAutocheckAnim.complete()
            }
        }
    }

    SequentialAnimation{
        id: speedAutocheckAnim
        PropertyAnimation{target: gauge; property: "digitSpeedAnim"; from: 0; to: 300; duration: 1500; easing.type: Easing.Linear;}
        PropertyAnimation{target: gauge; property: "digitSpeedAnim"; to: 0; duration: 1500; easing.type: Easing.Linear;}
        onStarted: {
            //txtSpeed.text = Qt.binding(function(){ return String(Math.floor(digitSpeedAnim+0.5))})
            txtSpeed = Qt.binding(function(){ return String(Math.floor(digitSpeedAnim+0.5))})
        }
        onStopped: {
            //复归
            beSpeedAnim.enabled  = true
            handleSpeed()
        }
    }

    SequentialAnimation{
        id: speedAutocheckAnim_dial
        PropertyAnimation{target: gauge; property: "digitSpeedAnim_dial"; from: 0; to: 240; duration: 1500; easing.type: Easing.Linear;}
        PropertyAnimation{target: gauge; property: "digitSpeedAnim_dial"; to: 0; duration: 1500; easing.type: Easing.Linear;}
        onStopped: {
            //复归
            beSpeedAnim_dial.enabled  = true
            handleSpeed_dial()
        }
    }

    SequentialAnimation{
        id: powerAutocheckAnim
        PropertyAnimation{target: gauge; property: "powerAnim"; from: 0; to: -100; duration: 500; easing.type: Easing.Linear;}
        PropertyAnimation{target: gauge; property: "powerAnim"; to: 0; duration: 500; easing.type: Easing.Linear;}
        PropertyAnimation{target: gauge; property: "powerAnim"; to: 100; duration: 500; easing.type: Easing.Linear;}
        PropertyAnimation{target: gauge; property: "powerAnim"; to: 0; duration: 500; easing.type: Easing.Linear;}
        onStarted: {
            //txtSpeed.text = Qt.binding(function(){ return String(Math.floor(digitSpeedAnim+0.5))})
            txtSpeed = Qt.binding(function(){ return String(Math.floor(digitSpeedAnim+0.5))})
        }

        onStopped: {
            bePowerAnim.enabled  = true
            gauge.powerAnim = Qt.binding(function() { return GaugeScreen.powerValue })
        }
    }

    onDigitSpeedChanged: {
        if(autoCheckState === 1){
            return
        }
        handleSpeed()
        handleSpeed_dial()
    }

    onPowerChanged: {
        if(autoCheckState === 1){
            return
        }
        handlePower()
    }

    function handleSpeed(){
        if(digitSpeed === "--"){
            //txtSpeed.text = "--"
            txtSpeed = "--"
            digitSpeedAnim = 0
        }
        else{
            //txtSpeed.text = Qt.binding(function(){ return String(Math.floor(digitSpeedAnim+0.5))})
            txtSpeed = Qt.binding(function(){ return String(Math.floor(digitSpeedAnim+0.5))})
            digitSpeedAnimTime = Math.abs(Number(digitSpeed) - Number(digitSpeedAnim)) / 300 * 1000
            digitSpeedAnim = Number(digitSpeed)
        }
    }

    function handleSpeed_dial(){
        if(digitSpeed === "--"){
            digitSpeedAnim_dial = 0
        }
        else{
            digitSpeed_dial = digitSpeed > 240 ? 240 : digitSpeed;
            digitSpeedAnimTime_dial = Math.abs(Number(digitSpeed_dial) - Number(digitSpeedAnim_dial)) / 240 * 1000
            digitSpeedAnim_dial = Number(digitSpeed_dial)
        }
    }

    function handlePower(){
        powerAnimTime = Math.abs(Number(power) - Number(powerAnim)) / 200 * 2000
        powerAnim = Number(power)
    }

    Behavior on digitSpeedAnim {
        id: beSpeedAnim
        NumberAnimation { duration: digitSpeedAnimTime; easing.type: Easing.Linear; }
    }
    Behavior on digitSpeedAnim_dial {
        id: beSpeedAnim_dial
        NumberAnimation { duration: digitSpeedAnimTime_dial; easing.type: Easing.Linear; }
    }
    Behavior on powerAnim {
        id: bePowerAnim
        NumberAnimation { duration: powerAnimTime; easing.type: Easing.Linear; }
    }

    Loader {
        id :normalLoader
        //visible: meterMode === ManagerEnums.SMALL_MAP
        //active: meterMode === ManagerEnums.SMALL_MAP
        visible: pointNaiVisible
        anchors.fill: parent
        source: "GaugeNormal.qml"
        onLoaded: {
            active = true
        }
    }

    Loader {
        id :navLoader
        //visible: meterMode !== ManagerEnums.SMALL_MAP
        //active: meterMode !== ManagerEnums.SMALL_MAP
        visible: !pointNaiVisible
        source: "GaugeNav.qml"
        onLoaded: {
            active = true
        }
    }
}
