import QtQuick 2.15

Item {
    id:qmlProjectItem
    width: 1920
    height: 720

    property real digitSpeed
    property real digitSpeedAnim: 0
    property real digitSpeedAnimTime: 0
    property string gear
    property bool adasGearR: false  //档位信息，倒挡时停止车道线行驶动画
    property int roadLaneAnimTimes: 1

    //车道线曲率，取值：-3 ~ 3
    property real lane0Position
    property real lane1Position
    property real lane2Position
    property real lane3Position

    property real lanePosition_HWA

    property real lane0PositionAnim: 0
    property real lane1PositionAnim: 0
    property real lane2PositionAnim: 0
    property real lane3PositionAnim: 0

    property real lane0PositionAnimTime: 0
    property real lane1PositionAnimTime: 0
    property real lane2PositionAnimTime: 0
    property real lane3PositionAnimTime: 0

    // 车道线类型：实线、虚线
    property int adasCarRoadLineTypeLeftMost
    property int adasCarRoadLineTypeLeft
    property int adasCarRoadLineTypeRight
    property int adasCarRoadLineTypeRightMost

    // line0车道线颜色 【0：无效】【1：黄色】【2：白色】【3：绿色】【4：蓝色】【5：红色】【6：灰色】
    property int adasCarRoadLineColorLeftMost
    property int adasCarRoadLineColorLeft
    property int adasCarRoadLineColorRight
    property int adasCarRoadLineColorRightMost
    property int bottomAlarmStartPos    //红色报警区域位置
    property int adasHWAAebWaring
    property int adasHWAAebWaring_left
    property int adasHWAAebWaring_right
    property int adasHWAAebWaring_HWA


    //HWA渐变动画参数
    property real bottomAlarmGradual1
    property real bottomAlarmGradual2

    property int roadLaneTimeout

    //左、前、右车坐标位置
    property real cIPVObstaclePosY
    property real cIPVObstaclePosX
    property real leftObstaclePosY
    property real leftObstaclePosX
    property real rightObstaclePosY
    property real rightObstaclePosX

    //左、前、右车坐标系转换
    property real carLeftPosX:
                        if(lane2Position * leftObstaclePosX > 0){
                            leftObstaclePosX * 100.0 + lane2Position * (-1.3 * leftObstaclePosY)*1.4
                        }
                        else{
                            leftObstaclePosX * 100.0 + lane2Position * (-1.3 * leftObstaclePosY)
                        }
    property real carLeftPosZ: -570.0 - 7.5 * leftObstaclePosY
    property real carLeftRotation_y: aDAS3DID.settingCurve0/Math.abs(aDAS3DID.settingCurve0)*Math.max(0,Math.atan(Math.abs(aDAS3DID.settingCurve0)/250*((-550-(-550.0 - 7.5 * leftObstaclePosY))/1125*300-75))*180/3.1415926)*0.7

    property real carRightPosX:
                        if(lane1Position * rightObstaclePosX > 0){
                            rightObstaclePosX * 100.0 + lane1Position * (-1.3 * rightObstaclePosY)*1.4
                        }
                        else{
                            rightObstaclePosX * 100.0 + lane1Position * (-1.3 * rightObstaclePosY)
                        }
    property real carRightPosZ: -570.0 - 7.5 * rightObstaclePosY
    property real carRightRotation_y: aDAS3DID.settingCurve2/Math.abs(aDAS3DID.settingCurve2)*Math.max(0,Math.atan(Math.abs(aDAS3DID.settingCurve2)/250*((-550-(-550.0 - 7.5 * rightObstaclePosY))/1125*300-75))*180/3.1415926)*0.7

    property real carFrontPosX:
                        if(lane0Position * cIPVObstaclePosX > 0){
                            cIPVObstaclePosX * 100.0 + lane0Position * (-1.3 * cIPVObstaclePosY)*1.4
                        }
                        else{
                            cIPVObstaclePosX * 100.0 + lane0Position * (-1.3 * cIPVObstaclePosY)
                        }
    property real carFrontPosZ: -570.0 - 7.5 * cIPVObstaclePosY
    property real carFrontRotation_y: aDAS3DID.settingCurve1/Math.abs(aDAS3DID.settingCurve1)*Math.max(0,Math.atan(Math.abs(aDAS3DID.settingCurve1)/250*((-550-(-550.0 - 7.5 * cIPVObstaclePosY))/1125*300-75))*180/3.1415926)*0.7

    //前车大小变化
//    property real heavy1CarScale: 1.0 - leftObstaclePosY * 0.003
//    property real heavy2CarScale: 1.0 - rightObstaclePosY * 0.003
//    property real heavy3CarScale: 1.0 - cIPVObstaclePosY * 0.003
//    property real car1CarScale: 1.0 - leftObstaclePosY * 0.003
//    property real car2CarScale: 1.0 - rightObstaclePosY * 0.003
//    property real car3CarScale: 1.0 - cIPVObstaclePosY * 0.003
//    property real people1CarScale: 1.2 - leftObstaclePosY * 0.002
//    property real people2CarScale: 1.2 - rightObstaclePosY * 0.002
//    property real people3CarScale: 1.2 - cIPVObstaclePosY * 0.002
//    property real bicycle1CarScale: 1.2 - leftObstaclePosY * 0.002
//    property real bicycle2CarScale: 1.2 - rightObstaclePosY * 0.002
//    property real bicycle3CarScale: 1.2 - cIPVObstaclePosY * 0.002

    property real speedLeftZ: 0
    property real speedRightZ: 0
    property bool speedLeftVisible: false
    property bool speedRightVisible: false

    //模型是否可见
    property bool    adasMidRoadCarVisible
    property bool    adasLeftRoadCarVisible
    property bool    adasRightRoadCarVisible
    //模型类型： 1：bicycle  2：car  3：people  4：trunk
    property int    adasLeftObstacle
    property int    adasRightObstacle
    property int    adasCipvObstacle

    property int    vehicleSmallColor

    onDigitSpeedChanged: {
        if(digitSpeed >= 0xFFFF){
            digitSpeedAnimBehavior.enabled = false;
            digitSpeedAnimTime = Math.abs(Number(digitSpeedAnim) - 0) / 220 * 2000;
            digitSpeedAnim = 0;
            digitSpeedAnimBehavior.enabled = true;
        }
        else{
            digitSpeedAnimTime = Math.abs(Number(digitSpeed) - Number(digitSpeedAnim)) / 220 * 2000;
            digitSpeedAnim = Number(digitSpeed);
        }
    }

    onDigitSpeedAnimChanged: {
        var c_speed = Number(digitSpeedAnim);
        if(c_speed >= 140){
            c_speed = 150;
        }
        roadLaneAnimTimes = Math.ceil((c_speed - 0.4)/10);
        if(roadLaneAnimTimes <= 0){
            roadLaneAnimTimes = 1;
        }
        startRoadLaneAnim();
    }

    onGearChanged: {startRoadLaneAnim();}

    onAdasGearRChanged: {startRoadLaneAnim();}

    Behavior on digitSpeedAnim {
        id:digitSpeedAnimBehavior
        NumberAnimation { duration: digitSpeedAnimTime; easing.type: Easing.Linear; }
    }

    Behavior on lane0PositionAnim {
        id:lane0PositionAnimBehavior
        NumberAnimation { duration: lane0PositionAnimTime; easing.type: Easing.Linear; }
    }
    Behavior on lane1PositionAnim {
        id:lane1PositionAnimBehavior
        NumberAnimation { duration: lane1PositionAnimTime; easing.type: Easing.Linear; }
    }
    Behavior on lane2PositionAnim {
        id:lane2PositionAnimBehavior
        NumberAnimation { duration: lane2PositionAnimTime; easing.type: Easing.Linear; }
    }
    Behavior on lane3PositionAnim {
        id:lane3PositionAnimBehavior
        NumberAnimation { duration: lane3PositionAnimTime; easing.type: Easing.Linear; }
    }

    onLane0PositionChanged: {
        if(roadLaneTimeout != 1){
            lane0PositionAnimTime = Math.abs(lane0Position - lane0PositionAnim) / 3 * 400;
            lane0PositionAnim = lane0Position;
        }
    }
    onLane1PositionChanged: {
        if(roadLaneTimeout != 1){
            lane1PositionAnimTime = Math.abs(lane1Position - lane1PositionAnim) / 3 * 400;
            lane1PositionAnim = lane1Position;
        }
    }
    onLane2PositionChanged: {
        if(roadLaneTimeout != 1){
            lane2PositionAnimTime = Math.abs(lane2Position - lane2PositionAnim) / 3 * 400;
            lane2PositionAnim = lane2Position;
        }
    }
    onLane3PositionChanged: {
        if(roadLaneTimeout != 1){
            lane3PositionAnimTime = Math.abs(lane3Position - lane3PositionAnim) / 3 * 400;
            lane3PositionAnim = lane3Position;
        }
    }

    onRoadLaneTimeoutChanged: {
        if(roadLaneTimeout == 1){
            lane0PositionAnimTime = Math.abs(0 - lane0PositionAnim) / 3 * 1000;
            lane0PositionAnim = 0;
            lane1PositionAnimTime = Math.abs(0 - lane1PositionAnim) / 3 * 1000;
            lane1PositionAnim = 0;
            lane2PositionAnimTime = Math.abs(0 - lane2PositionAnim) / 3 * 1000;
            lane2PositionAnim = 0;
            lane3PositionAnimTime = Math.abs(0 - lane3PositionAnim) / 3 * 1000;
            lane3PositionAnim = 0;
        }
        else{
            lane0PositionAnimTime = Math.abs(lane0Position - lane0PositionAnim) / 3 * 1000;
            lane0PositionAnim = lane0Position;
            lane1PositionAnimTime = Math.abs(lane1Position - lane1PositionAnim) / 3 * 1000;
            lane1PositionAnim = lane1Position;
            lane2PositionAnimTime = Math.abs(lane2Position - lane2PositionAnim) / 3 * 1000;
            lane2PositionAnim = lane2Position;
            lane3PositionAnimTime = Math.abs(lane3Position - lane3PositionAnim) / 3 * 1000;
            lane3PositionAnim = lane3Position;
        }
    }

    function startRoadLaneAnim(){
        if(digitSpeedAnim == 0) {
            speedLeftVisible = false;
            speedRightVisible = false;
            laneAnimationTimer.stop();
            speedLaneAnimTimer.stop();
        }
        else{
            if((gear == "R") || (adasGearR == true)){
                speedLeftVisible = false;
                speedRightVisible = false;
                laneAnimationTimer.stop();
                speedLaneAnimTimer.stop();
            }
            else{
                if(!laneAnimationTimer.running){
                    laneAnimationTimer.restart();
                }
                if(!speedLaneAnimTimer.running){
                    speedLeftVisible = true;
                    speedRightVisible = true;
                    speedLaneAnimTimer.restart();
                }
            }
        }
    }

    Rectangle{
        x: 0
        y: 0
        width: 300
        height: 300
        color: "transparent"

        Roads {
            id: aDAS3DID
            x:0
            y:0
            height: 740
            width:  740
            visible: true
            digitSpeed: qmlProjectItem.digitSpeed
//            settingCurve0: lane0Position == 0 ? 0.001:lane0Position     //line0车道线曲率
//            settingCurve1: lane1Position == 0 ? 0.001:lane1Position     //line1车道线曲率
//            settingCurve2: lane2Position == 0 ? 0.001:lane2Position     //line2车道线曲率
//            settingCurve3: lane3Position == 0 ? 0.001:lane3Position     //line3车道线曲率

//            settingCurve_HWA: lanePosition_HWA == 0 ? 0.001:lanePosition_HWA     //车道曲率

            settingLane0Type: adasCarRoadLineTypeLeftMost               //line0车道线类型    【0：不显示】【1：虚线】【2：实线】
            settingLane0ColorIndex: adasCarRoadLineColorLeftMost        // line0车道线颜色 【0：无效】【1：黄色】【2：白色】【3：绿色】【4：蓝色】【5：红色】【6：灰色】
            settingLane1Type: adasCarRoadLineTypeLeft
            settingLane1ColorIndex: adasCarRoadLineColorLeft
            settingLane2Type: adasCarRoadLineTypeRight
            settingLane2ColorIndex: adasCarRoadLineColorRight
            settingLane3Type: adasCarRoadLineTypeRightMost
            settingLane3ColorIndex: adasCarRoadLineColorRightMost

            settingCarFrontBottomAlarmGradual1 : bottomAlarmGradual1
            settingCarFrontBottomAlarmGradual2: bottomAlarmGradual2

            settingCarFrontBottomAlarmStartPos: bottomAlarmStartPos    //红色报警区域位置
            settingCarFrontBottomAlarmEnable: adasHWAAebWaring        //红色报警区域显示
            settingCarFrontBottomAlarmEnable_left: adasHWAAebWaring_left         //左报警区域显示
            settingCarFrontBottomAlarmEnable_right : adasHWAAebWaring_right         //右报警区域显示

            /*四条车道线：
                line0   line1   line2   line3
                  |       |       |       |
                  |       |       |       |
                  |       |       |       |
                  |       |       |       |
                  |       |       |       |
                  |       |       |       |
                  |       |       |       |
                  |       |  本车  |       |
            */
        }

    }
    Timer{
        id: laneAnimationTimer
        interval: 10
        running: false
        repeat: true
        onTriggered: {
            aDAS3DID.settingTime = (aDAS3DID.settingTime + 0.5 * roadLaneAnimTimes) % 100;
        }
    }

    Timer{
        id: speedLaneAnimTimer
        interval: 20
        running: false
        repeat: true
        onTriggered: {
            speedLeftZ = speedLeftZ + 5 * roadLaneAnimTimes;
            if(speedLeftZ > 500)
            {
                speedLeftZ = -900;
            }
            speedRightZ = speedRightZ + 5 * roadLaneAnimTimes;
            if(speedRightZ > 500)
            {
                speedRightZ = -900;
            }
        }
    }
}
