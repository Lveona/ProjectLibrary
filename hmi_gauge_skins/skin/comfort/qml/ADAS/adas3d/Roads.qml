import QtQuick 2.15
//import QtQuick3D 1.15
import "../custools"
//includes:
//  4 lanes
//  center alarm
//  left lane alram
//  right lane alarm.

Item {
    id: root
    height: 800
    width: 600

    //PUBLIC settings
    //increasing time value
    property real settingTime: 0.0
    property real digitSpeed: 0.0

    //each lane color index: 0 - 3
    //each lane style: 0 - 2
    property int settingLane0Type: ADASScreen.laneLine3_Type
    property int settingLane0ColorIndex: ADASScreen.laneLine3_Color
    onSettingLane0ColorIndexChanged: {setColorlane0();}
    property int settingLane1Type: ADASScreen.laneLine1_Type
    property int settingLane1ColorIndex: ADASScreen.laneLine1_Color
    onSettingLane1ColorIndexChanged: {setColorlane1();}
    property int settingLane2Type: ADASScreen.laneLine2_Type
    property int settingLane2ColorIndex: ADASScreen.laneLine2_Color
    onSettingLane2ColorIndexChanged: {setColorlane2();}
    property int settingLane3Type: ADASScreen.laneLine4_Type
    property int settingLane3ColorIndex: ADASScreen.laneLine4_Color
    onSettingLane3ColorIndexChanged: {setColorlane3();}

    //车道线显示
    property bool settingLane3_Display: ADASScreen.laneLine3_Display
    property bool settingLane1_Display: ADASScreen.laneLine1_Display
    property bool settingLane2_Display: ADASScreen.laneLine2_Display
    property bool settingLane4_Display: ADASScreen.laneLine4_Display

    //车道线曲率
    property real settingCurve0: ADASScreen.laneLine3_Curv
    property real settingCurve1: ADASScreen.laneLine1_Curv
    property real settingCurve2: ADASScreen.laneLine2_Curv
    property real settingCurve3: ADASScreen.laneLine4_Curv
    //HWA曲率
    property real settingCurve_HWA: ADASScreen.laneLine2_Curv

    //lane No.1 and No.2 luminous effect enable
    property bool settingLaneLuminousEnable: true

    //car front bottom alarm position, enable
    property real settingCarFrontBottomAlarmStartPos: 0.5

    //车道 控制
    property int settingCarFrontBottomAlarmEnable: 0 //中间
    property int settingCarFrontBottomAlarmEnable_left: 0 //左侧
    property int settingCarFrontBottomAlarmEnable_right: 0 //右侧

    //HWA渐变
    property real settingCarFrontBottomAlarmGradual1: 0
    property real settingCarFrontBottomAlarmGradual2: 0

    //蓝顔色
    property color settingCarFrontBottomAlarmColor: Qt.rgba(60.0/255.0, 170.0/255.0, 247.0/255.0, 1.0)

    //PRIVATE internal settings
    property int  settingLaneCycles: 6
    property real settingLaneWidth: 0.011
    property real settingLane0Pos:  0.0400//0.0055
    property real settingLane1Pos:  0.3310//0.3352
    property real settingLane2Pos:  0.6690//0.6648
    property real settingLane3Pos:  0.9600//0.9945

    //HWA箭头宽度（用车道线实现的）
    property real settingLaneWidth_HWA: 0.07
    //HWA箭头宽度 起始位置
    property real settingLanePos_HWA:  settingLane1Pos + 0.04

    //每条车道线颜色、发光颜色rgba参数
    property color lane0SetColor:            Qt.rgba(1.0,1.0,1.0, 1.0)
    property color lane0SetLuminousColor:    Qt.rgba(0.0,0.196,0.51, 1.0)
    property color lane1SetColor:            Qt.rgba(1.0,1.0,1.0, 1.0)
    property color lane1SetLuminousColor:    Qt.rgba(0.0,0.196,0.51, 1.0)
    property color lane2SetColor:            Qt.rgba(1.0,1.0,1.0, 1.0)
    property color lane2SetLuminousColor:    Qt.rgba(0.0,0.196,0.51, 1.0)
    property color lane3SetColor:            Qt.rgba(1.0,1.0,1.0, 1.0)
    property color lane3SetLuminousColor:    Qt.rgba(0.0,0.196,0.51, 1.0)

    //左车道
    Item {
        id: item_AlarmRende_Left
        height: 800
        width: 600

        ShaderEffect {  //红色报警区域以及车道描画
            id: alarmRende_Left
            anchors.fill: parent
            blending: true

            property real settingCurve: root.settingCurve0 //settingCurve0
            property real settingCurvePlus: root.settingCurve1//settingCurve1

            property real settingLaneWidth: root.settingLaneWidth
            property real settingLane1Pos:  root.settingLane0Pos
            property real settingLane2Pos:  root.settingLane1Pos
            property real settingCarFrontBottomAlarmStartPos: root.settingCarFrontBottomAlarmStartPos
            property int settingCarFrontBottomAlarmEnable:  root.settingCarFrontBottomAlarmEnable_left
            property color settingCarFrontBottomAlarmColor:  root.settingCarFrontBottomAlarmColor

            property var modelviewMat: modelviewMatrix
            property var projectMat: projectMatrix

            mesh: GridMesh { resolution: Qt.size(1, 100) }
            vertexShader: "qrc:/comfort/qml/ADAS/adas3d/Alarm.vsh"
            fragmentShader: "qrc:/comfort/qml/ADAS/adas3d/Alarm.fsh"
        }
    }

    //中间车道
    Item {
        id: item_AlarmRende_Middle
        height: 800
        width: 600

        ShaderEffect {  //红色报警区域以及车道描画
            id: alarmRende_Middle
            anchors.fill: parent
            blending: true

            property real settingCurve: root.settingCurve1//settingCurve1
            property real settingCurvePlus: root.settingCurve2//settingCurve2

            property real settingLaneWidth: root.settingLaneWidth
            property real settingLane1Pos:  root.settingLane1Pos
            property real settingLane2Pos:  root.settingLane2Pos
            property real settingCarFrontBottomAlarmStartPos: root.settingCarFrontBottomAlarmStartPos
            property int settingCarFrontBottomAlarmEnable:  root.settingCarFrontBottomAlarmEnable
            property color settingCarFrontBottomAlarmColor:  root.settingCarFrontBottomAlarmColor

            property var modelviewMat: modelviewMatrix
            property var projectMat: projectMatrix

            mesh: GridMesh { resolution: Qt.size(1, 100) }
            vertexShader: "qrc:/comfort/qml/ADAS/adas3d/Alarm.vsh"
            fragmentShader: "qrc:/comfort/qml/ADAS/adas3d/Alarm.fsh"
        }
    }

    //右车道
    Item {
        id: item_AlarmRende_Right
        height: 800
        width: 600

        ShaderEffect {  //红色报警区域以及车道描画
            id: alarmRende_Right
            anchors.fill: parent
            blending: true

            property real settingCurve: root.settingCurve2//settingCurve2
            property real settingCurvePlus: root.settingCurve3//settingCurve3

            property real settingLaneWidth: root.settingLaneWidth
            property real settingLane1Pos:  root.settingLane2Pos
            property real settingLane2Pos:  root.settingLane3Pos
            property real settingCarFrontBottomAlarmStartPos: root.settingCarFrontBottomAlarmStartPos
            property int settingCarFrontBottomAlarmEnable:  root.settingCarFrontBottomAlarmEnable_right
            property color settingCarFrontBottomAlarmColor:  root.settingCarFrontBottomAlarmColor

            property var modelviewMat: modelviewMatrix
            property var projectMat: projectMatrix

            mesh: GridMesh { resolution: Qt.size(1, 100) }
            vertexShader: "qrc:/comfort/qml/ADAS/adas3d/Alarm.vsh"
            fragmentShader: "qrc:/comfort/qml/ADAS/adas3d/Alarm.fsh"
        }
    }

    //车道线3
    CusRoadLine {
        id: lane0Render
        settingTime: root.settingTime
        digitSpeed: root.digitSpeed
        settingLaneType: root.settingLane0Type//settingLane0Type
        laneSetColor: root.lane0SetColor//lane0SetColor
        laneSetLuminousColor: root.lane0SetLuminousColor
//        settingLaneColorIndex: root.settingLane0ColorIndex
        settingLaneLuminousEnable: false
        settingCurve: root.settingCurve0//settingCurve0
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane0Pos
        settingIsMirrored: false
        settingCutRoad: 0.028
        visible: settingLane3_Display
    }

    //车道线1
    CusRoadLine {
        id: lane1Render
        settingTime: root.settingTime
        digitSpeed: root.digitSpeed
        settingLaneType: root.settingLane1Type//settingLane1Type
        settingLaneColorIndex: root.settingLane1ColorIndex
        settingLaneLuminousEnable: false
        settingCurve: root.settingCurve1//settingCurve1
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane1Pos
        laneSetColor: root.lane1SetColor//lane1SetColor
        laneSetLuminousColor: root.lane1SetLuminousColor
        settingIsMirrored: false
        settingCutRoad: 0.028 //((root.settingCurve1+1.5)*0.017/3)+0.048
        visible: settingLane1_Display
    }

    //车道线2
    CusRoadLine {
        id: lane2Render
        settingTime: root.settingTime
        digitSpeed: root.digitSpeed
        settingLaneType: root.settingLane2Type//settingLane2Type
        settingLaneColorIndex: root.settingLane2ColorIndex
        settingLaneLuminousEnable: false
        settingCurve: root.settingCurve2//settingCurve2
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane2Pos
        laneSetColor: root.lane2SetColor
        laneSetLuminousColor: root.lane2SetLuminousColor
        settingIsMirrored: true
        settingCutRoad: 0.028 //0.065-((root.settingCurve2+1.5)*0.017/3)
        visible: settingLane2_Display
    }

    //车道线4
    CusRoadLine {
        id: lane3Render
        settingTime: root.settingTime
        digitSpeed: root.digitSpeed
        settingLaneType: root.settingLane3Type//settingLane3Type
        //settingLaneColorIndex: root.settingLane3ColorIndex
        settingLaneLuminousEnable: false
        settingCurve: root.settingCurve3//settingCurve3
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane3Pos
        laneSetColor: root.lane3SetColor//lane3SetColor
        laneSetLuminousColor: root.lane3SetLuminousColor
        settingIsMirrored: true
        settingCutRoad: 0.028 //0.15
        visible: settingLane4_Display
    }

    //车道线高亮1
    CusRoadLine {
        id: lane0Luminous
        settingTime: root.settingTime
        settingLaneType: root.settingLane0Type
        //settingLaneColorIndex: root.settingLane1ColorIndex
        settingLaneLuminousEnable: root.settingLaneLuminousEnable
        settingCurve: root.settingCurve0
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane0Pos
        laneSetColor: root.lane0SetColor
        laneSetLuminousColor: root.lane0SetLuminousColor
        settingIsMirrored: false
        settingCutRoad: 0.028 //((root.settingCurve1+1.5)*0.017/3)+0.048
        //高亮显示
        visible: false
    }

    //车道线高亮2
    CusRoadLine {
        id: lane1Luminous
        settingTime: root.settingTime
        settingLaneType: root.settingLane1Type
        //settingLaneColorIndex: root.settingLane1ColorIndex
        settingLaneLuminousEnable: root.settingLaneLuminousEnable
        settingCurve: root.settingCurve1
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane1Pos
        laneSetColor: root.lane1SetColor
        laneSetLuminousColor: root.lane1SetLuminousColor
        settingIsMirrored: false
        settingCutRoad: 0.028 //((root.settingCurve1+1.5)*0.017/3)+0.048
        //高亮显示
        visible: false
    }

    //车道线高亮3
    CusRoadLine {
        id: lane2Luminous
        settingTime: root.settingTime
        settingLaneType: root.settingLane2Type
        //settingLaneColorIndex: root.settingLane2ColorIndex
        settingLaneLuminousEnable: root.settingLaneLuminousEnable
        settingCurve: root.settingCurve2
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane2Pos
        laneSetColor: root.lane2SetColor
        laneSetLuminousColor: root.lane2SetLuminousColor
        settingIsMirrored: true
        settingCutRoad:0.028 // 0.065-((root.settingCurve2+1.5)*0.017/3)
        //高亮显示
        visible: false
    }

    //车道线高亮4
    CusRoadLine {
        id: lane3Luminous
        settingTime: root.settingTime
        settingLaneType: root.settingLane3Type
        //settingLaneColorIndex: root.settingLane3ColorIndex
        settingLaneLuminousEnable: root.settingLaneLuminousEnable
        settingCurve: root.settingCurve3
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane3Pos
        laneSetColor: root.lane3SetColor
        laneSetLuminousColor: root.lane3SetLuminousColor
        settingIsMirrored: true
        settingCutRoad:0.028 // 0.065-((root.settingCurve2+1.5)*0.017/3)
        //高亮显示
        visible: false
    }

    //HWA巡航辅助
    Item {
        id: item_Lane_HWA_Render
        height: 800
        width: 600

        CusRoadLineHWA{
            id: lane_HWA_Render
            anchors.fill:parent
            settingTime: root.settingTime
            settingLaneType: 0//root.settingLane1Type
            laneSetColor: Qt.rgba(60.0/255.0, 170.0/255.0, 247.0/255.0, 1.0)
            laneSetLuminousColor: Qt.rgba(60.0/255.0, 170.0/255.0, 247.0/255.0, 1.0)//root.lane1SetLuminousColor
            //        settingLaneColorIndex: root.settingLane0ColorIndex
            settingLaneLuminousEnable: false
            settingCurve: root.settingCurve1//settingCurve1
            settingLaneCycles: root.settingLaneCycles
            settingLaneWidth: root.settingLaneWidth_HWA
            settingLanePos:  root.settingLanePos_HWA
            settingIsMirrored: false
            settingCutRoad: 0.028
            adasAnim_Bottom_Top: true
            //测试滑块
//            settingCarFrontBottomAlarmGradual1: root.settingCarFrontBottomAlarmGradual1
//            settingCarFrontBottomAlarmGradual2: root.settingCarFrontBottomAlarmGradual2

            //rh Can信号
            //        visible: laneLine3_Display
            //        onVisibleChanged: {
            //            console.log(laneLine3_Display)
            //        }

        }
    }

    //HWA动效
    SequentialAnimation{
        id: lane_HWA_Render_Anim
        running: true
        loops: Animation.Infinite
        //初始化操作 settingCarFrontBottomAlarmGradual2值必须为1.0
        PropertyAnimation {target: lane_HWA_Render; property: "settingCarFrontBottomAlarmGradual2"; duration: 0; from: 0.0; to: 1.0; easing.type: Easing.InOutQuad}
        PropertyAnimation {target: lane_HWA_Render; property: "settingCarFrontBottomAlarmGradual1"; duration: 1000; from: 0.0; to: 1.0; easing.type: Easing.InOutQuad}
        PropertyAnimation {target: lane_HWA_Render; property: "settingCarFrontBottomAlarmGradual2"; duration: 1000; from: 1.0; to: 0.0; easing.type: Easing.InOutQuad}
    }

    function setColorlane0(){
          if (settingLane0ColorIndex === 0) {
              lane0SetColor = Qt.rgba(220.0,220.0,220.0, 1.0); //灰色
          } else if (settingLane0ColorIndex === 1) {
              lane0SetColor = Qt.rgba(0.0,0.0,255.0, 1.0); //蓝色
          } else if (settingLane0ColorIndex === 2) {
              lane0SetColor = Qt.rgba(255.0,255.0,0.0, 1.0); //黄色
          } else if (settingLane0ColorIndex === 3) {
              lane0SetColor = Qt.rgba(255.0,0.0,0.0, 1.0); //红色
          }
      }

      function setColorlane1(){
          if (settingLane1ColorIndex === 0) {
              lane1SetColor = Qt.rgba(220.0,220.0,220.0, 1.0); //灰色
          } else if (settingLane1ColorIndex === 1) {
              lane1SetColor = Qt.rgba(0.0,0.0,255.0, 1.0); //蓝色
          } else if (settingLane1ColorIndex === 2) {
              lane1SetColor = Qt.rgba(255.0,255.0,0.0, 1.0); //黄色
          } else if (settingLane1ColorIndex === 3) {
              lane1SetColor = Qt.rgba(255.0,0.0,0.0, 1.0); //红色
          }
      }

      function setColorlane2(){
          if (settingLane2ColorIndex === 0) {
              lane2SetColor = Qt.rgba(220.0,220.0,220.0, 1.0); //灰色
          } else if (settingLane2ColorIndex === 1) {
              lane2SetColor = Qt.rgba(0.0,0.0,255.0, 1.0); //蓝色
          } else if (settingLane2ColorIndex === 2) {
              lane2SetColor = Qt.rgba(255.0,255.0,0.0, 1.0); //黄色
          } else if (settingLane2ColorIndex === 3) {
              lane2SetColor = Qt.rgba(255.0,0.0,0.0, 1.0); //红色
          }
      }

      function setColorlane3(){
          if (settingLane3ColorIndex === 0) {
              lane3SetColor = Qt.rgba(220.0,220.0,220.0, 1.0); //灰色
          } else if (settingLane3ColorIndex === 1) {
              lane3SetColor = Qt.rgba(0.0,0.0,255.0, 1.0); //蓝色
          } else if (settingLane3ColorIndex === 2) {
              lane3SetColor = Qt.rgba(255.0,255.0,0.0, 1.0); //黄色
          } else if (settingLane3ColorIndex === 3) {
              lane3SetColor = Qt.rgba(255.0,0.0,0.0, 1.0); //红色
          }
      }
}


