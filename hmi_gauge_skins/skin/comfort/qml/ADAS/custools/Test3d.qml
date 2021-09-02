import QtQuick 2.15
import QtQuick.Window 2.0
//import QtQuick.Controls 2.0
import QtQuick3D 1.15
import "./../"
Item {
    id:main
    visible: true
    width: 740
    height: 720
    x: 0
//    title: qsTr("Neusoft 3D ADAS Application")
//    color: "#000066"

    // temporal property
    property double lane0Position: slider_curvature.value
    property double lane1Position: slider_curvature1.value
    property double lane2Position: slider_curvature2.value
    property double lane3Position: slider_curvature3.value

    property int adasCarRoadLineTypeLeft: slider_lane_left_type.value
    property int adasCarRoadLineColorLeft: slider_lane_left_color.value
    property int adasCarRoadLineTypeRight: slider_lane_right_type.value
    property int adasCarRoadLineColorRight: slider_lane_right_color.value
    property int adasCarRoadLineTypeLeftMost: slider_lane_left_most_type.value
    property int adasCarRoadLineColorLeftMost: slider_lane_left_most_color.value
    property int adasCarRoadLineTypeRightMost: slider_lane_right_most_type.value
    property int adasCarRoadLineColorRightMost: slider_lane_right_most_color.value

    property real leftObstaclePosX:   slider_car_left_x.value
    property real leftObstaclePosY:   slider_car_left_z.value
    property int  adasLeftObstacle:   slider_car_left_type.value

    property real cIPVObstaclePosX:   slider_car_front_x.value
    property real cIPVObstaclePosY:   slider_car_front_z.value
    property int  adasCipvObstacle:   slider_car_front_type.value

    property real rightObstaclePosX:  slider_car_right_x.value
    property real rightObstaclePosY:  slider_car_right_z.value
    property int  adasRightObstacle:  slider_car_right_type.value

    property bool adasMidRoadCarVisible:  switch_front_indicator.position === 0  //ADASScreen.midRoadCarVisible
    property bool adasLeftRoadCarVisible: switch_left_indicator.position === 0  //ADASScreen.leftRoadCarVisible
    property bool adasRightRoadCarVisible:switch_right_indicator.position === 0 //ADASScreen.rightRoadCarVisible

    property int frontCarAtLeftRoad : 0//ADASScreen.frontCarAtLeftRoad
    property int frontCarAtRightRoad: 0//ADASScreen.frontCarAtRightRoad
    property int adasVSTDistance    : 0//ADASScreen.adasVSTDistance             //Following distance, not used
    property int vehicleSmallColor  : 0//slider_front_indicator_color.value//ADASScreen.vehicleSmallColor      //side car color【0：Do not show】【1：gray】【2：blue】【3：yellow】

    property bool     hoodSts      : false//PopupScreen.popupDataObject.hood    //Car front cover status 【false：close】【true：open】
    property bool     flDoorSts    : false//PopupScreen.popupDataObject.flDoor  //Front left door status 【false：close】【true：open】
    property bool     frDoorSts    : false//PopupScreen.popupDataObject.frDoor  //Front right door status 【false：close】【true：open】
    property bool     rlDoorSts    : false//PopupScreen.popupDataObject.rlDoor  //Rear left door status 【false：close】【true：open】
    property bool     rrDoorSts    : false//PopupScreen.popupDataObject.rrDoor  //Rear right door status 【false：close】【true：open】

    property int digitSpeed: slider_digit_speed.value

    property string ldwWarningLine  : ""    //ADASScreen.ldwWarningLine      //Lane departure waring【"warningRight"：Slef car deviates to the right】【"warningLeft"：Slef car deviates to the left】【else：No deviation】

    property int    roadLaneTimeout: 0//ADASScreen.RoadLaneTimeout     //Lane line curvature signal status【0：All lane lines are straight】【1：Processing according to signal value】

    property real   lane0C0LanePosition: 0//ADASScreen.Lane0C0LanePosition             //lane0_C0 singal. value:-20.8 ~ 20.47, unit:m
    property real   lane0C1HeadingAngle: 0//ADASScreen.Lane0C1HeadingAngle             //lane0_C1 singal. value:-0.357 ~ 0.357, unit:rad
    property real   lane0C2LaneCurvature: 0//ADASScreen.Lane0C2LaneCurvature           //lane0_C2 singal. value:-0.032768 ~ 0.032767, unit:1/m
    property real   lane0C3LaneCurvatureDriv: 0//ADASScreen.Lane0C3LaneCurvatureDriv   //lane0_C3 singal. value:-0.000131072 ~ 0.000131068, unit:1/m2

    property real   lane1C0LanePosition: 0//ADASScreen.Lane1C0LanePosition             //lane1_C0 singal. value:-20.8 ~ 20.47, unit:m
    property real   lane1C1HeadingAngle: 0//ADASScreen.Lane1C1HeadingAngle             //lane1_C1 singal. value:-0.357 ~ 0.357, unit:rad
    property real   lane1C2LaneCurvature: 0//ADASScreen.Lane1C2LaneCurvature           //lane1_C2 singal. value:-0.032768 ~ 0.032767, unit:1/m
    property real   lane1C3LaneCurvatureDriv: 0//ADASScreen.Lane1C3LaneCurvatureDriv   //lane1_C3 singal. value:-0.000131072 ~ 0.000131068, unit:1/m2

    property real   lane2C0LanePosition: 0//ADASScreen.Lane2C0LanePosition             //lane2_C0 singal. value:-20.8 ~ 20.47, unit:m
    property real   lane2C1HeadingAngle: 0//ADASScreen.Lane2C1HeadingAngle             //lane2_C1 singal. value:-0.357 ~ 0.357, unit:rad
    property real   lane2C2LaneCurvature: 0//ADASScreen.Lane2C2LaneCurvature           //lane2_C2 singal. value:-0.032768 ~ 0.032767, unit:1/m
    property real   lane2C3LaneCurvatureDriv: 0//ADASScreen.Lane2C3LaneCurvatureDriv   //lane2_C3 singal. value:-0.000131072 ~ 0.000131068, unit:1/m2

    property real   lane3C0LanePosition: 0//ADASScreen.Lane3C0LanePosition             //lane3_C0 singal. value:-20.8 ~ 20.47, unit:m
    property real   lane3C1HeadingAngle: 0//ADASScreen.Lane3C1HeadingAngle             //lane3_C1 singal. value:-0.357 ~ 0.357, unit:rad
    property real   lane3C2LaneCurvature: 0//ADASScreen.Lane3C2LaneCurvature           //lane3_C2 singal. value:-0.032768 ~ 0.032767, unit:1/m
    property real   lane3C3LaneCurvatureDriv: 0//ADASScreen.Lane3C3LaneCurvatureDriv   //lane3_C3 singal. value:-0.000131072 ~ 0.000131068, unit:1/m2


    property string gear: ""
    property real adasHWAAebWaring: checkbox_bottom_alarm_enable.checkState == Qt.Checked
    property real adasHWAAebWaring_left: checkbox_bottom_alarm_enable_left.checkState == Qt.Checked
    property real adasHWAAebWaring_right: checkbox_bottom_alarm_enable_rigth.checkState == Qt.Checked
    property real bottomAlarmStartPos: slider_bottom_alarm_opacity.value

    property real bottomAlarmGradual1: slider_bottom_alarm_opacity_Gradua1.value
    property real bottomAlarmGradual2: slider_bottom_alarm_opacity_Gradua2.value
    property var count: 1


    property var carPosX: [leftObstaclePosX, cIPVObstaclePosX, rightObstaclePosX]
    property var carPosZ: [leftObstaclePosY, cIPVObstaclePosY, rightObstaclePosY]
    property var carType: [adasLeftObstacle, adasCipvObstacle, adasRightObstacle]

//    Column{
//        TextField{
//            id: tf
//            width: 50
//            height: 20
//            onTextChanged: {
//                console.log("====",text)
//            }
//        }

//        TestSlider{
//            label: "X "
//            s: 32
//            e: -32
//            onVc: {
//                if(v === "1"){
//                    leftObstaclePosX = v
//                }else if (v === "2"){
//                    cIPVObstaclePosX = v
//                }else if(v === "3"){
//                    rightObstaclePosX = v
//                }
//            }
//        }
//        TestSlider{
//            label: "Z "
//            s: -256
//            e: 256
//            onVc: {
//                if(v === "1"){
//                    leftObstaclePosY = v
//                }else if (v === "2"){
//                    cIPVObstaclePosY = v
//                }else if(v === "3"){
//                    rightObstaclePosY = v
//                }
//            }
//        }
//        TestSlider{
//            label: "type "
//            s: 0
//            e: 4
//            onVc: {
//                if(v === "1"){
//                    adasLeftObstacle = v
//                }else if (v === "2"){
//                    adasCipvObstacle = v
//                }else if(v === "3"){
//                    adasRightObstacle = v
//                }
//            }
//        }
//        Switch {
//            text: qsTr("")
////            onPositionChanged:
//        }
//    }

    //Car
    Item{
        id: car3d
        width: 740
        height: 720
        x: 0
        y: 0
        Row {
            spacing: 50
            Column{
                id: c1
                spacing: 5
                Text {
                    id: text_car_left
                    width: 200
                    height: 93
                    text: qsTr("LeftCar \n -x \n -z \n -opacity")
                    font.pixelSize: 12
                    color: "white"
                }

                Slider {
                    id: slider_car_left_x
                    value: -4
                    to: 32
                    from: -32
                    onValueChanged: {console.log(" slider_car_left_x: "+value)}
                }

                Slider {
                    id: slider_car_left_z
                    value: 0
                    to: -256
                    from: 256
                    onValueChanged: {console.log(" slider_car_left_z: "+value)}
                }
                Slider {
                    id: slider_car_left_type
                    from: 0
                    to: 4
                    value: 2
                    stepSize: 1
                    onValueChanged: {console.log(" slider_car_left_type: "+value)}
                }

                Slider {
                    id: slider_car_left_opacity
                    value: 1.0
                    to: 1.0
                    from: 0.0
                    onValueChanged: {console.log(" slider_car_left_opacity: "+value)}
                }
                Row{
                    spacing: 20

                    Switch {
                        id: switch_left_indicator
                        text: qsTr("")
                    }

                    Slider {
                        id: slider_left_indicator_color
                        width: 112
                        height: 40
                        from: 0
                        value: 0
                        to: 2
                        stepSize: 1
                        onValueChanged: {console.log(" slider_left_indicator_color: "+value)}
                    }
                }
            }
            Column{
                spacing: 5
                Text {
                    id: text_car_front
                    width: 200
                    height: 93
                    text: qsTr("FrontCar \n -x \n -z \n -indicator\n- opacity")
                    font.pixelSize: 12
                    color: "white"
                }

                Slider {
                    id: slider_car_front_x
                    value: 0
                    to: 32
                    from: -32
                    onValueChanged: {console.log(" slider_car_front_x: "+value)}
                }

                Slider {
                    id: slider_car_front_z
                    value: 0
                    to: -256
                    from: 256
                    onValueChanged: {console.log(" slider_car_front_z: "+value)}
                }
                Slider {
                    id: slider_car_front_type
                    from: 0
                    to: 4
                    value: 2
                    stepSize: 1
                    onValueChanged: {console.log(" slider_car_front_type: "+value)}
                }
                Slider {
                    id: slider_car_front_opacity
                    value: 1.0
                    from: 0.0
                    to: 1.0
                    onValueChanged: {console.log(" slider_car_front_opacity: "+value)}
                }
                Row{
                    spacing: 20
                    Switch {
                        id: switch_front_indicator
                        text: qsTr("")
                    }
                    Slider {
                        id: slider_front_indicator_color
                        width: 112
                        height: 40
                        value: 2
                        from: 0
                        to: 4
                        stepSize: 1
                        onValueChanged: {console.log(" slider_front_indicator_color: "+value)}
                    }

                }
            }
            Column{
                spacing: 5
                Text {
                    id: text_car_right
                    width: 200
                    height: 93
                    text: qsTr("RightCar \n -x \n -z \n - opacity")
                    font.pixelSize: 12
                    color: "white"
                }

                Slider {
                    id: slider_car_right_x
                    value: 4
                    to: 32
                    from: -32
                    onValueChanged: {console.log(" slider_car_right_x: "+value)}
                }

                Slider {
                    id: slider_car_right_z
                    value: 0
                    to: -256
                    from: 256
                    onValueChanged: {console.log(" slider_car_right_z: "+value)}
                }
                Slider {
                    id: slider_car_right_type
                    from: 0
                    to: 4
                    value: 2
                    stepSize: 1
                    onValueChanged: {console.log(" slider_car_right_type: "+value)}
                }
                Slider {
                    id: slider_car_right_opacity
                    from: 0.0
                    value: 1.0
                    to: 1.0
                    onValueChanged: {console.log(" slider_car_right_opacity: "+value)}
                }
                Row{
                    spacing: 20

                    Switch {
                        id: switch_right_indicator
                        text: qsTr("")
                    }

                    Slider {
                        id: slider_right_indicator_color
                        width: 112
                        height: 40
                        from: 0
                        value: 0
                        to: 2
                        stepSize: 1
                        onValueChanged: {console.log(" slider_right_indicator_color: "+value)}
                    }
                }
            }
        }
    }

    //Curvature
    Item{
        height: parent.height
        id: roadCurvature
        anchors.right: parent.right
//        anchors.left: car3d.right
        Text {
            id: text_road
            width: 200
            height: 93
            text: qsTr("Road\n- digitSpeed 0 ~ 220\n- curvature")
            font.pixelSize: 12
            color: "white"
        }

        CheckBox {
            anchors.top: text_road.bottom
            id: checkbox_lane_luminous
        }
        Column{
            anchors.top: checkbox_lane_luminous.bottom
            spacing: 5
            Slider {
                id: slider_digit_speed
                from: 0
                to: 220
                value: 0
                stepSize: 1
                onValueChanged: {console.log(" slider_digit_speed: "+value)}
            }

            Slider {
                id: slider_curvature
                value: 0
                from: -3
                to: 3
                onValueChanged: {console.log(" slider_curvature: "+value)}
            }

            Slider {
                id: slider_curvature1
                value: 0
                to: 3
                from: -3
                onValueChanged: {console.log(" slider_curvature1: "+value)}
            }

            Slider {
                id: slider_curvature2
                value: 0
                to: 3
                from: -3
                onValueChanged: {console.log(" slider_curvature2: "+value)}
            }

            Slider {
                id: slider_curvature3
                value: 0
                to: 3
                from: -3
                onValueChanged: {console.log(" slider_curvature3: "+value)}
            }
        }
    }


    Text {
        id: element
        anchors.bottom: lineRow.top
        anchors.left: lineRow.left
        width: 406
        height: 26
        color: "#ffffff"
        text: qsTr("Lane Type             Lane Color")
        font.pixelSize: 20
    }

    Text {
        id: element1
        anchors.right: lineRow.left
        anchors.verticalCenter: lineRow.verticalCenter
        width: 97
        height: 171
        color: "#ffffff"
        text: qsTr("Lane 0\n\nLane 1\n\nLane 2\n\nLane 3\n\n")
        font.pixelSize: 20
    }
    Row{
        id: lineRow
        x: 1180
        y: 480
        spacing: 20
        //line type
        Column{
            spacing: 5
            Slider {
                id: slider_lane_left_most_type
                from: 0
                to: 2
                value: 1
                stepSize: 1
                onValueChanged: {console.log(" slider_lane_left_most_type: "+value)}
            }

            Slider {
                id: slider_lane_left_type
                from: 0
                to: 2
                value: 1
                stepSize: 1
                onValueChanged: {console.log(" slider_lane_left_type: "+value)}
            }

            Slider {
                id: slider_lane_right_type
                from: 0
                to: 2
                value: 1
                stepSize: 1
                onValueChanged: {console.log(" slider_lane_right_type: "+value)}
            }

            Slider {
                id: slider_lane_right_most_type
                from: 0
                to: 2
                value: 1
                stepSize: 1
                onValueChanged: {console.log(" slider_lane_right_most_type: "+value)}
            }
        }

        //line color
        Column{
            spacing: 5
            Slider {
                id: slider_lane_left_most_color
                from: 1
                to: 6
                value: 6
                stepSize: 1
                onValueChanged: {console.log(" slider_lane_left_most_color: "+value)}
            }

            Slider {
                id: slider_lane_left_color
                from: 1
                to: 6
                value: 1
                stepSize: 1
                onValueChanged: {console.log(" slider_lane_left_color: "+value)}
            }

            Slider {
                id: slider_lane_right_color
                from: 1
                to: 6
                value: 1
                stepSize: 1
                onValueChanged: {console.log(" slider_lane_right_color: "+value)}
            }

            Slider {
                id: slider_lane_right_most_color
                from: 1
                to: 6
                value: 6
                stepSize: 1
                onValueChanged: {console.log(" slider_lane_right_most_color: "+value)}
            }
        }

    }

    Column{
        spacing: 10
        x:20
        y:400

        Text {
            id: element2
            width: 239
            height: 40
            color: "#ffffff"
            text: qsTr("Bottom alarm opacity Left")
            font.pixelSize: 22
        }
        Text {
            id: element2_Left
            width: 239
            height: 40
            color: "#ffffff"
            text: qsTr("Bottom alarm opacity")
            font.pixelSize: 22
        }

        Text {
            id: element2_Right
            width: 239
            height: 40
            color: "#ffffff"
            text: qsTr("Bottom alarm opacity Right")
            font.pixelSize: 22
        }
        }

    Column{
        spacing: 10
        x:300
        y:395
        CheckBox {
            id: checkbox_bottom_alarm_enable_left
        }
        CheckBox {
            id: checkbox_bottom_alarm_enable
        }
        CheckBox {
            id: checkbox_bottom_alarm_enable_rigth
        }
    }

    Slider {
        id: slider_bottom_alarm_opacity
        x: 340
        y: 445
        value: 0.5
        from: 0.0
        to: 1.0
        onValueChanged: {console.log(" slider_bottom_alarm_opacity: "+value)}
    }

    //渐变参数滑块1
    Slider {
        id: slider_bottom_alarm_opacity_Gradua1
        x: 340
        y: 495
        value: 0.0
        from: 0.0
        to: 1.0
        onValueChanged: {console.log(" slider_bottom_alarm_opacity_Gradua1: "+value)}
    }

    //渐变参数滑块2
    Slider {
        id: slider_bottom_alarm_opacity_Gradua2
        x: 540
        y: 495
        value: 1.0
        from: 0.0
        to: 1.0
        onValueChanged: {console.log(" slider_bottom_alarm_opacity_Gradua2: "+value)}
    }

    Text {
        id: element3
        x: 20
        y: 550
        width: 213
        height: 48
        color: "#ffffff"
        text: qsTr("Left lane alarm opacity")
        font.pixelSize: 20
    }

    Text {
        id: element4
        x: 20
        y: 600
        width: 213
        height: 48
        color: "#ffffff"
        text: qsTr("Right lane alarm opacity")
        font.pixelSize: 20
    }

    Slider {
        id: slider_left_lane_alarm_opacity
        x: 318
        y: 540
        value: 0.0
        from: 0.0
        to: 1.0
        onValueChanged: {console.log(" slider_left_lane_alarm_opacity: "+value)}
    }

    Slider {
        id: slider_right_lane_alarm_opacity
        x: 318
        y: 590
        value: 0.0
        from: 0.0
        to: 1.0
        onValueChanged: {console.log(" slider_right_lane_alarm_opacity: "+value)}
    }


//        Button {
//            id: button
//            x: 177
//            y: 623
//            text: qsTr("warningRight")
//            onClicked: {
//                ldwWarningLine = "warningRight"
//            }
//        }

//        Button {
//            id: button1
//            x: 43
//            y: 623
//            text: qsTr("warningLeft")
//            onClicked: {
//                ldwWarningLine = "warningLeft"
//            }
//        }

//        Button {
//            id: button2
//            x: 307
//            y: 623
//            text: qsTr("noWarning")
//            onClicked: {
//                ldwWarningLine = ""
//            }
//        }

//        Button {
//            id: button3
//            x: 437
//            y: 623
//            text: qsTr("gear")
//            onClicked: {
//                if(gear == "R"){
//                    gear = "";
//                }
//                else{
//                    gear = "R";
//                }
//                console.log(" gear: "+gear)
//            }
//        }

//        Adas3D{}

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.100000023841858}
}
##^##*/
