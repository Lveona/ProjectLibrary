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

//    Test3d{
//        visible: true
//        id: adas3d
//    }


//    Column{
//        anchors.right: parent.right
//        anchors.rightMargin: 100
//        id: c
//        spacing: 5
//        visible: false
//        property var lastx: -300
//        property var lasty: -55
//        property var lastz: 0
//        property var angle: 90
//        property var ratio: 18

//        TestSlider{
//            label: "changeProjectMatrix A"
//            s: 0
//            e: 90
//            value: c.angle
//            onVc: {
//                c.angle = v
//                Manager.changeProjectMatrix(v, c.ratio)
//            }
//        }

//        TestSlider{
//            label: "changeProjectMatrix R"
//            s: -30
//            e: 30
//            value: c.ratio
//            onVc: {
//                c.ratio = v
//                Manager.changeProjectMatrix(c.angle, v)
//            }
//        }

//        TestSlider{
//            label: "changeModelviewMatrixTranslate X"
//            s: -1000
//            e: 1000
//            value: c.lastx
//            onVc: {
//                c.lastx = v
//                Manager.changeModelviewMatrixTranslate(v, c.lasty, c.lastz)
//            }
//        }
//        TestSlider{
//            label: "changeModelviewMatrixTranslate Y"
//            s: -90
//            e: 90
//            value: c.lasty
//            onVc: {
//                c.lasty = v
//                Manager.changeModelviewMatrixTranslate(c.lastx, v, c.lastz)
//            }
//        }
//        TestSlider{
//            label: "changeModelviewMatrixTranslate Z"
//            s: 0
//            e: -100
//            value: c.lastz
//            onVc: {
//                c.lastz = v
//                Manager.changeModelviewMatrixTranslate(c.lastx, c.lasty, v)
//            }
//        }

//        TestSlider{
//            label: "changeModelviewMatrixRotate "
//            s: -90
//            e: 90
//            value: -69
//            onVc: Manager.changeModelviewMatrixRotate(v)
//        }
//    }


    Adas3D{
       gear: "D"//adas3d.gear
       digitSpeed: "100"//adas3d.digitSpeed
//        vehicleSmallColor: adas3d.vehicleSmallColor
//        roadLaneTimeout: adas3d.roadLaneTimeout

//        lane0Position: adas3d.lane0Position
//        lane1Position: adas3d.lane1Position
//        lane2Position: adas3d.lane2Position
//        lane3Position: adas3d.lane3Position

//        cIPVObstaclePosY: adas3d.cIPVObstaclePosY
//        cIPVObstaclePosX: adas3d.cIPVObstaclePosX
//        leftObstaclePosY: adas3d.leftObstaclePosY
//        leftObstaclePosX: adas3d.leftObstaclePosX
//        rightObstaclePosY: adas3d.rightObstaclePosY
//        rightObstaclePosX: adas3d.rightObstaclePosX

//        adasMidRoadCarVisible: adas3d.adasMidRoadCarVisible
//        adasLeftRoadCarVisible: adas3d.adasLeftRoadCarVisible
//        adasRightRoadCarVisible: adas3d.adasRightRoadCarVisible

//        adasLeftObstacle: adas3d.adasLeftObstacle
//        adasRightObstacle: adas3d.adasRightObstacle
//        adasCipvObstacle: adas3d.adasCipvObstacle

        adasCarRoadLineTypeLeftMost: 1//adas3d.adasCarRoadLineTypeLeftMost
        adasCarRoadLineColorLeftMost: 1//adas3d.adasCarRoadLineColorLeftMost
        adasCarRoadLineTypeLeft: 1//adas3d.adasCarRoadLineTypeLeft
        adasCarRoadLineColorLeft: 1//adas3d.adasCarRoadLineColorLeft
        adasCarRoadLineTypeRight: 1//adas3d.adasCarRoadLineTypeRight
        adasCarRoadLineColorRight: 1//adas3d.adasCarRoadLineColorRight
        adasCarRoadLineTypeRightMost: 1//adas3d.adasCarRoadLineTypeRightMost
        adasCarRoadLineColorRightMost: 1//adas3d.adasCarRoadLineColorRightMost
        adasHWAAebWaring_HWA:1
//        bottomAlarmStartPos: adas3d.bottomAlarmStartPos    //红色报警区域位置
        //HWA渐变参数
//        bottomAlarmGradual1: adas3d.bottomAlarmGradual1
//        bottomAlarmGradual2: adas3d.bottomAlarmGradual2

//        adasHWAAebWaring: adas3d.adasHWAAebWaring         //红色报警区域显示
//        adasHWAAebWaring_left: adas3d.adasHWAAebWaring_left //左侧报警区域显示
//        adasHWAAebWaring_right: adas3d.adasHWAAebWaring_right //右侧报警区域显示
    }

}
