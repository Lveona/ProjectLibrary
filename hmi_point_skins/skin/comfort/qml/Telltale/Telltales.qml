import QtQuick 2.0
import "./../Common/"
import qmlEnums 1.0
import TellData 1.0
Item {
    id: item
    x: 0
    y: 0
    property var list: TelltalesScreen.getTellListAll()

    property var leftTurnTell: list[TELLTALESIDEnums.PROPERTYID_TurnLeftLamp]
    property var rightTurnTell: list[TELLTALESIDEnums.PROPERTYID_TurnRightLamp]
    property var coolantTell: list[TELLTALESIDEnums.PROPERTYID_CoolantAlarmLamp]
    property var highBeamTell: list[TELLTALESIDEnums.PROPERTYID_HighBeamLamp]
    property var lowBeamTell: list[TELLTALESIDEnums.PROPERTYID_LowBeamLamp]
    property var lowPowerWarTell: list[TELLTALESIDEnums.PROPERTYID_LowPowerWarLamp]
    property var vcuHvBattErrTell: list[TELLTALESIDEnums.PROPERTYID_VcuHvBattErrLamp]

    property var ebdFaultTell: list[TELLTALESIDEnums.PROPERTYID_EBDFaultLamp]//EBD故障指示灯

    property var dcdcFailrWarnTell: list[TELLTALESIDEnums.PROPERTYID_DcdcFailrLamp]
    property var positionTell: list[TELLTALESIDEnums.PROPERTYID_PosiLamp]
    property var eMotorErrTell: list[TELLTALESIDEnums.PROPERTYID_EMotorAlarm]

    property var mainDriveTell: list[TELLTALESIDEnums.PROPERTYID_MainDrvrLamp]
    property var passengerTell: list[TELLTALESIDEnums.PROPERTYID_PassDriverLamp]
    property var backSeatTell: list[TELLTALESIDEnums.PROPERTYID_BackLeftLamp]
    property var backMiddleTell: list[TELLTALESIDEnums.PROPERTYID_BackMiddleLamp]
    property var backRightTell: list[TELLTALESIDEnums.PROPERTYID_BackRightLamp]

    property var antilLockBrakeTell: list[TELLTALESIDEnums.PROPERTYID_AntiLockBrakeLamp]
    property var ebdBrakeTell: list[TELLTALESIDEnums.PROPERTYID_EbdBrakeLamp]
    property var epbTell: list[TELLTALESIDEnums.PROPERTYID_EpbLamp]//驻车红色
    property var epbFaultTell: list[TELLTALESIDEnums.PROPERTYID_EpbFltLamp]//驻车故障黄色
    property var chrgCnctrDetdTell: list[TELLTALESIDEnums.PROPERTYID_ChrgCnctrDetdLamp]
    property var systemFailureTell: list[TELLTALESIDEnums.PROPERTYID_SystemFailureLamp]
    property var sysPowerLimitationTell: list[TELLTALESIDEnums.PROPERTYID_SysPowerLimitationLamp]//车辆功率提示
    property var backLeftVisible: TelltalesScreen.backLeftStatus
    property var backMidVisible: TelltalesScreen.backMidStatus
    property var backRightVisible: TelltalesScreen.backRightStatus
    property var esctcsTell: list[TELLTALESIDEnums.PROPERTYID_ESCTCS]//ESCTCS
    property var esctcsOffTell: list[TELLTALESIDEnums.PROPERTYID_ESCTCSOff]//ESCTCSOff
    property var fogTell: list[TELLTALESIDEnums.PROPERTYID_FogLamp]//后雾灯
    property var airbagTell: list[TELLTALESIDEnums.PROPERTYID_AirbagLamp]//安全气囊
    property var lowSpeedTell: list[TELLTALESIDEnums.PROPERTYID_LowSpeedLamp]//低速行人报警
    property var tireTell: list[TELLTALESIDEnums.PROPERTYID_Tire]//胎压
    property var batteryHeatTell: list[TELLTALESIDEnums.PROPERTYID_BatteryHeat]//动力电池过温告警
    property var avhTell: list[TELLTALESIDEnums.PROPERTYID_AVH]//AVH工作中
    property var hdcTell: list[TELLTALESIDEnums.PROPERTYID_HDC]//HDC指示灯
    property var hdcFaultTell: list[TELLTALESIDEnums.PROPERTYID_HDCFault]//HDC故障指示灯
    property var airSuspension_UpTell: list[TELLTALESIDEnums.PROPERTYID_AirSuspension_Up]//空气悬架上升
    property var airSuspension_DownTell: list[TELLTALESIDEnums.PROPERTYID_AirSuspension_Down]//空气悬架下降
    property var airSuspension_FaultTell: list[TELLTALESIDEnums.PROPERTYID_AirSuspension_Fault]//空气悬架故障
    property var epsSteerWarnTell: list[TELLTALESIDEnums.PROPERTYID_EpsSteerWarnLamp]//转向助力系统失效故障指示灯
    property var chargingTell: list[TELLTALESIDEnums.PROPERTYID_chargingLamp]//车辆续驶里程显示
    property var autoTell: list[TELLTALESIDEnums.PROPERTYID_autoLamp]//智能远光灯
    property var fcsTell: list[TELLTALESIDEnums.PROPERTYID_FCSLamp]//FCS灯
    property var accTell: list[TELLTALESIDEnums.PROPERTYID_ACCLamp]//ACC灯
    property var hwaTell: list[TELLTALESIDEnums.PROPERTYID_HWALamp]//HWA灯
    property var wiperTell: list[TELLTALESIDEnums.PROPERTYID_WiperfaultLamp]//前雨刮故障灯
    property var frontbonnetfaultTell: list[TELLTALESIDEnums.PROPERTYID_FrontbonnetfaultLamp]//前舱盖未关
    property var accStatusTell: list[TELLTALESIDEnums.PROPERTYID_AccStatusLamp]//ACC状态灯
    property var hwaStatusTell: list[TELLTALESIDEnums.PROPERTYID_HWAStatusLamp]//HWA状态灯
    property var speedlimitTell: list[TELLTALESIDEnums.PROPERTYID_SpeedLimitLamp]//限速标志
    property var speedlimitcancelTell: list[TELLTALESIDEnums.PROPERTYID_SpeedLimitCancelLamp]//限速取消标志
    /*[NACA-442444] BUG:P档锁故障无响应*/
    property var parkLockTell: list[TELLTALESIDEnums.PROPERTYID_ParkLockLamp]//P档锁
    property var vehSrvcWarnTell: list[TELLTALESIDEnums.PROPERTYID_VehSrvcWarn]//动力系统异常无响应
    property string accSpeed: TelltalesScreen.accSpeed
    property string speedlimit: TelltalesScreen.speedlimit

    property bool backLeftNotFasten: TelltalesScreen.backLeftNotFasten//true:左后安全带未系 false:左后安全带系上
    property bool backRightNotFasten: TelltalesScreen.backRightNotFasten//true:右后安全带未系 false:右后安全带系上
    property bool backMinNotFasten: TelltalesScreen.backMinNotFasten//true:中后安全带未系 false:中后安全带系上

    property bool backLeftSeatEmpty: TelltalesScreen.backLeftSeatEmpty//true:安全带后左未坐人 false:安全带后左坐人
    property bool backRightSeatEmpty: TelltalesScreen.backRightSeatEmpty//true:安全带后右未坐人 false:安全带后右坐人
    property bool backMinSeatEmpty: TelltalesScreen.backMinSeatEmpty//true:安全带中右未坐人 false:安全带中右坐人

    SequentialAnimation{
        id: telltalesAnim_Enter
        NumberAnimation{target: item; duration: 1000; from: 0.0; to: 1.0; properties: "opacity";}
    }

    SequentialAnimation{
        id: telltalesAnim_Out
        NumberAnimation{target: item; duration: 1000; from: 1.0; to: 0.0; properties: "opacity";}
    }

    //指示灯入场
    function telltalesAnimEnter(){
        telltalesAnim_Enter.start()
    }

    //指示灯出场
    function telltalesAnimOut(){
        telltalesAnim_Out.stop()
    }

    //前雨刮故障指示灯
    Image{ x: 14; y: 12;
        visible:  wiperTell.targetValue;
        source: "wiperfault.png"
    }

    //转向助力系统失效故障指示灯
    Image{ x: 90; y: 12;
        visible:  epsSteerWarnTell.targetValue;
        source: if(epsSteerWarnTell.colorType === COLORTYPEEnums.COLORTYPEQML_YELLOW)
                {
                    "EPSfault.png"
                }
                else if(epsSteerWarnTell.colorType === COLORTYPEEnums.COLORTYPEQML_RED)
                {
                    "EPSfault_red.png"
                }
                else{
                    ""
                }
    }

    //低速行人报警
    Image{ x: 165; y: 12;
        source: "avas.png"
        visible:  lowSpeedTell.targetValue;
    }

    //空气悬架故障
    Image{ x: 241; y: 12;
        visible:  airSuspension_FaultTell.targetValue;
        source: if(airSuspension_FaultTell.colorType === COLORTYPEEnums.COLORTYPEQML_YELLOW)
                {
                    "airsuspensionfault.png"
                }
                else if(airSuspension_FaultTell.colorType === COLORTYPEEnums.COLORTYPEQML_RED)
                {
                    "airsuspensionfault_red.png"
                }
                else{
                    ""
                }
    }

    //AVH工作中
    Image{ x: 392; y: 12;
        source: if(avhTell.colorType === COLORTYPEEnums.COLORTYPEQML_GREEN)
                {
                    "avh.png"
                }
                else if(avhTell.colorType === COLORTYPEEnums.COLORTYPEQML_YELLOW)
                {
                    "avh_yellow.png"
                }
                else if(avhTell.colorType === COLORTYPEEnums.COLORTYPEQML_WHITE)
                {
                    "avh_white.png"
                }
                else{
                    ""
                }
        visible:  avhTell.targetValue;
    }

    //HDC指示灯
    Image{ x: 467; y: 12;
        visible:  hdcTell.targetValue;
        source: if(hdcTell.colorType === COLORTYPEEnums.COLORTYPEQML_GREEN)
                {
                    "hdc_green.png"
                }
                else if(hdcTell.colorType === COLORTYPEEnums.COLORTYPEQML_YELLOW)
                {
                    "hdc_yellow.png"
                }
                else{
                    ""
                }
    }

    //主副驾安全带
    Image{ x: 543; y: 12;
        source: "safebelt_Main_Pass.png"
        visible:  mainDriveTell.targetValue;
    }

    //后排安全带
    Image{
        id:backSeat
        x: 1317; y: 12;
        visible: backSeatTell.targetValue
        source: "safebelt_Back.png"

        Image{//左
            x: 13; y: 50;
            visible: !backLeftNotFasten && !backLeftSeatEmpty
            source: "safebelt_dotgreen.png"
        }
        Image{//中
            x: 25; y: 50;
            visible: !backMinNotFasten && !backMinSeatEmpty
            source: "safebelt_dotgreen.png"
        }
        Image{//右
            x: 37; y: 50;
            visible: !backRightNotFasten && !backRightSeatEmpty
            source: "safebelt_dotgreen.png"
        }

        Image{//左
            x: 13; y: 50;
            visible: backLeftSeatEmpty//未坐人
            source: "safebelt_dotgrey.png"
        }
        Image{//中
            x: 25; y: 50;
            visible: backMinSeatEmpty
            source: "safebelt_dotgrey.png"
        }
        Image{//右
            x: 37; y: 50;
            visible: backRightSeatEmpty
            source: "safebelt_dotgrey.png"
        }

        Image{//左
            x: 13; y: 50;
            visible: backLeftNotFasten && !backLeftSeatEmpty
            source: "safebelt_dotred.png"
        }
        Image{//中
            x: 25; y: 50;
            visible: backMinNotFasten && !backMinSeatEmpty
            source: "safebelt_dotred.png"
        }
        Image{//右
            x: 37; y: 50;
            visible: backRightNotFasten && !backRightSeatEmpty
            source: "safebelt_dotred.png"
        }
    }

    //驻车红色
    Image{ x: 1393; y: 12;
        source: "EPB_red.png"
        visible:  epbTell.targetValue;
    }

    //驻车故障黄色
    Image{ x: 1468; y: 12;
        source: "EPB_yellow.png"
        visible:  epbFaultTell.targetValue;
    }

    //胎压报警灯
    Image{ x: 1544; y: 12;
        source: "tirepressure.png"
        visible:  tireTell.targetValue;
    }

    //制动系统故障指示 红//制动助力系统失效故障指示 黄
    Image{ x: 1619; y: 12;
        source:
            if(ebdFaultTell.targetValue)
            {
                if(ebdFaultTell.colorType === COLORTYPEEnums.COLORTYPEQML_RED)
                {
                    "EBD_red.png"
                }
                else if(ebdFaultTell.colorType === COLORTYPEEnums.COLORTYPEQML_YELLOW)
                {
                    "EBD_yellow.png"
                }
                else
                {
                    ""
                }
            }
            else{
                ""
            }
        visible:  ebdFaultTell.targetValue;
    }

    //低电量报警
    Image{ x: 1695; y: 12;
        source: "lowbattery.png"
        visible:  lowPowerWarTell.targetValue;
    }

    //动力电池不可用故障报警
    Image{ x: 1770; y: 12;
        source: "BMS.png"
        visible:  vcuHvBattErrTell.targetValue;
    }

    //前舱盖未关
    Image{ x: 1846; y: 12;
        source: "frontbonnetfault.png"
        visible:  frontbonnetfaultTell.targetValue;
    }

//第二排
    //安全气囊
    Image{ x: 14; y: 86;
        source: "srs.png"
        visible:  airbagTell.targetValue;
    }

    //ABS
    Image{ x: 90; y: 86;
        source: "ABS.png"
        visible:  antilLockBrakeTell.targetValue;
    }

    //电机系统严重故障报警
    Image{ x: 166; y: 86;
        source: "batterysystemfault.png"
        visible:  eMotorErrTell.targetValue;
    }

    //ESCTCS
    Image{ x: 242; y: 86;
        source: "TCS.png"
        visible:  esctcsTell.targetValue;
    }

    //ESCTCSOFF
    Image{ x: 316; y: 86;
        source: "TCSoff.png"
        visible:  esctcsOffTell.targetValue;
    }

    //AUTOLIGHT
    Image{ x: 392; y: 86;
        source: if(autoTell.colorType === COLORTYPEEnums.COLORTYPEQML_BLUE)
                {
                    "autolight_blue.png"
                }
                else if(autoTell.colorType === COLORTYPEEnums.COLORTYPEQML_WHITE)
                {
                    "autolight_white.png"
                }
                else if(autoTell.colorType === COLORTYPEEnums.COLORTYPEQML_RED)
                {
                    "autolight_red.png"
                }
                else{""}
        visible:  autoTell.targetValue;
    }

    //后雾灯
    Image{ x: 468; y: 86;
        source: "foglight.png"
        visible:  fogTell.targetValue;
    }

    //位置灯
    Image{ x: 543; y: 86;
        source: "parkinglight.png"
        visible:  positionTell.targetValue;
    }

    //左转向
    Image{ x: 619; y: 86;
        source: "leftlight.png"
        visible:  leftTurnTell.targetValue;
    }

    //HWA指示灯
    Image{ x: 696; y: 86;
        source: if(hwaStatusTell.colorType === COLORTYPEEnums.COLORTYPEQML_BLUE)
                {
                    "steelringwhell.png"
                }
                else if(hwaStatusTell.colorType === COLORTYPEEnums.COLORTYPEQML_GRAY)
                {
                    "steelringwhell_grey.png"
                }
                else if(hwaStatusTell.colorType === COLORTYPEEnums.COLORTYPEQML_YELLOW)
                {
                    "steelringwhell_yellow.png"
                }
                else{
                    ""
                }
        visible:  hwaStatusTell.targetValue;
    }

    //ACC状态
    Image{
        id:accStatus
        x: 1156; y: 86;
        source: if(accStatusTell.colorType === COLORTYPEEnums.COLORTYPEQML_BLUE)
                {
                    "maxspeed.png"
                }
                else if(accStatusTell.colorType === COLORTYPEEnums.COLORTYPEQML_GRAY)
                {
                    "maxspeed_grey.png"
                }
                else if(accStatusTell.colorType === COLORTYPEEnums.COLORTYPEQML_YELLOW)
                {
                    "maxspeed_yellow.png"
                }
                else{""}
        visible:  accStatusTell.targetValue;
    }
    /*[NACA-442444] BUG:P档锁故障无响应*/
    //P档锁故障
    Image{ x: 1846; y: 86;
        source: "Pfault.png"
        visible:  parkLockTell.targetValue;
    }
    Image{ x: 1694; y: 99;
        source: "icon_warning_dynamicwrong.png"
        visible:  vehSrvcWarnTell.targetValue;
    }

    CustomText{
        y:103
        anchors.horizontalCenter:accStatus.horizontalCenter
        font.pixelSize: 26
        text:accSpeed
        color: "white"
        visible: accStatus.visible
        font.family: "FZLanTingHeiS-R-GB"
    }

    //右转向
    Image{ x: 1238; y: 86;
        source: "rightlight.png"
        visible:  rightTurnTell.targetValue;
    }

    //近光灯
    Image{ x: 1315; y: 86;
        source: "headlight.png"
        visible:  lowBeamTell.targetValue;
    }

    //远光灯
    Image{ x: 1391; y:86;
        source: "headlightfullbeam.png"
        visible:  highBeamTell.targetValue;
    }

    //车辆限功率提示
    Image{ x: 1468; y: 86;
        source: "powerlimit.png"
        visible:  sysPowerLimitationTell.targetValue;
    }

    //电机冷却液/电池冷却液
    Image{ x: 1542; y: 86;
        source: "coolant.png"
        visible:  coolantTell.targetValue;
    }

    //DCDC
    Image{ x: 1618; y: 86;
        source: if(dcdcFailrWarnTell.colorType === COLORTYPEEnums.COLORTYPEQML_RED)
                {
                    "DCDCfault.png"
                }
                else if(dcdcFailrWarnTell.colorType === COLORTYPEEnums.COLORTYPEQML_YELLOW)
                {
                    "DCDC_yellow.png"
                }
                else{
                    ""
                }
        visible:  dcdcFailrWarnTell.targetValue;
    }

    //动力系统故障
    Image{ x: 1694; y: 86;
        source: "dynasystemfault.png"
        visible:  systemFailureTell.targetValue;
    }

    //动力电池过温告警
    Image{ x: 1770; y: 86;
        source: "batteryheat.png"
        visible:  batteryHeatTell.targetValue;
    }

    //TBD:充电线连接 缺少位置坐标
    Image{
//        x:;y:;
//        source: "chargeingconnect.png"
//        visible:  chrgCnctrDetdTell.targetValue;
    }

    //限速标志
    Image{ x: 772; y: 220;
        id:speedlimitImage
        source: "speedlimit.png"
        visible: speedlimitTell.targetValue
    }
    //限速取消标志
    Image{ x: 772; y: 220;
        id:speedlimitCancelImage
        source: "speedlimit_cancel.png"
        visible: speedlimitcancelTell.targetValue
    }
    CustomText{
        anchors.horizontalCenter:speedlimitImage.horizontalCenter
        anchors.verticalCenter: speedlimitImage.verticalCenter
        font.pixelSize: 30
        text:speedlimit
        color: "black"
        visible: speedlimitImage.visible || speedlimitCancelImage.visible
        font.family: "FZLanTingHeiS-R-GB"
        font.bold: true
    }
}
