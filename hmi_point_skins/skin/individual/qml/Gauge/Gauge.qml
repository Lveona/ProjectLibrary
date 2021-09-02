import QtQuick 2.8
//import QtQuick.Controls 1.4
import qmlEnums 1.0
import "./../Common/"

Item {
    id: gauge
    width: 1920
    height: 720
    visible: !Manager.isCharging

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
            digitSpeedAnimTime = Math.abs(Number(digitSpeed) - Number(digitSpeedAnim)) / 300 * 2000
            digitSpeedAnim = Number(digitSpeed)
        }
    }

    function handleSpeed_dial(){
        if(digitSpeed === "--"){
            digitSpeedAnim_dial = 0
        }
        else{
            digitSpeed_dial = digitSpeed > 240 ? 240 : digitSpeed;
            digitSpeedAnimTime_dial = Math.abs(Number(digitSpeed_dial) - Number(digitSpeedAnim_dial)) / 240 * 2000
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
        visible: meterMode === ManagerEnums.SMALL_MAP
        active: meterMode === ManagerEnums.SMALL_MAP
        anchors.fill: parent
        source: "GaugeNormal.qml"
        onLoaded: {
            active = true
        }
    }

    Loader {
        id :navLoader
        visible: meterMode !== ManagerEnums.SMALL_MAP
        active: meterMode !== ManagerEnums.SMALL_MAP
        source: "GaugeNav.qml"
        onLoaded: {
            active = true
        }
    }




//    Loader {
//        id: speedMiddleLoader
//        visible: meterMode == 0
//        active: meterMode == 0
//        sourceComponent: speedMiddleCom
//        anchors.fill: parent
//        onLoaded: {
//            active = true
//        }
//    }

//    Component {
//        id : speedMiddleCom
//        Item{
//            anchors.fill: parent
//            //visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
//            //车速
//            CustomText{
//                //id: txtSpeed
//                y: 139
//                anchors.horizontalCenter: parent.horizontalCenter
//                font.pixelSize: 110
//                color: "#bbb39c"
//                visible: txtSpeed === "--"//txtSpeed.text === "--"
//                text: txtSpeed//"0"

//            }
//            Row{
//                id: numRow
//                visible: txtSpeed !== "--"//txtSpeed.text !== "--"
//                spacing: 10
//                anchors.top: parent.top
//                anchors.margins: 153
//                anchors.horizontalCenter: parent.horizontalCenter
//                //百位
//                Image{
//                    visible: digitSpeedAnim >= 100
//                    source: Math.floor(digitSpeedAnim / 100) + ".png"
//                }
//                //十位
//                Image{
//                    visible: digitSpeedAnim >= 10
//                    source: Math.floor(digitSpeedAnim / 10 % 10) + ".png"
//                }
//                //个位
//                Image{
//                    source: Math.floor(digitSpeedAnim % 10) + ".png"
//                }
//            }

//            CustomText{
//                anchors.horizontalCenter: parent.horizontalCenter
//                y: 251
//                font.pixelSize: 40
//                text: "km/h"
//                color: "#E3E3E3"
//            }
//        }
//    }

///**************************************************************************************************************************/
//    Loader{
//        id: speedDialLoader
//        sourceComponent: speedDialCom
//        active: meterMode == 0
//        visible: meterMode == 0
//        onLoaded: {
//            active = true
//        }
//    }

//    Component{
//        id: speedDialCom
//        Item{
//            id: speedDialItem
//            width: 1920
//            height: 720
//            Image { // 车速底图
//                id: speedBg
//                anchors.left: speedDialItem.left
//                anchors.leftMargin: 3
//                anchors.top: speedDialItem.top
//                anchors.topMargin: 471
//                source: ("pic_HMI_classic_default_speeddial_base.png");
//                Image{
//                    x: 64
//                    y: 17
//                    source: "pic_HMI_classic_default_speeddial_number.png"
//                }
//            }
//            //圆心
//            property real speed_centerX: 824
//            property real speed_centerY: 180
//            property real speed_radius: 876
//            property real start_Angle: 107.5

//            //偏移： -73 -603
//            CustomShape{
//                id: speedShape
//                center_x: speed_centerX
//                center_y: speed_centerY
//                width: speed_radius * 2
//                height: width
//                radius: speed_radius
//                headlightY: 479
//                headlightX: 33
//                startAngle: start_Angle
//                curAngle:  digitSpeedAnim_dial < 40 ? 0.563 * digitSpeedAnim_dial : 8.46 * Math.log(digitSpeedAnim_dial - 24.69) - 0.42  //digitSpeedAnim > 120 ? (partB_Angle / 120 * (digitSpeedAnim - 120) + partA_Angle) : (partA_Angle / 120 * digitSpeedAnim)
//                headlightSrc: "qrc:/skin1/qml/Gauge/pic_HMI_classic_default_speeddial_highlight.png"
//            }

//            CustomPointer{
//                radius: 1000
//                center_x: speed_centerX
//                center_y: speed_centerY
//                visibleArea_y: 408
//                pointerOffset_x: 400
//                startAngle: start_Angle
//                curAngle: digitSpeedAnim_dial < 40 ? 0.563 * digitSpeedAnim_dial : 8.46 * Math.log(digitSpeedAnim_dial - 24.69) - 0.42//digitSpeedAnim > 120 ? (partB_Angle / 120 * (digitSpeedAnim - 120) + partA_Angle) : (partA_Angle / 120 * digitSpeedAnim)
//                pointerSrc: "qrc:/skin1/qml/Gauge/pic_HMI_classic_default_speeddial_pointer.png"
//                maskSrc: "qrc:/skin1/qml/Gauge/pic_HMI_classic_default_speeddial_mask.png"
//            }
//        }
//    }

//    //文字版本
//    Loader{
//        id: speedTextLoader
//        sourceComponent: speedTextCom
//        active: meterMode == 1
//        visible: meterMode == 1
//        onLoaded: {
//            active = true
//        }
//    }

//    Component {
//        id: speedTextCom
//        Item {
//            id:speedTextItem
//            width: 1920
//            height: 720
//            CustomText {
//                id: speedText
//                x:17
//                y:583
//                width:165
//                height:52
//                text:Math.floor(digitSpeedAnim)
//                font.pixelSize: 70

//            }
//            CustomText {
//                x:198
//                y:614
//                width: 94
//                height: 24
//                opacity: 0.6
//                color: "#e3e3e3"
//                text:"km/h"
//                font.pixelSize: 30
//            }
//        }
//    }



///**************************************************************************************************************************/

//    Loader{
//        id: powerDialLoader
//        sourceComponent: powerDialCom
//        active: meterMode == 0
//        visible: meterMode == 0
//        onLoaded: {
//            active = true
//        }
//    }

//    Component{
//        id: powerDialCom
//        Item{
//            id: powerDialItem
//            width: 1920
//            height: 720
//            //圆心
//            property real power_centerX: 1092
//            property real power_centerY: 180
//            property real power_radius: 876
//            property real power_startAngle: 61

//            Image { // 功率底图
//                id: powerBg
//                y: 434
//                anchors.right: parent.right
//                source: ("pic_HMI_classic_default_powerdiall_base.png");
//                Image{
//                    x: 137
//                    y: 85
//                    source: "pic_HMI_classic_default_powerdial_number.png"
//                }
//            }

//            CustomShape{//功率 -100 ~ 0
//                center_x: power_centerX
//                center_y: power_centerY
//                width: powerDialItem.power_radius*2
//                height: width
//                radius: powerDialItem.power_radius
//                startAngle: power_startAngle
//                curAngle: Math.abs((powerAnim < 0 ? powerAnim: 0) * 0.1125)                       //positive_Angle / 100 * Math.abs(powerAnim < 0 ? powerAnim: 0)//用visible和opacity会有卡顿
//                headlightSrc: "qrc:/skin1/qml/Gauge/pic_HMI_classic_default_powerdial_highlight2.png"
//                headlightY: 617
//                headlightX: 1223
//            }

//            CustomShape{//功率 0 ~ 100
//                id: powerShape
//                center_x: power_centerX
//                center_y: power_centerY
//                width: powerDialItem.power_radius*2
//                height: width
//                radius: powerDialItem.power_radius
//                startAngle: power_startAngle
//                curAngle: -Math.pow((powerAnim >= 0 ? powerAnim : 0), 0.7) * 1.34         //-negative_Angle / 100 * (powerAnim >= 0 ? powerAnim : 0)
//                headlightSrc: "qrc:/skin1/qml/Gauge/pic_HMI_classic_default_powerdial_highlight.png"
//                headlightY: 502
//                headlightX: 1254
//            }

//            CustomPointer{
//                radius: powerDialItem.power_radius
//                center_x: power_centerX
//                center_y: power_centerY
//                visibleArea_x: 1125
//                visibleArea_y: 407
//                pointerOffset_x: 400
//                startAngle: power_startAngle
//                curAngle: {
//                    if(powerAnim < 0){
//                        Math.abs(powerAnim * 0.1125)
//                    }else{
//                        -Math.pow(powerAnim, 0.7) * 1.34
//                    }
//                    //(powerAnim < 0 ? positive_Angle : -negative_Angle) / 100 * Math.abs(powerAnim)
//                }

//                pointerSrc: "qrc:/skin1/qml/Gauge/pic_HMI_classic_default_speeddial_pointer.png"
//                maskSrc: "qrc:/skin1/qml/Gauge/pic_HMI_classic_default_powerdial_mask.png"
//            }
//        }
//    }


//    //文字版本
//    Loader{
//        id: powerTextLoader
//        sourceComponent: powerTextCom
//        active: meterMode == 1
//        visible: meterMode == 1
//        onLoaded: {
//            active = true
//        }

//    }

//    Component {
//        id: powerTextCom
//        Item {
//            id:powerTextItem
//            width: 1920
//            height: 720
//            CustomText {
//                x:1616
//                y:619
//                width: 125
//                height: 17
//                opacity: 0.6
//                color: "#e3e3e3"
//                text:"PWR(%)"
//                font.pixelSize: 24
//            }
//            CustomText {
//                id: powerText
//                x:1736
//                y:585
//                width:167
//                height:52
//                text:Math.floor(powerAnim)
//                font.pixelSize: 70
//            }
//        }
//    }

//    property real speedAngle: 0
//    Row{
//        spacing: 10
//        Slider{
//            id: s
//            width: 200
//            minimumValue: /*98//*/0
//            maximumValue: /*168//*/49
//        }
//        Slider{
//            id: ss
//            width: 200
//            minimumValue: /*98//*/-100
//            maximumValue: /*168//*/100
//        }
//    }

}
