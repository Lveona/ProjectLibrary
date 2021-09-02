import QtQuick 2.8
import qmlEnums 1.0
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


    Item{
        anchors.fill: parent
        //visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
        //车速
        CustomText{
            y: 139
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 110
            color: "#bbb39c"
            visible: txtSpeed === "--"//txtSpeed.text === "--"
            text: txtSpeed//"0"

        }
        Row{
            id: numRow
            visible: txtSpeed !== "--"//txtSpeed.text !== "--"
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
    }


/**********************************************************************************************************************/
    Item{
        id: speedDialItem
        width: 1920
        height: 720
        Image { // 车速底图
            id: speedBg
            anchors.left: speedDialItem.left
            anchors.leftMargin: 3
            anchors.top: speedDialItem.top
            anchors.topMargin: 471
            source: ("pic_HMI_classic_default_speeddial_base.png");
            Image{
                x: 64
                y: 17
                source: "pic_HMI_classic_default_speeddial_number.png"
            }
        }
        //圆心
//        property real speed_centerX: 824
//        property real speed_centerY: 180
//        property real speed_radius: 876
//        property real start_Angle: 107.5

        //偏移： -73 -603
        CustomShape{
            id: speedShape
            center_x: speed_centerX
            center_y: speed_centerY
            width: speed_radius * 2
            height: width
            radius: speed_radius
            headlightY: 479
            headlightX: 33
            startAngle: start_Angle
            curAngle:  digitSpeedAnim_dial < 40 ? 0.563 * digitSpeedAnim_dial : 8.46 * Math.log(digitSpeedAnim_dial - 24.69) - 0.42  //digitSpeedAnim > 120 ? (partB_Angle / 120 * (digitSpeedAnim - 120) + partA_Angle) : (partA_Angle / 120 * digitSpeedAnim)
            headlightSrc: "../Gauge/pic_HMI_classic_default_speeddial_highlight.png"
        }

        CustomPointer{
            radius: 1000
            center_x: speed_centerX
            center_y: speed_centerY
            visibleArea_y: 408
            pointerOffset_x: 400
            startAngle: start_Angle
            curAngle: digitSpeedAnim_dial < 40 ? 0.563 * digitSpeedAnim_dial : 8.46 * Math.log(digitSpeedAnim_dial - 24.69) - 0.42//digitSpeedAnim > 120 ? (partB_Angle / 120 * (digitSpeedAnim - 120) + partA_Angle) : (partA_Angle / 120 * digitSpeedAnim)
            pointerSrc: "../Gauge/pic_HMI_classic_default_speeddial_pointer.png"
            maskSrc: "../Gauge/pic_HMI_classic_default_speeddial_mask.png"
        }
    }


/** *******************************************************************************************************************/




    Item{
        id: powerDialItem
        width: 1920
        height: 720
//        //圆心
//        property real power_centerX: 1092
//        property real power_centerY: 180
//        property real power_radius: 876
//        property real power_startAngle: 61

        Image { // 功率底图
            id: powerBg
            y: 434
            anchors.right: parent.right
            source: ("pic_HMI_classic_default_powerdiall_base.png");
            Image{
                x: 137
                y: 85
                source: "pic_HMI_classic_default_powerdial_number.png"
            }
        }

        CustomShape{//功率 -100 ~ 0
            center_x: power_centerX
            center_y: power_centerY
            width: power_radius*2
            height: width
            radius: power_radius
            startAngle: power_startAngle
            curAngle: Math.abs((powerAnim < 0 ? powerAnim: 0) * 0.1125)                       //positive_Angle / 100 * Math.abs(powerAnim < 0 ? powerAnim: 0)//用visible和opacity会有卡顿
            headlightSrc: "../Gauge/pic_HMI_classic_default_powerdial_highlight2.png"
            headlightY: 617
            headlightX: 1223
        }

        CustomShape{//功率 0 ~ 100
            id: powerShape
            center_x: power_centerX
            center_y: power_centerY
            width: power_radius*2
            height: width
            radius: power_radius
            startAngle: power_startAngle
            curAngle: -Math.pow((powerAnim >= 0 ? powerAnim : 0), 0.7) * 1.34         //-negative_Angle / 100 * (powerAnim >= 0 ? powerAnim : 0)
            headlightSrc: "../Gauge/pic_HMI_classic_default_powerdial_highlight.png"
            headlightY: 502
            headlightX: 1254
        }

        CustomPointer{
            radius: power_radius
            center_x: power_centerX
            center_y: power_centerY
            visibleArea_x: 1125
            visibleArea_y: 407
            pointerOffset_x: 400
            startAngle: power_startAngle
            curAngle: {
                if(powerAnim < 0){
                    Math.abs(powerAnim * 0.1125)
                }else{
                    -Math.pow(powerAnim, 0.7) * 1.34
                }
                //(powerAnim < 0 ? positive_Angle : -negative_Angle) / 100 * Math.abs(powerAnim)
            }

            pointerSrc: "../Gauge/pic_HMI_classic_default_speeddial_pointer.png"
            maskSrc: "../Gauge/pic_HMI_classic_default_powerdial_mask.png"
        }
    }

}
