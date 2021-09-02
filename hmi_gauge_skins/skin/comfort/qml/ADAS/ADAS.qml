import QtQuick 2.8
import "../Common/"
import qmlEnums 1.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0
//import QtQuick.Controls 2.0
import "./custools"
import "./adas3d"

Item {
    id: adas
    width: 1920
    height: 720

    property var gearStatus: HomeScreen.gear//档位信息

    property var digitSpeed: SettingScreen.vehicleSpeed //车速

    //property int currentPage: SettingScreen.currentPage //0：当前无画面 1：充电 2：carinfo 3:导航
    //车道线颜色
    property var laneLine3_Color: ADASScreen.laneLine3_Color
    property var laneLine1_Color: ADASScreen.laneLine1_Color
    property var laneLine2_Color: ADASScreen.laneLine2_Color
    property var laneLine4_Color: ADASScreen.laneLine4_Color
    //车道线类型
    property var laneLine3_Type: ADASScreen.laneLine3_Type
    property var laneLine1_Type: ADASScreen.laneLine1_Type
    property var laneLine2_Type: ADASScreen.laneLine2_Type
    property var laneLine4_Type: ADASScreen.laneLine4_Type

//    Test3d{
//        visible: true
//        id: adas3d
//    }


    /*Column{
        id: c
        spacing: 5
        visible: false
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
                console.log("changeModelviewMatrixRotate : ",v," : ",c.ratio)
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
                console.log("changeModelviewMatrixRotate : ",c.angle," : ",v)
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
                console.log("changeModelviewMatrixRotate : ",v," : ",c.lasty," : ",c.lastz)
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
                console.log("changeModelviewMatrixRotate : ",c.lastx," : ",v," : ",c.lastz)
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
            console.log("changeModelviewMatrixRotate : ",c.lastx," : ",c.lasty," : ",v)
            }
        }

        TestSlider{
            label: "changeModelviewMatrixRotate "
            s: -90
            e: 90
            value: -69
            onVc: {
                Manager.changeModelviewMatrixRotate(v)
                console.log("changeModelviewMatrixRotate : ",v)
            }
        }
    }*/

    Adas3D{
       gear: gearStatus
       digitSpeed: adas.digitSpeed
//        vehicleSmallColor: adas3d.vehicleSmallColor
//        roadLaneTimeout: adas3d.roadLaneTimeout

//        lane0Position: adas3d.lane0Position
//        lane1Position: adas3d.lane1Position
//        lane2Position: adas3d.lane2Position
//        lane3Position: adas3d.lane3Position


        adasCarRoadLineTypeLeftMost:     laneLine3_Type
        adasCarRoadLineTypeLeft:         laneLine1_Type
        adasCarRoadLineTypeRight:        laneLine2_Type
        adasCarRoadLineTypeRightMost:    laneLine4_Type

        adasCarRoadLineColorLeftMost:    laneLine3_Color
        adasCarRoadLineColorLeft:        laneLine1_Color
        adasCarRoadLineColorRight:       laneLine2_Color
        adasCarRoadLineColorRightMost:   laneLine4_Color
        adasHWAAebWaring_HWA:1
//        bottomAlarmStartPos: adas3d.bottomAlarmStartPos    //红色报警区域位置
        //HWA渐变参数
//        bottomAlarmGradual1: adas3d.bottomAlarmGradual1
//        bottomAlarmGradual2: adas3d.bottomAlarmGradual2

//        adasHWAAebWaring: adas3d.adasHWAAebWaring         //红色报警区域显示
//        adasHWAAebWaring_left: adas3d.adasHWAAebWaring_left //左侧报警区域显示
//        adasHWAAebWaring_right: adas3d.adasHWAAebWaring_right //右侧报警区域显示
    }

    Item {
        id: roadsItem
        x:532
        y:190
        //z:12
        width: 863
        height: 470

        Image {
            id: roadsImage
            source: "qrc:/adas_image/blackMask.png"
        }

        //车道线入场
        ParallelAnimation{
            id: roadsAnim_Start
            NumberAnimation { target: roadsImage; duration: 1000; properties: "y"; from: 0.0; to: -980}
            onStarted: {
                roadTimer_Start.start() //定时器
                enterLoaderOver = true;  //入场最开始loader时
                Manager.enterAnimStart = false; //进场动画开始
                SettingScreen.currentPage = 2
            }
        }

        //车道线出场
        ParallelAnimation{
            id: roadsAnim_End
            NumberAnimation { target: roadsImage; duration: 500; properties: "y"; from: -900; to: 0.0}
            onStopped: {
                if(isThemeSetting){
                    outAnimationState = true;
                }
                SettingScreen.currentPage = 0
                adas.opacity = 0.0
                if(navigationMapMod !== InterconnectScreenEnums.SMALL_MAP){
                    naviIn.start()
                }
            }
        }
    }

    //车道线入场动效
    function roadsChanged(){
        adas.opacity = 1.0
        roadsAnim_Start.start();
    }

    //车道线入场停止
    function roadsChanged_Stop(){
        adas.opacity = 1.0
        roadsAnim_Start.complete();
    }

    //车道线出场动效
    function roadsChanged_End(){
        roadsAnim_End.start();
    }

    //车道线出场停止
    function roadsChanged_End_Stop(){
        roadsAnim_End.complete();
    }

    Timer{
        id: roadTimer_Start
        interval: 200
        running: false
        onTriggered: {
            startComfortAnim()
        }
    }
}
