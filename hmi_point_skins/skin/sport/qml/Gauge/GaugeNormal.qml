import QtQuick 2.8
import qmlEnums 1.0
import QtGraphicalEffects 1.0
import "./../Common/"

Item {
    id: gaugeNor
    width: 1920
    height: 720
    opacity:1.0
    property real compFrameLength: 24
    property real compAnim: 0
    property real compIndex: Math.ceil(compAnim)

    property real waterFrameLength: 24
    property real waterAnim: 0
    property real waterIndex: Math.ceil(waterAnim)


    SequentialAnimation{
        running: true
        loops: Animation.Infinite
        //水波纹帧动画
        PropertyAnimation{ id: animationWate; target: gaugeNor; property: "waterAnim"; from: 0; to: compFrameLength; duration: 500 }
        //表盘帧动画
        PropertyAnimation{ id: animationComp; target: gaugeNor; property: "compAnim"; from: 0; to: compFrameLength; duration: 500 }

    }
    //入
    SequentialAnimation{
        id:bottomlineIn
        PropertyAnimation{target: speeditemMask; property: "height"; from: 513; to: 0;duration: 1000;}
        onStarted: {
            console.log("bottomlineIn")
        }
        onStopped: {
            console.log("bottomlineIn over")
            handleEnterAnimOver();
            speeditemMask.height = 0;
        }
    }
    //出
    SequentialAnimation{
        id:bottomlineOut

        PauseAnimation {duration: 500}
        PropertyAnimation{target: speeditemMask; property: "height"; from: 0; to: 513; duration: 1000;}
        onStarted: {
            console.log("bottomlineOut")
        }
        onStopped: {
            console.log("bottomlineOut over")
            speeditemMask.height = 513;
            if(isThemeSetting){
                outAnimationState = true;
            }
        }
    }
    function pointIn(){
        bottomlineIn.start();
    }
    function pointOut(){
        bottomlineOut.start();
    }
//    Image{
//            id: bottomLineImg
//            visible: true
//            x:0
//            y:615
//            width: 1920
//            height: 105
//            source: "../Gauge/pic_HMI_sport_baseline.png"
//        }

//        Image {
//            id: bottomLeftMask
//            x:0
//            y:615
//            width:791
//            height:105
//            source: "../Gauge/black_bg.png"
//        }

//    OpacityMask{
//        anchors.fill: bottomLeftItem
//        source: bottomLineImg
//        maskSource: bottomLeftItem
//    }

//    Item{
//        id: bottomRightItem
//        anchors.fill: bottomLineImg
//        Image {
//            id: bottomRightMask
//            y: -100
//            source: "../Gauge/maskBg1.png"
//        }
//    }

    //表盘背景
    Image {
        id: compImage
        source: "../Gauge/dialFrame/Comp 1_000" + ( compIndex < 10 ? "0" + compIndex : compIndex) + ".png"
    }

    //水波纹背景
    Image{
        id: waterImage
        source: "../Gauge/dialFrame/water_000" + ( waterIndex < 10 ? "0" + waterIndex : waterIndex ) + ".png"
    }


    CustomImage{
        x:1167
        y:172
        source:"pic_HMI_sport_dialhighlight.png"
    }

    CustomImage {
        x:1238
        y:280
        source: "pic_HMI_sport_dialhighlight_2.png"
    }

    CustomImage {
        x:1217
        y:255
        source: "pic_HMI_sport_dialpoint.png"
    }

    property real start_Angle: 135
    property real speed_radius: 280
    //车速表盘
    Item{
        id:v_speed
        anchors.fill: parent

        CustomShape{
            radius: speed_radius
            startAngle: start_Angle
            curAngle:  digitSpeedAnim_dial / 240 * 270
            headlightSrc: "../Gauge/highlight.png"
        }
//        Image{
//            id: imgArea2
//            x: 719
//            y: 473
//            source: "../Gauge/pointer.png"
//            transform: Rotation{
//                angle: digitSpeedAnim_dial / 240 * 270 + start_Angle
//                axis.x : 0
//                axis.y : 0
//                axis.z : 1
//                origin.y : 384
//            }
//        }
    }

    Item{
        id:speeditem
        anchors.fill: parent

        //车速
        CustomText{
            y: 139
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 110
            color: "#bbb39c"
            visible: txtSpeed === "--"
            text: txtSpeed

        }
        Row{
            id: numRow
            visible: txtSpeed !== "--"
            spacing: 10
            anchors.top: parent.top
            anchors.margins: 326
            anchors.horizontalCenter: parent.horizontalCenter
            //百位
            Image{
                visible: digitSpeedAnim >= 100
                source: Math.floor(digitSpeedAnim / 100) + ".png"
            }
            //十位
            Image{
                visible: digitSpeedAnim >= 10
                source: Math.floor(digitSpeedAnim / 10 % 10) + ".png"
            }
            //个位
            Image{
                source: Math.floor(digitSpeedAnim % 10) + ".png"
            }
        }

        CustomText{
            anchors.horizontalCenter: parent.horizontalCenter
            y: 424
            font.pixelSize: 40
            text: "km/h"
            color: "#E3E3E3"
        }
    }
    Image {
        id: speeditemMask
        x:685
        y:129
        width:573
        height:0
        source: "../Gauge/black_bg.png"
    }
}
