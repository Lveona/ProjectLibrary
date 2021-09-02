import QtQuick 2.8
import qmlEnums 1.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0
import QtQuick.Shapes 1.15 //放在 import QtGraphicalEffects 1.0 下面
import "./../Common/"

Item {

    //车速圆心
    property real speed_centerX: 824
    property real speed_centerY: 180
    property real speed_radius: 876
    property real start_Angle: 107.5
    //功率圆心
    property real power_centerX: 1092
    property real power_centerY: 180
    property real power_radius: 876
    property real power_startAngle: 61

    Component.onCompleted: {
//        console.log("===============")
        speedDiaAnimStart();
        powerDiaAnimStart();
        numberAnimStart();
    }

    Item{
        id: numItem
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
            anchors.margins: 153
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
            y: 251
            font.pixelSize: 40
            text: "km/h"
            color: "#E3E3E3"
        }

        //数字入场动效
        SequentialAnimation{
            id:numberAnim_Start
            NumberAnimation { target: numItem; properties: "opacity"; duration: 500; from: 0.0; to: 1.0}
            onStopped: {
                handleEnterAnimOver();
            }
        }

        //数字出场动效
        SequentialAnimation{
            id:numberAnim_End
            NumberAnimation { target: numItem; properties: "opacity"; duration: 500; from: 1.0; to: 0.0}

            PauseAnimation {
                duration: 2000
            }
            onStopped:{
                if(isThemeSetting){
                    outAnimationState = true;
                }
                pointNaiVisible = false;
            }
        }
    }

    //数字入场动效
    function numberAnimStart(){
        pointNaiVisible = true;
        numberAnim_Start.start();
    }

    //数字入场动效停止
    function numberAnimStart_Stop(){
        numberAnim_Start.complete();
    }

    //数字出场动效
    function numberAnimEnd(){
        numberAnim_End.start();
    }

    //数字出场动效停止
    function numberAnimEnd_Stop(){
        numberAnim_End.complete();
    }

/**********************************************************************************************************************/
    property var point1: Qt.point(676, 662)
    property var point2: Qt.point(674 - 70, 662 + 139)
    property var point3: Qt.point(25, 575)
    property var point4: Qt.point(117, 385)
    property var maxValue: 240

    Item{
        id: speedDialItem
        width: 1920
        height: 720
        visible: false
        Image { // 车速底图
            id: speedBg
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            source: ("pic_HMI_classic_default_speeddial_base.png");
            Image{
                x: 51
                y: 9
                source: "pic_HMI_classic_default_speeddial_number.png"
            }
        }

        CustomShape{
	    id: speedShape
            point1: Qt.point(676, 662)
            point2: Qt.point(674 - 70, 662 + 139)
            point3: Qt.point(25, 575)
            point4: Qt.point(117, 385)
            headlightSrc: "../Gauge/pic_HMI_classic_default_speeddial_highlight.png"
            headlightY: 433
            curValue: digitSpeedAnim_dial
            maxValue: 240
        }

        CustomPointer{
            pointerRotate: 118
            pointerSrc: "../Gauge/pic_HMI_classic_default_speeddial_pointer.png"
            maskSrc: "../Gauge/pic_HMI_classic_default_speeddial_mask.png"
            pointerY: 672
            pointerX: 412 - (digitSpeedAnim_dial / 240 * 692)
        }
    }

    //转速表入场动效
    SequentialAnimation{
        id: speedDiaAnim_Start
        ParallelAnimation{
            PropertyAnimation{target: speedDiaVisibleAreaimg; property: "x"; from: speedDiaVisibleAreaimg.width; to: -40; duration: 1000; easing.type: Easing.Linear;}
        }
    }

    //转速表出场动画
    SequentialAnimation{
        id: speedDiaAnim_End
        ParallelAnimation{
            PropertyAnimation{target: speedDiaVisibleAreaimg; property: "x"; from: -40; to: speedDiaVisibleAreaimg.width; duration: 1000; easing.type: Easing.Linear;}
        }
    }

    //转速表入场动效
    function speedDiaAnimStart(){
        pointNaiVisible = true
        speedDiaAnim_Start.start()
    }

    //转速表入场动效停止
    function speedDiaAnimStart_Stop(){
        speedDiaAnim_Start.complete()
    }

    //转速表出场动效
    function speedDiaAnimEnd(){
        speedDiaAnim_End.start()
    }

    //转速表出场动效停止
    function speedDiaAnimEnd_Stop(){
        speedDiaAnim_End.complete()
    }

    Item{
        id: speedDiaVisibleItem
        width: speedDialItem.width
        height: speedDialItem.height
        visible: false

        Image{
            id: speedDiaVisibleAreaimg
            y: 420
            source: "maskBg1.png"
            width: sourceSize.width
            height: sourceSize.height
        }
    }

    OpacityMask{
        anchors.fill: speedDialItem
        source: speedDialItem
        maskSource: speedDiaVisibleItem
    }

