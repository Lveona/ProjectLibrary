import QtQuick 2.8
import "./../Common/"
import qmlEnums 1.0

Item {
    id: home
    width: 1920
    height: 720
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
        source: "topline.png"

        //驾驶模式
        CustomTextEn{
            id: dm
            x: 142
            y: 7
            width: 186
            font.pixelSize: 24
            color: "#8C8271"
            text: driveMode
        }

        //Ready灯
        CustomTextEn{
            id: readyTxt
            anchors.right: lineImg.right
            anchors.rightMargin: 165
            anchors.top: lineImg.top
            anchors.topMargin: 9
            color: "#50c5a0"
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
        active: Manager.receiveCtrlPowerMode == ManagerEnums.QML_POWERMODE_D1
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
            visible: doorWarning
            Image{
                x: -38
                y: 36
                source: "left_charge.png"
                visible: flChargePort
            }

            Image{
                x: 103
                y: 36
                source: "right_charge.png"
                visible: frChargePort
            }

            Image{
                anchors.horizontalCenter: parent.horizontalCenter
                y: -12
                source: "hood_door.png"
                visible: hood
            }
            Image{
                x: -54
                anchors.verticalCenter: frId.verticalCenter
                source: "left_door.png"
                visible: flDoor
            }
            Image{
                id: frId
                x: 97
                y: 79
                source: "right_door.png"
                visible: frDoor
            }
            Image{
                x: -54
                anchors.verticalCenter: rrId.verticalCenter
                source: "left_door.png"
                visible: rlDoor
            }
            Image{
                id: rrId
                x: 97
                y: 138
                source: "right_door.png"
                visible: rrDoor
            }
            Image{
                anchors.horizontalCenter: parent.horizontalCenter
                y: 219
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
