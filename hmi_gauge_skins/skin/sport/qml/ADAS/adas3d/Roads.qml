import QtQuick 2.15
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

    //each lane color index: 0 - 3
    //each lane style: 0 - 2
    property int settingLane0Type: 0//ADASScreen.laneLine1_Type
    property int settingLane0ColorIndex: 0
    onSettingLane0ColorIndexChanged: {setColorlane0();}
    property int settingLane1Type: 0//ADASScreen.laneLine2_Type
    property int settingLane1ColorIndex: 0
    onSettingLane1ColorIndexChanged: {setColorlane1();}
    property int settingLane2Type: 0//ADASScreen.laneLine3_Type
    property int settingLane2ColorIndex: 0
    onSettingLane2ColorIndexChanged: {setColorlane2();}
    property int settingLane3Type: 0//ADASScreen.laneLine4_Type
    property int settingLane3ColorIndex: 0
    onSettingLane3ColorIndexChanged: {setColorlane3();}

    //lane No.1 and No.2 luminous effect enable
    property bool settingLaneLuminousEnable: true

    //car front bottom alarm position, enable
    property real settingCarFrontBottomAlarmStartPos: 0.5
    property int settingCarFrontBottomAlarmEnable: 0
    property color settingCarFrontBottomAlarmColor: Qt.rgba(232.0/255.0, 0.0/255.0, 51.0/255.0, 1.0)

    property real settingCurve0: 0.0
    property real settingCurve1: 0.0
    property real settingCurve2: 0.0
    property real settingCurve3: 0.0

    //PRIVATE internal settings
    property int  settingLaneCycles: 6
    property real settingLaneWidth: 0.011
    property real settingLane0Pos:  0.0400//0.0055
    property real settingLane1Pos:  0.3310//0.3352
    property real settingLane2Pos:  0.6690//0.6648
    property real settingLane3Pos:  0.9600//0.9945


    //每条车道线颜色、发光颜色rgba参数
    property color lane0SetColor:            Qt.rgba(1.0,1.0,1.0, 1.0)
    property color lane0SetLuminousColor:    Qt.rgba(0.0,0.196,0.51, 1.0)
    property color lane1SetColor:            Qt.rgba(1.0,1.0,1.0, 1.0)
    property color lane1SetLuminousColor:    Qt.rgba(0.0,0.196,0.51, 1.0)
    property color lane2SetColor:            Qt.rgba(1.0,1.0,1.0, 1.0)
    property color lane2SetLuminousColor:    Qt.rgba(0.0,0.196,0.51, 1.0)
    property color lane3SetColor:            Qt.rgba(1.0,1.0,1.0, 1.0)
    property color lane3SetLuminousColor:    Qt.rgba(0.0,0.196,0.51, 1.0)

    ShaderEffect {  //红色报警区域以及车道描画
        id: alarmRender
        anchors.fill: root
        blending: true

        property real settingCurve: root.settingCurve1
        property real settingCurvePlus: root.settingCurve2

        property real settingLaneWidth: root.settingLaneWidth
        property real settingLane1Pos:  root.settingLane1Pos
        property real settingLane2Pos:  root.settingLane2Pos
        property real settingCarFrontBottomAlarmStartPos: root.settingCarFrontBottomAlarmStartPos
        property int settingCarFrontBottomAlarmEnable:  root.settingCarFrontBottomAlarmEnable
        property color settingCarFrontBottomAlarmColor:  root.settingCarFrontBottomAlarmColor

        property var modelviewMat: modelviewMatrix
        property var projectMat: projectMatrix

        mesh: GridMesh { resolution: Qt.size(1, 100) }
        vertexShader: "qrc:/sport/qml/ADAS/adas3d/Alarm.vsh"
        fragmentShader: "qrc:/sport/qml/ADAS/adas3d/Alarm.fsh"

        property var singleDashOfLaneWithLumination: Image {
            source: "qrc:/sport/qml/ADAS/singleDashOfLaneWithLumination.png"
            width: sourceSize.width
            height: sourceSize.height
            visible: false
        }
        property var singleDashOfLaneWithoutLumination: Image {
            source: "qrc:/sport/qml/ADAS/singleDashOfLaneWithoutLumination.png"
            width: sourceSize.width
            height: sourceSize.height
            visible: false
        }
    }

    //车道线1
    CusRoadLine {
        id: lane0Render
        settingTime: root.settingTime
        settingLaneType: root.settingLane0Type
        laneSetColor: root.lane0SetColor
        laneSetLuminousColor: root.lane0SetLuminousColor
//        settingLaneColorIndex: root.settingLane0ColorIndex
        settingLaneLuminousEnable: false
        settingCurve: root.settingCurve0
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane0Pos
        settingIsMirrored: false
        settingCutRoad: 0.028
        //rh Can信号显示车道线
        //        visible: laneLine0_Display
        //        onVisibleChanged: {
        //            console.log(laneLine1_Display)
        //        }
    }

    //车道线2
    CusRoadLine {
        id: lane1Render
        settingTime: root.settingTime
        settingLaneType: root.settingLane1Type
        //settingLaneColorIndex: root.settingLane1ColorIndex
        settingLaneLuminousEnable: false
        settingCurve: root.settingCurve1
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane1Pos
        laneSetColor: root.lane1SetColor
        laneSetLuminousColor: root.lane1SetLuminousColor
        settingIsMirrored: false
        settingCutRoad: 0.028 //((root.settingCurve1+1.5)*0.017/3)+0.048
        //rh Can信号显示车道线
        //        visible: laneLine1_Display
        //        onVisibleChanged: {
        //            console.log(laneLine1_Display)
        //        }
    }

    //车道线3
    CusRoadLine {
        id: lane2Render
        settingTime: root.settingTime
        settingLaneType: root.settingLane2Type
        //settingLaneColorIndex: root.settingLane2ColorIndex
        settingLaneLuminousEnable: false
        settingCurve: root.settingCurve2
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane2Pos
        laneSetColor: root.lane2SetColor
        laneSetLuminousColor: root.lane2SetLuminousColor
        settingIsMirrored: true
        settingCutRoad: 0.028 //0.065-((root.settingCurve2+1.5)*0.017/3)

        //rh Can信号显示车道线
        //        visible: laneLine2_Display
        //        onVisibleChanged: {
        //            console.log(laneLine2_Display)
        //        }
    }

    //车道线4
    CusRoadLine {
        id: lane3Render
        settingTime: root.settingTime
        settingLaneType: root.settingLane3Type
        //settingLaneColorIndex: root.settingLane3ColorIndex
        settingLaneLuminousEnable: false
        settingCurve: root.settingCurve3
        settingLaneCycles: root.settingLaneCycles
        settingLaneWidth: root.settingLaneWidth
        settingLanePos:  root.settingLane3Pos
        laneSetColor: root.lane3SetColor
        laneSetLuminousColor: root.lane3SetLuminousColor
        settingIsMirrored: true
        settingCutRoad: 0.028 //0.15
        //rh Can信号显示车道线
        //        visible: laneLine3_Display
        //        onVisibleChanged: {
        //            console.log(laneLine3_Display)
        //        }
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


    function setColorlane0(){
        if (settingLane0ColorIndex === 1) {
            lane0SetColor = Qt.rgba(1.0,0.6,0.02, 1.0);
            lane0SetLuminousColor = Qt.rgba(1.0,0.6,0.02, 1.0);
        } else if (settingLane0ColorIndex === 2) {
            lane0SetColor = Qt.rgba(1.0,1.0,1.0, 1.0);
            lane0SetLuminousColor = Qt.rgba(0.0,0.196,0.51, 1.0);
        } else if (settingLane0ColorIndex === 3) {
            lane0SetColor = Qt.rgba(0.0,1.0,0.0, 1.0);
            lane0SetLuminousColor = Qt.rgba(0.0,1.0,0.0, 1.0);
        } else if (settingLane0ColorIndex === 4) {
            lane0SetColor = Qt.rgba(0.345,0.592,1.0, 1.0);
            lane0SetLuminousColor = Qt.rgba(0.0,0.196,0.51, 1.0);
        } else if (settingLane0ColorIndex === 5) {
            lane0SetColor = Qt.rgba(1.0,0.227,0.282, 1.0);
            lane0SetLuminousColor = Qt.rgba(0.329,0.094,0.239, 1.0);
        } else if (settingLane0ColorIndex === 6) {
            lane0SetColor = Qt.rgba(0.388,0.431,0.537, 1.0);
            lane0SetLuminousColor = Qt.rgba(0.133,0.22,0.46, 1.0);
        }
    }

    function setColorlane1(){
        if (settingLane1ColorIndex === 1) {
            lane1SetColor = Qt.rgba(1.0,0.6,0.02, 1.0);
            lane1SetLuminousColor = Qt.rgba(1.0,0.6,0.02, 1.0);
        } else if (settingLane1ColorIndex === 2) {
            lane1SetColor = Qt.rgba(1.0,1.0,1.0, 1.0);
            lane1SetLuminousColor = Qt.rgba(0.0,0.196,0.51, 1.0);
        } else if (settingLane1ColorIndex === 3) {
            lane1SetColor = Qt.rgba(0.0,1.0,0.0, 1.0);
            lane1SetLuminousColor = Qt.rgba(0.0,1.0,0.0, 1.0);
        } else if (settingLane1ColorIndex === 4) {
            lane1SetColor = Qt.rgba(0.345,0.592,1.0, 1.0);
            lane1SetLuminousColor = Qt.rgba(0.0,0.196,0.51, 1.0);
        } else if (settingLane1ColorIndex === 5) {
            lane1SetColor = Qt.rgba(1.0,0.227,0.282, 1.0);
            lane1SetLuminousColor = Qt.rgba(0.329,0.094,0.239, 1.0);
        } else if (settingLane1ColorIndex === 6) {
            lane1SetColor = Qt.rgba(0.388,0.431,0.537, 1.0);
            lane1SetLuminousColor = Qt.rgba(0.133,0.22,0.46, 1.0);
        }
    }

    function setColorlane2(){
        if (settingLane2ColorIndex === 1) {
            lane2SetColor = Qt.rgba(1.0,0.6,0.02, 1.0);
            lane2SetLuminousColor = Qt.rgba(1.0,0.6,0.02, 1.0);
        } else if (settingLane2ColorIndex === 2) {
            lane2SetColor = Qt.rgba(1.0,1.0,1.0, 1.0);
            lane2SetLuminousColor = Qt.rgba(0.0,0.196,0.51, 1.0);
        } else if (settingLane2ColorIndex === 3) {
            lane2SetColor = Qt.rgba(0.0,1.0,0.0, 1.0);
            lane2SetLuminousColor = Qt.rgba(0.0,1.0,0.0, 1.0);
        } else if (settingLane2ColorIndex === 4) {
            lane2SetColor = Qt.rgba(0.345,0.592,1.0, 1.0);
            lane2SetLuminousColor = Qt.rgba(0.0,0.196,0.51, 1.0);
        } else if (settingLane2ColorIndex === 5) {
            lane2SetColor = Qt.rgba(1.0,0.227,0.282, 1.0);
            lane2SetLuminousColor = Qt.rgba(0.329,0.094,0.239, 1.0);
        } else if (settingLane2ColorIndex === 6) {
            lane2SetColor = Qt.rgba(0.388,0.431,0.537, 1.0);
            lane2SetLuminousColor = Qt.rgba(0.133,0.22,0.46, 1.0);
        }
    }

    function setColorlane3(){
        if (settingLane3ColorIndex === 1) {
            lane3SetColor = Qt.rgba(1.0,0.6,0.02, 1.0);
            lane3SetLuminousColor = Qt.rgba(1.0,0.6,0.02, 1.0);
        } else if (settingLane3ColorIndex === 2) {
            lane3SetColor = Qt.rgba(1.0,1.0,1.0, 1.0);
            lane3SetLuminousColor = Qt.rgba(0.0,0.196,0.51, 1.0);
        } else if (settingLane3ColorIndex === 3) {
            lane3SetColor = Qt.rgba(0.0,1.0,0.0, 1.0);
            lane3SetLuminousColor = Qt.rgba(0.0,1.0,0.0, 1.0);
        } else if (settingLane3ColorIndex === 4) {
            lane3SetColor = Qt.rgba(0.345,0.592,1.0, 1.0);
            lane3SetLuminousColor = Qt.rgba(0.0,0.196,0.51, 1.0);
        } else if (settingLane3ColorIndex === 5) {
            lane3SetColor = Qt.rgba(1.0,0.227,0.282, 1.0);
            lane3SetLuminousColor = Qt.rgba(0.329,0.094,0.239, 1.0);
        } else if (settingLane3ColorIndex === 6) {
            lane3SetColor = Qt.rgba(0.388,0.431,0.537, 1.0);
            lane3SetLuminousColor = Qt.rgba(0.133,0.22,0.46, 1.0);
        }
    }
}
