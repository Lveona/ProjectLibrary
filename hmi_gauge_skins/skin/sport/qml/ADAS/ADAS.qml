import QtQuick 2.8
import "../Common/"
import qmlEnums 1.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0
import "./custools"
import "./adas3d"

Item {
    id: adas
    width: 1920
    height: 720

//    Image{
//        id: adasRoad
//        anchors.horizontalCenter: parent.horizontalCenter
//        y: 263
//        source: "adas_road.png"

//        Image{
//            anchors.left: adasRoad.left
//            anchors.leftMargin: 716
//            anchors.top: adasRoad.top
//            anchors.topMargin: 67
//            source: "car1.png"
//        }
//        Image{
//            anchors.horizontalCenter: adasRoad.horizontalCenter
//            anchors.top: adasRoad.top
//            anchors.topMargin: 77
//            source: "maincar.png"
//        }
//        Image{
//            anchors.right: adasRoad.right
//            anchors.rightMargin: 744
//            anchors.top: adasRoad.top
//            anchors.topMargin: 64
//            source: "car2.png"
//        }
//    }


    Image {
        anchors.fill: parent
        source: "qrc:/sport/qml/ADAS/ADAS_default.png"
    }

    Test3d{
//        visible: false
        id: adas3d
    }


    Column{
        anchors.right: parent.right
        anchors.rightMargin: 100
        id: c
        spacing: 5
//        visible: false
        property var lastx: -300
        property var lasty: -55
        property var lastz: 0
        property var angle: 90
        property var ratio: 18

        TestSlider{
            label: "changeProjectMatrix A"
            s: 0
            e: 90
            value: c.angle
            onVc: {
                c.angle = v
                Manager.changeProjectMatrix(v, c.ratio)
            }
        }

        TestSlider{
            label: "changeProjectMatrix R"
            s: -30
            e: 30
            value: c.ratio
            onVc: {
                c.ratio = v
                Manager.changeProjectMatrix(c.angle, v)
            }
        }

        TestSlider{
            label: "changeModelviewMatrixTranslate X"
            s: -1000
            e: 1000
            value: c.lastx
            onVc: {
                c.lastx = v
                Manager.changeModelviewMatrixTranslate(v, c.lasty, c.lastz)
            }
        }
        TestSlider{
            label: "changeModelviewMatrixTranslate Y"
            s: -90
            e: 90
            value: c.lasty
            onVc: {
                c.lasty = v
                Manager.changeModelviewMatrixTranslate(c.lastx, v, c.lastz)
            }
        }
        TestSlider{
            label: "changeModelviewMatrixTranslate Z"
            s: 0
            e: -100
            value: c.lastz
            onVc: {
                c.lastz = v
                Manager.changeModelviewMatrixTranslate(c.lastx, c.lasty, v)
            }
        }

        TestSlider{
            label: "changeModelviewMatrixRotate "
            s: -90
            e: 90
            value: -69
            onVc: Manager.changeModelviewMatrixRotate(v)
        }
    }


    Adas3D{
        gear: adas3d.gear
        digitSpeed: adas3d.digitSpeed
        vehicleSmallColor: adas3d.vehicleSmallColor
        roadLaneTimeout: adas3d.roadLaneTimeout

        lane0Position: adas3d.lane0Position
        lane1Position: adas3d.lane1Position
        lane2Position: adas3d.lane2Position
        lane3Position: adas3d.lane3Position

        cIPVObstaclePosY: adas3d.cIPVObstaclePosY
        cIPVObstaclePosX: adas3d.cIPVObstaclePosX
        leftObstaclePosY: adas3d.leftObstaclePosY
        leftObstaclePosX: adas3d.leftObstaclePosX
        rightObstaclePosY: adas3d.rightObstaclePosY
        rightObstaclePosX: adas3d.rightObstaclePosX

        adasMidRoadCarVisible: adas3d.adasMidRoadCarVisible
        adasLeftRoadCarVisible: adas3d.adasLeftRoadCarVisible
        adasRightRoadCarVisible: adas3d.adasRightRoadCarVisible

        adasLeftObstacle: adas3d.adasLeftObstacle
        adasRightObstacle: adas3d.adasRightObstacle
        adasCipvObstacle: adas3d.adasCipvObstacle

        adasCarRoadLineTypeLeftMost: adas3d.adasCarRoadLineTypeLeftMost
        adasCarRoadLineColorLeftMost: adas3d.adasCarRoadLineColorLeftMost
        adasCarRoadLineTypeLeft: adas3d.adasCarRoadLineTypeLeft
        adasCarRoadLineColorLeft: adas3d.adasCarRoadLineColorLeft
        adasCarRoadLineTypeRight: adas3d.adasCarRoadLineTypeRight
        adasCarRoadLineColorRight: adas3d.adasCarRoadLineColorRight
        adasCarRoadLineTypeRightMost: adas3d.adasCarRoadLineTypeRightMost
        adasCarRoadLineColorRightMost: adas3d.adasCarRoadLineColorRightMost
//        bottomAlarmStartPos: adas3d.bottomAlarmStartPos    //红色报警区域位置
//        adasFcwAebWaring: adas3d.adasFcwAebWaring         //红色报警区域显示

    }


/*-------------------------------------------------------------*/
//    Image{
//        id: adasRoad
//        anchors.horizontalCenter: parent.horizontalCenter
//        y: 263
//        source: "adas_road.png"

//        Image{
//            anchors.left: adasRoad.left
//            anchors.leftMargin: 716
//            anchors.top: adasRoad.top
//            anchors.topMargin: 67
//            source: "car1.png"
//        }
//        Image{
//            anchors.horizontalCenter: adasRoad.horizontalCenter
//            anchors.top: adasRoad.top
//            anchors.topMargin: 77
//            source: "maincar.png"
//        }
//        Image{
//            anchors.right: adasRoad.right
//            anchors.rightMargin: 744
//            anchors.top: adasRoad.top
//            anchors.topMargin: 64
//            source: "car2.png"
//        }
//    }

/*-------------------------------------------------------------*/
//    property int isMidAreaScreenIndex: Manager.isMidAreaScreenIndex
//    property string ldwWorkingSts: ADASScreen.ldwWorkingSts//指示灯状态
//    property string ldwWarningLine: ADASScreen.ldwWarningLine//警戒线
//    property string ldwWarningArrow: ADASScreen.ldwWarningArrow//报警箭头
//    property string dasfcmWarning: ADASScreen.dasfcmWarning//紧急制动提示符
//    property string warningWords: ADASScreen.warningWords//报警文言
////    property int speed_hundred: TelltalesScreen.adasTrafficSign_speed_hundred   //交通标示指示数字百位
////    property int speed_ten: TelltalesScreen.adasTrafficSign_speed_ten           //交通标示指示数字十位
////    property int speed_bit: TelltalesScreen.adasTrafficSign_speed_bit           //交通标示指示数字个位
//    property int speed_hundred: 0   //交通标示指示数字百位
//    property int speed_ten: 0           //交通标示指示数字十位
//    property int speed_bit: 0          //交通标示指示数字个位

//    property int isAdasScreenIndex : ADASScreen.adasScreenIndex//adas不同画面
//    property int dASACCSetHeadway  : 0//跟车距离显示
//    //isAdasScreenIndex: 0:vts,1:frontcar,2:lka_ready,3:lka_active,4:ldw_ready,
//    //5:ldw_active,6:ldw_active_right,7:ldw_active_left,8:ldw_inactive

//    property bool     hoodSts      : PopupScreen.popupDataObject.hood
//    property bool     flDoorSts    : PopupScreen.popupDataObject.flDoor
//    property bool     frDoorSts    : PopupScreen.popupDataObject.frDoor
//    property bool     rlDoorSts    : PopupScreen.popupDataObject.rlDoor
//    property bool     rrDoorSts    : PopupScreen.popupDataObject.rrDoor
//    property bool     tailSts      : PopupScreen.popupDataObject.tail

////    property string digitSpeed:GaugeScreen.digitSpeedValue     //0-220
//    property string digitSpeed:""     //0-220
//    property real n_digitSpeed: 0
//    property real digitSpeedAnim: 0
//    property real digitSpeedAnimTime: 0

//    //为了让adas的车门 关联 显示车速
//    onDigitSpeedChanged: {
//        if(Number(digitSpeed) >= 0xFFFF){
//            //0
//            digitSpeedAnim = 0
//            n_digitSpeed = 0
//        }
//        else{
//            //get speed
//            n_digitSpeed =  Qt.binding(function(){ return (Math.floor(digitSpeedAnim+0.5))})
//            digitSpeedAnimTime = Math.abs(Number(digitSpeed) - Number(digitSpeedAnim)) / 220 * 2000
//            digitSpeedAnim = Number(digitSpeed)
//        }
//    }

//    Behavior on digitSpeedAnim {
//        NumberAnimation { duration: digitSpeedAnimTime; easing.type: Easing.Linear; }
//    }

//    Loader{
//        id: loaderADAS
//        active: isMidAreaScreenIndex===2
//        sourceComponent: comADAS
//        onLoaded: {
//            active = true
//        }
//    }

//    Item {
//        id: adasShow
//        width: 1920
//        height: 720

//        Image{
//            //车道偏离指示灯
//            id: adas_working_sts
//            x:1434
//            y:443
//            source: {
//                if(ldwWorkingSts === "white")
//                {
//                    "Telltale_adas_white.png"
//                }
//                else if(ldwWorkingSts === "green")
//                {
//                    "Telltale_adas_green.png"
//                }
//                else if(ldwWorkingSts === "yellow" || ldwWorkingSts === "twinkle")
//                {
//                    "Telltale_adas_yellow.png"
//                }
//                else if(ldwWorkingSts === "blue")
//                {
//                    "Telltale_adas_blue.png"
//                }
//                else{""}
//            }
//        }

//        Image {
//            id:imgDasfcmWarning
//            x: 1371; y: 569
//            width: 60
//            height: 60
//            source:
//            {
//                if(dasfcmWarning === "red")
//                {
//                    "ADAS_Crash_Red.png"
//                }
//                else if(dasfcmWarning === "yellow")
//                {
//                    "ADAS_Crash_Yellow.png"
//                }
//                else{""}
//            }
//        }

//        Item {
//            id: adas_speed
//            x: 1434; y: 569
//            visible: false
//            height: 60
//            width: 60
//            Image {
//                id: bg
//                height: 60
//                width: 60
//                source: "../ADAS/ADAS_Speed_BG.png"
//            }
//            Row{
//                id: row
//                spacing: 0
//                anchors.horizontalCenter: adas_speed.horizontalCenter
//                anchors.verticalCenter: adas_speed.verticalCenter
//                width: {
//                    if(digitalnum1.visible == true){
//                        digitalnum1.width*3+spacing*2
//                    }
//                    else if(digitalnum2.visible == true){
//                        digitalnum1.width*2+spacing
//                    }
//                    else{
//                        digitalnum1.width
//                    }
//                }
//                height: 22
//                Image{
//                    //百位数字图片
//                    id: digitalnum1
//                    visible: speed_hundred > 0
//                    source: "../Popup/Computer_SpeedMark_"+speed_hundred+".png"
//                }
//                Image{
//                    //十位数字图片
//                    id: digitalnum2
//                    visible: !(speed_hundred <= 0 && speed_ten <= 0)
//                    source: "../Popup/Computer_SpeedMark_"+speed_ten+".png"
//                }
//                Image{
//                    //个位数字图片
//                    id: digitalnum3
//                    visible: speed_bit >= 0
//                    source: "../Popup/Computer_SpeedMark_"+speed_bit+".png"
//                }
//            }
//        }

//        Image {
//            id: adasCruiseIndicator    //自适应巡航指示灯
//            x:1371; y:506
//            height: 60
//            width: 60
//            source: {
//                //1:白 2：绿 else：无
//                if(ADASScreen.adasCruiseIndicatorColor === 1){
//                    "../Telltales/Telltale_zhishiyingxunhang_white.png"
//                }
//                else if(ADASScreen.adasCruiseIndicatorColor === 2){
//                    "../Telltales/Telltale_zhishiyingxunhang_green.png"
//                }
//                else{""}
//            }
//        }

//    }

//    Component{
//        id: comADAS
//        Item{
//            id: comAdasItem
//            width: 1920
//            height: 720
//            visible: isMidAreaScreenIndex===2

//            Image{
//                id: adas_bg
//                x:462
//                y:288
//                source:"ADAS_BG_Status.png"
//            }

//            CustomText{
//                id:adas_warning_words
//                anchors.horizontalCenter: comAdasItem.horizontalCenter
//                y:233
//                font.pixelSize: 32
//                text:
////                    if(TelltalesScreen.cruise_speed !== "" && warningWords === ""){
////                        trLanguge(TelltalesScreen.cruise_speed)
////                    }
////                    else
//                        if(warningWords !== ""){
//                        trLanguge(warningWords)
//                    }else{
//                        ""
//                    }

//                opacity: 0.7
//            }

//            Image {
//                id: imgRoadLine
//                x: 737; y: 322
//                source:
//                {
//                    if(ldwWarningLine === "ready" )
//                    {
//                        "ADAS_RoadLine_White.png"
//                    }
//                    else if(ldwWarningLine === "active" )
//                    {
//                        "ADAS_RoadLine_Green.png"
//                    }
//                    else if(ldwWarningLine === "warningRight")
//                    {
//                        "ADAS_RoadLine_Red_Right.png"
//                    }
//                    else if(ldwWarningLine === "warningLeft")
//                    {
//                        "ADAS_RoadLine_Red_Left.png"
//                    }
//                    else{""}
//                }
//            }

//            Image {
//                id:imgLdwWarningArrow
//                x: 740; y: 466
//                source:
//                {
//                    if(ldwWarningArrow === "white")
//                    {
//                        "ADAS_Arrow_White.png"
//                    }
//                    else if(ldwWarningArrow === "blue")
//                    {
//                        "ADAS_Arrow_Blue.png"
//                    }
//                    else{""}
//                }
//            }

//            Image {
//                id: vehicleSmall    //自适应巡航前方有车显示:0无，1前车灰色，2蓝色，3黄色
//                x:922; y:328
//                source: {
//                    if(ADASScreen.vehicleSmallColor === 1){
//                        "ADAS_Vehicle_FrontCar_Small_Gray.png"
//                    }
//                    else if(ADASScreen.vehicleSmallColor === 2){
//                        "ADAS_Vehicle_FrontCar_Small_Blue.png"
//                    }
//                    else if(ADASScreen.vehicleSmallColor === 3){
//                        "ADAS_Vehicle_FrontCar_Small_Yellow.png"
//                    }
//                    else{""}
//                }
//            }

//            Item{
//                id : itemVehicle
//                width: 1920
//                height:720
//                x: {
//                    if(ldwWarningLine === "warningRight")
//                    {
//                        871
//                    }
//                    else if(ldwWarningLine === "warningLeft")
//                    {
//                        791
//                    }
//                    else
//                    {831}
//                }
//                y:330

//                Image {
//                    id: imgVehicle
//                    visible:!itemVehicleDoor.visible
//                    source: "ADAS_Vehicle_OffLight.png"
//                    width: 258
//                    height: 280
//                }

//                Item{
//                    id : itemVehicleDoor
//                    width: 258
//                    height: 280
//                    visible: (flDoorSts || frDoorSts || rlDoorSts || rrDoorSts || hoodSts) && (n_digitSpeed <= 5)

//                    Image{
//                        id : imgVehicleByDoorBg
//                        source:"ADAS_Vehicle_OffLight.png"
//                    }

//                    Image{
//                        id : imgVehicleByDoorFL
//                        source:"ADAS_Vehicle_Door_FL.png"
//                        visible: flDoorSts
//                        x: 847 - itemVehicle.x
//                        y: 416 - itemVehicle.y
//                    }
//                    Image{
//                        id : imgVehicleByDoorFR
//                        source:"ADAS_Vehicle_Door_FR.png"
//                        visible: frDoorSts
//                        x: 998 - itemVehicle.x
//                        y: 416 - itemVehicle.y
//                    }
//                    Image{
//                        id : imgVehicleByDoorBL
//                        source:"ADAS_Vehicle_Door_BL.png"
//                        visible: rlDoorSts
//                        x: 838 - itemVehicle.x
//                        y: 423 - itemVehicle.y
//                    }
//                    Image{
//                        id : imgVehicleByDoorBR
//                        source:"ADAS_Vehicle_Door_BR.png"
//                        visible: rrDoorSts
//                        x: 1005 - itemVehicle.x
//                        y: 423 - itemVehicle.y
//                    }
//                    Image{
//                        id : imgVehicleByDoorF
//                        source:"ADAS_Vehicle_Door_F.png"
//                        visible: hoodSts
//                        x: 895 - itemVehicle.x
//                        y: 392 - itemVehicle.y
//                    }
////                    Image{
////                        id : imgVehicleByDoorB
////                        source:"ADAS_Vehicle_Door_B.png"
////                        visible: tailSts
////                        x: 899 - itemVehicle.x
////                        y: 415 - itemVehicle.y
////                    }
//                }
//            }

//            CustomText{
//                anchors.horizontalCenter: comAdasItem.horizontalCenter
//                y:233
//                font.pixelSize: 32
//                text:
//                    if(warningWords === ""){
//                        trLanguge(ADASScreen.cruisingSpeed)
//                    }
//                    else{
//                        ""
//                    }
//                opacity: 0.7
//            }

//            Item {
//                id: adasAdaptiveCruise  //自适应巡航
//                width: 447
//                height: 287
//                x:737; y:322
//                visible: (isAdasScreenIndex == 1)

//                //                Image {
//                //                    id: vehicleBig
//                //                    width: 214
//                //                    height: 175
//                //                    x:117; y:122; z:1
//                //                    source: "ADAS_Vehicle_VTS_Big.png"
//                //                }

//                Image {
//                    id: adasVSTDistance0
//                    width: 239
//                    height: 160
//                    x:104; y:46
//                    source: "ADAS_VTS_Distance_0.png"
//                }

//                Image {
//                    id: adasVSTDistance1
//                    width: 155
//                    height: 70
//                    x:146; y:57
//                    source: {
//                        if(ADASScreen.adasVSTDistance === 1 || ADASScreen.adasVSTDistance === 2
//                                || ADASScreen.adasVSTDistance === 3){
//                            "ADAS_VTS_Distance_1.png"
//                        }
//                        else{""}
//                    }
//                }

//                Image {
//                    id: adasVSTDistance2
//                    width: 155
//                    height: 70
//                    x:146; y:57
//                    source: {
//                        if(ADASScreen.adasVSTDistance === 1){
//                            "ADAS_VTS_Distance_2_BG.png"
//                        }
//                        else if(ADASScreen.adasVSTDistance === 2 || ADASScreen.adasVSTDistance === 3){
//                            "ADAS_VTS_Distance_2.png"
//                        }
//                        else{""}
//                    }
//                }

//                Image {
//                    id: adasVSTDistance3
//                    width: 155
//                    height: 70
//                    x:146; y:57
//                    source: {
//                        if(ADASScreen.adasVSTDistance === 1 || ADASScreen.adasVSTDistance === 2){
//                            "ADAS_VTS_Distance_3_BG.png"
//                        }
//                        else if(ADASScreen.adasVSTDistance === 3){
//                            "ADAS_VTS_Distance_3.png"
//                        }
//                        else{""}
//                    }
//                }

//            }
//            //            //车尾灯，需与UI确认
//            //            Image {
//            //                id: imgVehicleLightLeft
//            //                x: {
//            //                    if(ldwWarningLine === "warningRight")
//            //                    {
//            //                        913
//            //                    }
//            //                    else if(ldwWarningLine === "warningLeft")
//            //                    {
//            //                        833
//            //                    }
//            //                    else
//            //                    {873}
//            //                }
//            //                y: 486
//            //                source:"ADAS_Vehicle_Light_Left.png"
//            //            }
//            //            Image {
//            //                id: imgVehicleLightRight
//            //                x: {
//            //                    if(ldwWarningLine === "warningRight")
//            //                    {
//            //                        1041
//            //                    }
//            //                    else if(ldwWarningLine === "warningLeft")
//            //                    {
//            //                        961
//            //                    }
//            //                    else
//            //                    {1001}
//            //                }
//            //                y: 486
//            //                source:"ADAS_Vehicle_Light_Right.png"
//            //            }
//        }
//    }

}
