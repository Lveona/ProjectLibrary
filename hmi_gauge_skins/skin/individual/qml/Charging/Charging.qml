import QtQuick 2.0
import "../Common"
import qmlEnums 1.0

Item {
    id: charging
    width: 1920
    height: 720
    property bool isCardShown: CarInfoScreen.isCardShown//c区卡片是否显示
    property var remainTime: HomeScreen.remainTime  //剩余充电时间
    property var chargeStatus: HomeScreen.chargeStatus  //充电状态
    property bool isCharging: HomeScreen.isCharging  //充电状态

    property string remainRange: CarInfoScreen.remainRange //续航里程

    property var chargePercent: HomeScreen.chargeValue  //剩余电量值
    property var chargeColor : HomeScreen.chargeColor   //进度条颜色

    property bool isWarningState : Manager.isWarningState
    property var voltage: HomeScreen.chargeVoltage  //充电电压
    property var elect: HomeScreen.chargeElect  //充电电流
    property var miniAdas: ADASScreen.miniAdasVisible
    property var doorWarning   : HomeScreen.doorWarning   //车门报警
    property var fldoor: HomeScreen.flDoor  //车前左门
    property var frdoor: HomeScreen.frDoor  //车前右门
    property var rldoor: HomeScreen.rlDoor  //车后左门
    property var rrdoor: HomeScreen.rrDoor  //车后右门
    property var tail: HomeScreen.tail  //车尾门
    property var hood: HomeScreen.hood  //车前门

    function trRemainTime(v)
    {
        return v.replace("小时",trLanguge("小时")).replace("分钟",trLanguge("分钟"));
    }
    Image{
        source: "charge_bg.png"
    }

    Image{
        source: "charge_door1.png"
        x: 833
        y: 130
        visible: frdoor
    }
    Image{
        source: "charge_door4.png"
        x: 990
        y: 126
        visible: rrdoor
    }

    Image{
        source: "charge_emptycar.png"
        x: 320
        y: 24
        visible:doorWarning
    }
    Image{
        source: "charge_backgap.png"
        x: 1209
        y: 218
        visible: tail
    }
    Image{
        source: "charge_door2.png"
        x: 803
        y: 342
        visible: fldoor
    }

    Image{
        source: "charge_door3.png"
        x: 955
        y: 294
        visible: rldoor
    }


    Image{
        source: "charge_frontgap.png"
        x: 628
        y: 169
        visible: hood
    }


    Image{
        source: "rightring.png"
        y: 275
        x: 125
        visible: !isWarningState && !isCardShown
        CustomText{
            id: remainId
            x: 94
            y : 48
            font.pixelSize: 28
            color: "#C4BAB4";
            font.family:trLanguge("font")
            text: trLanguge("当前续航")+":"
        }
        CustomText{
            font.family:trLanguge("font")
            anchors.left: remainId.right
            anchors.verticalCenter: remainId.verticalCenter
            font.pixelSize: 28
            color: "#C4BAB4";
            text:  remainRange + "km"
        }
    }

    //右侧区域
    Image{
        id: leftBg
        x: 1452
        y: 275
        width: sourceSize.width
        height: sourceSize.height
        visible: !miniAdas
        source: "leftring.png"

        Item{
            id: connectItem
            width: leftBg.width
            height: leftBg.height

        }

        Item{
            id: chargingItem
            width: leftBg.width
            height: leftBg.height
            visible: true

            Image{
                id: chargeImg
                y: 3
                anchors.left: chargeTxt.left
                source: {
                    switch(chargeStatus){
                    case 0x2:
                    case 0x4:
                    case 0xA:
                    case 0xC:
                        "HMI_charge.png"
                        break;
                    default:
                        ""
                        break;
                    }
                }

            }
            Image{
                id: chargeImg_2
                y: 3
                anchors.horizontalCenter:  chargingItem.horizontalCenter
                source: {
                    switch(chargeStatus){
                    case 0x1:
                    case 0x3:
                    case 0x6:
                    case 0x9:
                    case 0xB:
                    case 0xD:
                        "charging_connect.png"
                        break;
                    case 0x7:
                    case 0xF:
                        "charge_warning.png"
                        break;
                    default:
                        ""
                        break;
                    }
                }

            }

            CustomTextEn{
                anchors.left: chargeImg.right
                anchors.leftMargin: 9
                font.pixelSize: 26
                visible: voltage !== "--"&&voltage !== ""&&isCharging
                text: voltage + "V"
            }
            CustomTextEn{
                anchors.left: chargeImg.right
                anchors.top: chargeImg.top
                font.pixelSize: 26
                visible: elect !== "--"&&elect !== ""&&isCharging
                text: elect + "A"
            }
            CustomText{
                id: chargingTxt
                anchors.horizontalCenter:  chargingItem.horizontalCenter
                anchors.bottom: chargingItem.top
                anchors.bottomMargin: 10
                color: "#e4e4e4"
                font.pixelSize: 26
                visible: remainTime !== ""
                font.family:trLanguge("font")
                text:{
                    switch(chargeStatus){
                    case 0x3:
                    case 0xB:
                        trLanguge("充电已完成")
                        break;
                    case 0x6:
                    case 0xD:
                        trLanguge("放电中…")
                        break;
                    case 0x7:
                    case 0xF:
                        trLanguge("充电系统故障")
                        break;
                    default:
                        ""
                        break;
                    }
                }
            }

            CustomText{
                id: chargeTxt
                anchors.horizontalCenter: chargingItem.horizontalCenter
                anchors.top: chargingItem.top
                anchors.topMargin: 75
                color: "#e4e4e4"
                font.pixelSize: 26
                opacity: 0.5
                font.family:trLanguge("font")
                text: {
                    switch(chargeStatus){
                    case 0x01:
                    case 0x03:
                    case 0x09:
                    case 0x0B:
                        trLanguge("充电枪已插入")
                        break;
                    case 0x02:
                    case 0x04:
                    case 0xA:
                    case 0xC:
                        trLanguge("充电中…")
                        break;
                    case 0x6:
                    case 0xD:
                        trLanguge("放电枪已插入")
                        break;
                    default:
                        ""
                        break;
                    }
                }
            }
            CustomText{
                id: remainTxt
                anchors.left: chargingItem.left
                anchors.leftMargin: 99
                anchors.top: chargingItem.top
                anchors.topMargin: 169
                color: "#e4e4e4"
                font.pixelSize: 26
                width: 350
                wrapMode: Text.WordWrap
                visible: remainTime !== ""&&isCharging
                font.family:trLanguge("font")
                text: trLanguge("充满剩余时间")+":"+trRemainTime(remainTime);
            }


        }
    }

    Loader{
        id: chargeLoader
        active: true
        sourceComponent: chargeCom
    }

    Component{
        id: chargeCom
        Image{
            y: 458
            x: 393
            source: "car_battery.png"
            Item{
                height: battImg.height
                width: chargePercent === "--" ? 0 : chargePercent / 100 * battImg.width
                anchors.left: parent.left
                anchors.leftMargin: 341.5
                anchors.verticalCenter: parent.verticalCenter
                clip: true
                Image{
                    id: battImg
                    source: {
                        if(chargeColor === COLORTYPEEnums.COLORTYPEQML_RED){
                            "red.png"
                        }else if(chargeColor === COLORTYPEEnums.COLORTYPEQML_YELLOW){
                            "yellow.png"
                        }else if(chargeColor === COLORTYPEEnums.COLORTYPEQML_GREEN){
                            "green.png"
                        }else{
                            ""
                        }
                    }
                }
            }
            CustomText{
                text: chargePercent + "%"
                color: "#e4e4e4"
                font.pixelSize: 60
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

}
