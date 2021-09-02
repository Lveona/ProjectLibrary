﻿import QtQuick 2.8
import "./../Common/"
import qmlEnums 1.0
import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Shapes 1.15 //放在 import QtGraphicalEffects 1.0 下面

Item {
    id: home
    width: 1920
    height: 720
    opacity:0.0
    property var isAdasWarn: ADASScreen.miniAdasVisible //是否有报警
    property var chargeConn: HomeScreen.chargeConn

    property var isReady: HomeScreen.isReady//ready
    property var chargeValue: HomeScreen.chargeValue//剩余电量值
    property var chargeAnimState : HomeScreen.chargeAnimState //剩余电量动画是否执行
    property var chargeColor : HomeScreen.chargeColor //进度条颜色
    property var gearStatus: HomeScreen.gear//档位信息
    property var odo : HomeScreen.odo //总计里程
    property var temp : HomeScreen.temp //室外温度
    property var driveMode: HomeScreen.driveMode//驾驶模式

    property var doorWarning   : HomeScreen.doorWarning   //车门报警
    property var hood   : HomeScreen.hood   //前舱盖
    property var flDoor : HomeScreen.flDoor //主驾
    property var frDoor : HomeScreen.frDoor //副驾
    property var rlDoor : HomeScreen.rlDoor //后排左
    property var rrDoor : HomeScreen.rrDoor //后排右
    property var tail   : HomeScreen.tail   //尾门
    property var flChargePort: HomeScreen.flChargePort //左充电口盖
    property var frChargePort: HomeScreen.frChargePort //右充电口盖

    property var volumeVisible   : InterconnectScreen.volumeVisible   //音量调
    property var volumePercent   : InterconnectScreen.volumePercent   //当前音量百分比
    property var miniAdas: ADASScreen.miniAdasVisible
    property int navigationMapMod: InterconnectScreen.navigationMapMod
    property bool carDoorVisible: funcCarDoorVisible()
    property int currentPage: SettingScreen.currentPage

    //渐变的宽度
    property int valuewidht: 0

    //home入场渐变效果
    SequentialAnimation {
        id:homeAllAnim_Start
        NumberAnimation {target: home; duration: 1000; properties: "opacity"; from: 0.0; to: 1.0;}
    }

    //home导航入场渐变效果
    SequentialAnimation {
        id:homeAllAnim_Start_Nai
        NumberAnimation {target: home; duration: 1000; properties: "opacity"; from: 0.0; to: 1.0;}
    }

    //home出场整体渐变效果
    SequentialAnimation {
        id:homeAllAnim_End
        NumberAnimation {target: home; duration: 1000; properties: "opacity"; from: 1.0; to: 0.0;}
        onStopped: {
            anim_topline_chu_Start() //topline出场动效
        }
    }

    //home导航出场整体渐变效果
    SequentialAnimation {
        id:homeAllAnim_End_Nai
        NumberAnimation {target: home; duration: 1000; properties: "opacity"; from: 1.0; to: 0.0;}
        onStopped: {
            anim_topline_chu_Start_Nai()
        }
    }

    //home整体入场动效
    function homeAnimStart(){
        homeAllAnim_Start.start()
    }

    //home导航入场
    function homeAnimStart_Nai(){
        homeAllAnim_Start_Nai.start()
    }

    //home整体入场动效停止
    function homeAnimStart_Stop(){
        homeAllAnim_Start.complete()
    }

    //home整体出场动效
    function homeAnimEnd(){
        homeAllAnim_End.start()
    }

    //home导航整体出场动效
    function homeAnimEnd_Nai(){
        homeAllAnim_End_Nai.start()
    }

    //home整体出场动效停止
    function homeAnimEnd_Stop(){
        homeAllAnim_End.complete()
    }

    function funcCarDoorVisible(){
        if(navigationMapMod === 1 || navigationMapMod === 2){
            if(miniAdas){
                return false;
            }else{
                return true;
            }
        }else{
            return true;
        }
    }

        Image{
            id: lineImg
            y: 25
            x: 514
            width: 895
            height: 54

        //驾驶模式
        CustomTextEn{
            id: dm
            x: 142
            y: 7
            width: 186
            font.pixelSize: 24
            color: "#f4d4b7"
            text: driveMode
        }

        //Ready灯
        CustomTextEn{
            id: readyTxt
            anchors.right: lineImg.right
            anchors.rightMargin: 165
            anchors.top: lineImg.top
            anchors.topMargin: 9
            color: "#4bfc28"
            font.pixelSize: 24
            text: "READY"
            visible: isReady
        }

        //档位
        Image{
            id: gear
            anchors.horizontalCenter: lineImg.horizontalCenter
            anchors.leftMargin: 430
            anchors.top: lineImg.top
            anchors.topMargin: -5
            source: gearStatus !== "--" ? gearStatus + ".png" : ""
        }/*

        CustomTextEn{
            width: 33
            height: width
            anchors.horizontalCenter: lineImg.horizontalCenter
            anchors.leftMargin: 430
            anchors.top: lineImg.top
            anchors.topMargin: -5
            color: "#f8d8bb"
            font.pixelSize: 46
            text: gearStatus === "--" ? gearStatus : ""
        }*/
    }
    Item{
        id: bottomItem
        width: parent.width
        height: 24
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 17
        visible: !chargeConn

        //ODO
        CustomTextEn{
            anchors.right: parent.right
            anchors.rightMargin: 269
            font.pixelSize: 32
            color: "#C4BAB4"
            text: odo + "km"
        }

        // 室外温度
        CustomTextEn{
            anchors.rightMargin: 51
            anchors.right: parent.right
            color: "#C4BAB4"
            font.pixelSize: 32
            text: temp + "°C"//℃
        }
    }

    //电量
    Loader{
        id: socLoader
        active: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
        visible: !chargeConn
        sourceComponent: socComponent
        onLoaded: {
            active = true
        }
    }
    Component{
        id: socComponent
        Item{
            id: socItm
            width: 1920
            height: 31
            y: 672

            Image {
                id: socProgressGray
                anchors.left: socItm.left
                anchors.leftMargin: 62
                source:"progressBar_gray.png"
                height: 31
                Item{
                    id: itemBlue
                    anchors.left: parent.left
                    anchors.leftMargin: -1
                    height: socProgress.height
                    width: chargeValue === "--" ? 0 : chargeValue / 100 * socProgressGray.sourceSize.width + 4 //5是图片的边缘
                    anchors.verticalCenter: parent.verticalCenter
                    clip: true

                    Image {
                        id: socProgress
                        source: {
                            if(chargeColor === COLORTYPEEnums.COLORTYPEQML_RED){
                                "progressBar_red.png"
                            }else if(chargeColor === COLORTYPEEnums.COLORTYPEQML_YELLOW){
                                "progressBar_yellow.png"
                            }else if(chargeColor === COLORTYPEEnums.COLORTYPEQML_GREEN){
                                "progressBar_green.png"
                            }else{
                                ""
                            }
                        }
                    }
                }
            }

            CustomTextEn{
                id: epTxt
                anchors.left: socProgressGray.right
                anchors.leftMargin: 18
                anchors.verticalCenter: socProgressGray.verticalCenter
                font.pixelSize: 32
                color: "#C4BAB4";
                text: chargeValue
            }

            CustomTextEn{
                anchors.left: epTxt.right
                anchors.verticalCenter: socProgressGray.verticalCenter
                font.pixelSize: 32
                color: "#C4BAB4";
                text: "%"
            }
        }
    }

    //车门
    Loader{
        id: carDoorLoader
        active: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
        visible: !chargeConn && carDoorVisible
        sourceComponent: carDoorComponent
        onLoaded: {
            active = true
        }
    }
    Component{
        id: carDoorComponent
        Image {
            id: name
            x: 1541
            y: 186
            source: "door_bg.png"
            visible: doorWarning &&  !isAdasWarn
            Image{
                x: -22
                y: 53
                source: "left_charge.png"
                visible: flChargePort
            }

            Image{
                x: 118
                y: 53
                source: "right_charge.png"
                visible: frChargePort
            }

            Image{
                anchors.horizontalCenter: parent.horizontalCenter
                y: 5
                source: "hood_door.png"
                visible: hood
            }
            Image{
                x: -38
                y: 94
                anchors.verticalCenter: frId.verticalCenter
                source: "left_door.png"
                visible: flDoor
            }
            Image{
                id: frId
                x: 116
                y: 94
                source: "right_door.png"
                visible: frDoor
            }
            Image{
                x: -38
                y: 152
                anchors.verticalCenter: rrId.verticalCenter
                source: "left_door.png"
                visible: rlDoor
            }
            Image{
                id: rrId
                x: 116
                y: 152
                source: "right_door.png"
                visible: rrDoor
            }
            Image{
                anchors.horizontalCenter: parent.horizontalCenter
                y: 236
                source: "tail_door.png"
                visible: tail
            }
        }
    }

    //音量条
    Image{
        id: bg
        visible:false//volumeVisible
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        source: "pic_toast_white.png"
        Image{
            id: volumeImg
            x: 192
            y: 20
            source: "icon_toast_volume.png"
        }

        Row {
            id: volumeBarBg
            anchors.left: volumeImg.right
            anchors.leftMargin: 12
            anchors.verticalCenter: volumeImg.verticalCenter
            spacing: -13
            Repeater {
                id: s1
                model: 22
                Image {
                    width: sourceSize.width
                    height: sourceSize.height
                    source: "sound_bg.png"
                }
            }
        }
        Row {
            id: curVolume
            anchors.left: volumeImg.right
            anchors.leftMargin: 12
            anchors.verticalCenter: volumeImg.verticalCenter
            spacing: -13
            Repeater {
                model: s1.model * volumePercent / 100
                Image {
                    width: sourceSize.width
                    height: sourceSize.height
                    source: "sound_hl.png"
                }
            }
        }
    }
}