/** *******************************************************************************************************************/




    Item{
        id: powerDialItem
        width: 1920
        height: 720
        visible: false

        Image { // 功率底图
            id: powerBg
            y: 442
            anchors.right: parent.right
            source: ("pic_HMI_classic_default_powerdiall_base.png");
            Image{
                x: 11
                y: 36
                source: "pic_HMI_classic_default_powerdial_number.png"
            }
        }

        CustomShape{//功率 -100 ~ 0
            point1: Qt.point(1396, 495)
            point2: Qt.point(1525, 720)
            point3: Qt.point(1207 + 132, 601 + 222)
            point4: Qt.point(1207, 601)
            headlightSrc: "../Gauge/pic_HMI_classic_default_powerdial_highlight2.png"
            headlightX: 1238
            headlightY: 610
            curValue: powerAnim < 0 ? powerAnim: 0
            maxValue: -100
        }

        CustomShape{//功率 0 ~ 100
	    id: powerShape
            point1: Qt.point(1396, 495)
            point2: Qt.point(1522, 719)
            point3: Qt.point(1870, 536)
            point4: Qt.point(1724, 303)
            headlightSrc: "../Gauge/pic_HMI_classic_default_powerdial_highlight.png"
            curValue: powerAnim >= 0 ? powerAnim: 0
            headlightX: 1447
            headlightY: 439
            maxValue: 100
        }

        CustomPointer{
            pointerRotate: 67
            maskX: 1920 - 789
            pointerSrc: "../Gauge/pic_HMI_classic_default_speeddial_pointer.png"
            maskSrc:    "../Gauge/pic_HMI_classic_default_powerdial_mask.png"
            pointerY: 672
            pointerX: 1231 + (powerAnim / 100 * (powerAnim < 0 ? 218 : 452))
        }
    }


    //功率表入场动效
    SequentialAnimation{
        id: powerDiaAnim_Start
        ParallelAnimation{
            PropertyAnimation{target: powerDiaVisibleAreaimg; property: "x"; from: 1920 - powerDiaVisibleAreaimg.width * 2; to: 1920 - powerDiaVisibleAreaimg.width + 40; duration: 1000; easing.type: Easing.Linear;}
        }
    }

    //功率表出场动效
    SequentialAnimation{
        id: powerDiaAnim_End
        ParallelAnimation{
            PropertyAnimation{target: powerDiaVisibleAreaimg; property: "x"; from: 1920 - powerDiaVisibleAreaimg.width + 40; to: 1920 - powerDiaVisibleAreaimg.width * 2; duration: 1000; easing.type: Easing.Linear;}
        }
    }

    //功率表入场动效
    function powerDiaAnimStart(){
        pointNaiVisible = true
        powerDiaAnim_Start.start()
    }

    //功率表入场动效停止
    function powerDiaAnimStart_Stop(){
        powerDiaAnim_Start.complete()
    }

    //功率表出场动效
    function powerDiaAnimEnd(){
        powerDiaAnim_End.start()
    }

    //功率表出场动效停止
    function powerDiaAnimEnd_Stop(){
        powerDiaAnim_End.complete()
    }

    Item{
        id: powerDiavisibleItem
        width: powerDialItem.width
        height: powerDialItem.height
        visible: false

        Image{
            id: powerDiaVisibleAreaimg
            y: 420
            source: "maskBg1.png"
            width: sourceSize.width
            height: sourceSize.height
        }
    }

    OpacityMask{
        anchors.fill: powerDialItem
        source: powerDialItem
        maskSource: powerDiavisibleItem
    }

}
