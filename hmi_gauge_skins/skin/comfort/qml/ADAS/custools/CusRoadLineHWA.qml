import QtQuick 2.0

Item {
    id: root
    height: 800
    width: 600

    property real settingTime
    property int settingLaneType
//    property int settingLaneColorIndex
    property bool settingLaneLuminousEnable//车道线发光控制开关

    property real settingCurve

    //渐变
    property real settingCarFrontBottomAlarmGradual1
    property real settingCarFrontBottomAlarmGradual2

    property int  settingLaneCycles
    property real settingLaneWidth//车道线描画宽度
    property real settingLanePos //车道线描画位置

    property color laneSetColor //车道线颜色
    property color laneSetLuminousColor //车道线发光颜色

    property bool settingIsMirrored
    property real settingCutRoad //车道线截断，最大值为1即全部截断

    property bool adasAnim_Bottom_Top: false

    ShaderEffect {
        anchors.fill: root
        blending: true
        property real settingTime: root.settingTime
        property int settingLaneType: root.settingLaneType
//        property int settingLaneColorIndex: root.settingLaneColorIndex
        property bool settingLaneLuminousEnable: root.settingLaneLuminousEnable

        property real settingCurve: root.settingCurve

        property int  settingLaneCycles: root.settingLaneCycles
        property real settingLaneWidth: root.settingLaneWidth
        property real settingLanePos:  root.settingLanePos

        property color laneSetColor: root.laneSetColor
        property color laneSetLuminousColor: root.laneSetLuminousColor

        property real settingCarFrontBottomAlarmGradual1: root.settingCarFrontBottomAlarmGradual1
        property real settingCarFrontBottomAlarmGradual2: root.settingCarFrontBottomAlarmGradual2

        property var modelviewMat: modelviewMatrix
        property var projectMat: projectMatrix

        mesh: GridMesh { resolution: Qt.size(1, 100) }
        vertexShader: "qrc:/comfort/qml/ADAS/adas3d/Arrow.vsh"
        fragmentShader: "qrc:/comfort/qml/ADAS/adas3d/Arrow.fsh"

        property bool settingIsMirrored: root.settingIsMirrored
        property real settingCutRoad: root.settingCutRoad

        property var singleDashOfLaneWithLumination: Image {
            source: "qrc:/adas_image/pic_HMI_classic_default_HWA_arrow.png"
            width: sourceSize.width
            height: sourceSize.height
            visible: false
        }
    }
}
