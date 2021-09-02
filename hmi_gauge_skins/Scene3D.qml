import QtQuick3D 1.15
import QtQuick 2.15
import QtQuick3D.Materials 1.15
import CacheSetter 1.0
//import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import QtQuick.Shapes 1.15 //放在 import QtGraphicalEffects 1.0 下面
import "./"

View3D {
    id: view3D
    anchors.fill: parent
    width: 1920
    height: 720
    visible: (4 !== updateTitleType) || (0 !== currentChild1Page) ?  false : true

    CacheSetter {   //引入cache
        myView: view3D
    }

    property int currentChild1Page : DiagScreen.currentChild1Page
    property int updateTitleType:   Update_Thread.messageType
    property real scene3DOpacity: 0.0

    property real digitSpeed: SettingScreen.vehicleSpeed//0.0 //车速

    //门开提示
    property var adas3d_DOW_FL: ADASScreen.ADAS_DOW_FL //左前门
    property var adas3d_DOW_FR: ADASScreen.ADAS_DOW_FR //右前门
    property var adas3d_DOW_RL: ADASScreen.ADAS_DOW_RL //左后门
    property var adas3d_DOW_RR: ADASScreen.ADAS_DOW_RR //右后门

    //追尾预警
    property var adas3d_RCW_WARN: ADASScreen.RCW_WARN

    //前碰撞预警
    property var adas3d_FCW_WARN: ADASScreen.FCW_WARN

    //RCTA碰撞提示左后侧
    property var adas3d_RCTA_LEFT_WARN: ADASScreen.RCTA_LEFT_WARN

    //RCTA碰撞提示右后侧
    property var adas3d_RCTA_RIGHT_WARN: ADASScreen.RCTA_RIGHT_WARN

    //BSD盲区检测 左后侧 右后侧
    property var adas3d_LCA_LEFT_WARN: ADASScreen.LCA_LEFT_WARN
    property var adas3d_LCA_RIGHT_WARN: ADASScreen.LCA_RIGHT_WARN

    //FCTA 左前侧 右前侧碰撞提示
    property var fctaLeft:  ADASScreen.fctaLeft
    property var fctaRight: ADASScreen.fctaRight

    //泊车状态标志位
    property var prkgStsIndcr: ADASScreen.prkgStsIndcr

    //左侧泊车位提示
    property var prkgLeSlotTyp1: ADASScreen.prkgLeSlotTyp1
    property var prkgLeSlotTyp2: ADASScreen.prkgLeSlotTyp2
    property var prkgLeSlotTyp3: ADASScreen.prkgLeSlotTyp3

    //右侧泊车位提示
    property var adas3d_PrkgRiSlotTyp1: ADASScreen.PrkgRiSlotTyp1
    property var adas3d_PrkgRiSlotTyp2: ADASScreen.PrkgRiSlotTyp2
    property var adas3d_PrkgRiSlotTyp3: ADASScreen.PrkgRiSlotTyp3

    //泊车距离显示
    property var parkUpDistance:        ADASScreen.parkUpDistance
    property var parkDownDistance:      ADASScreen.parkDownDistance
    property var parkUpDistanceColor:   ADASScreen.parkUpDistanceColor
    property var parkDownDistanceColor: ADASScreen.parkDownDistanceColor
    property var parkLeftDistanceColor: ADASScreen.parkLeftDistanceColor
    property var parkRightistanceColor: ADASScreen.parkRightistanceColor
    property var leftILC: ADASScreen.leftILC
    property var rightILC:ADASScreen.rightILC
    property var leftILCVisible:  ADASScreen.leftILCVisible
    property var rightILCVisible: ADASScreen.rightILCVisible
    property var miniAdasVisible: ADASScreen.miniAdasVisible

    //目标信息
    property var targetList: ADASScreen.getTargetListAll()
    //目标0
    property var targetObj0: targetList[0]
    //目标1
    property var targetObj1: targetList[1]
    //目标2
    property var targetObj2: targetList[2]
    //目标3
    property var targetObj3: targetList[3]
    //目标4
    property var targetObj4: targetList[4]
    //目标5
    property var targetObj5: targetList[5]

//    function cameraYchange(v){
//        camera.y = v
//    }
//    function cameraZchange(v){
//        camera.z = v
//    }
//    function cameraRchange(v){
//        camera.fieldOfView = v
//    }

    environment: SceneEnvironment { //加载HDR（会导致卡顿），以及设置抗锯齿
        //        lightProbe: Texture {
        //            source: "adashdr.hdr"
        //        }
        ////        probeBrightness: 500
        antialiasingMode: SceneEnvironment.SSAA
        antialiasingQuality: SceneEnvironment.VeryHigh
    }

    DirectionalLight { //平行光源
        id: light
        x: 0
        y: 730.889
        color: "#a6a6a6"
        eulerRotation.z: -0.31782
        eulerRotation.y: -0.04799
        z: 890.78333
        eulerRotation.x: -76.64114
        brightness: 70
        ambientColor: "#a6a6a6"
    }

//    Timer{
//        id:adadsadsadda
//        interval: 300
//        //running: true
////        repeat: true
//        onTriggered: {
////            digitSpeed = (digitSpeed + 1) % 240
//            //digitSpeed = 1
//            console.log("当前车速为：",digitSpeed)
//        }
//    }

    Component.onCompleted: {
        ////////////低速摄像机////////////
        camera.y = 0
        camera.z = 90
        camera.eulerRotation.x = 0
        //////////////本车//////////////
        thisCar.scaleX = 0.05
        thisCar.scaleY = 0.05
        thisCar.scaleZ = 0.05
        thisCar.y = -20
        /////////////车道线/////////////
        Manager.changeModelviewMatrixTranslate(-300,-90, -100)
        Manager.changeModelviewMatrixRotate(0)
        Manager.changeProjectMatrix(90, 18)
    }

    //车速变化 镜头
    onDigitSpeedChanged: {
        if(digitSpeed >= 0 && digitSpeed < 10){
            ////////////低速摄像机////////////
            camera.y = 0
            camera.z = 90
            camera.eulerRotation.x = 0
            //////////////本车//////////////
            thisCar.scaleX = 0.05
            thisCar.scaleY = 0.05
            thisCar.scaleZ = 0.05
            thisCar.y = -20
            /////////////车道线/////////////
            Manager.changeModelviewMatrixTranslate(-300,-90, -100)
            Manager.changeModelviewMatrixRotate(0)
            Manager.changeProjectMatrix(90, 18)
        }else if(digitSpeed >= 10 && digitSpeed <= 90){
            ////////////中速摄像机////////////
            camera.y = -135
            camera.z = 74
            camera.eulerRotation.x = 74
            //////////////本车//////////////
            thisCar.scaleX = 0.09
            thisCar.scaleY = 0.09
            thisCar.scaleZ = 0.09
            thisCar.y = -35
            /////////////车道线/////////////
            Manager.changeModelviewMatrixTranslate(-300, -55, 0)
            Manager.changeModelviewMatrixRotate(-69)
            Manager.changeProjectMatrix(90, 18)
        }else{
            ////////////高速摄像机////////////
            camera.y = -100
            camera.z = 27
            camera.eulerRotation.x = 84
            //////////////本车//////////////
            thisCar.scaleX = 0.045
            thisCar.scaleY = 0.045
            thisCar.scaleZ = 0.045
            thisCar.y = -45
            /////////////车道线/////////////
            Manager.changeModelviewMatrixRotate(-85)
            Manager.changeModelviewMatrixTranslate(-300, -55, -82)
            Manager.changeProjectMatrix(90, 12)
        }
    }

    PerspectiveCamera { //摄像头参数
        id: camera
        scale.x:1
        scale.y:1
        scale.z:1
        fieldOfView: 60
        fieldOfViewOrientation: PerspectiveCamera.Vertical
    }

    //本车
    CusNode{
        id: thisCar
        x: 0
        z: 0
        rotationX: 90
        type: 5
        visible: true

        //关门 —— 左前门
        Model {
            id: fl_close
            source: "qrc:/mesh/fl_close.mesh"
            visible: !fl_open.visible
            DefaultMaterial {
                id: defaultMaterial_material_fl_close
            }
            materials: [
                defaultMaterial_material_fl_close
            ]
        }

        //开门 —— 左前门
        Model {
            id: fl_open
            x: -93.1656
            y: 85.511
            z: -93.2513
            eulerRotation.x: -1.72087e-06
            eulerRotation.y: -60
            eulerRotation.z: 5.92359e-06
            source: "qrc:/mesh/fl_open.mesh"
            visible: adas3d_DOW_FL === 1 || adas3d_DOW_FL === 2

            DefaultMaterial {
                id: defaultMaterial_material_fl_open
                diffuseColor: adas3d_DOW_FL === 1 ? "yellow": "red"
            }
            materials: [
                defaultMaterial_material_fl_open
            ]

            SequentialAnimation{
                running: true
                loops: Animation.Infinite
                NumberAnimation {target: fl_open; property: "opacity"; duration: adas3d_DOW_FL === 1 ? 500: 250; to: 0.0; easing.type: Easing.InOutQuad}
                NumberAnimation {target: fl_open; property: "opacity"; duration: adas3d_DOW_FL === 1 ? 500: 250; to: 1.0; easing.type: Easing.InOutQuad}
            }
        }


        //关门 —— 左后门
        Model {
            id: rl_close
            source: "qrc:/mesh/door_rl_close.mesh"
            visible: !rl_open.visible

            DefaultMaterial {
                id: defaultMaterial_material_rl_close
            }

            materials: [
                defaultMaterial_material_rl_close
            ]
        }

        //开门 —— 左后门
        Model{
            id: rl_open
            x: -89.3679
            y: 107.918
            z: 17.8367
            eulerRotation.y: -60
            source: "qrc:/mesh/door_rl_open.mesh"
            visible: adas3d_DOW_RL === 1 || adas3d_DOW_RL === 2

            DefaultMaterial{
                id: defaultMaterial_material_rl_open
                diffuseColor: adas3d_DOW_RL === 1 ? "yellow" : "red"
            }

            materials: [
                defaultMaterial_material_rl_open
            ]

            SequentialAnimation{
                running: true
                loops:Animation.Infinite
                NumberAnimation {target: rl_open; property: "opacity"; duration: adas3d_DOW_RL === 1 ? 500 : 250; to: 0.0; easing.type: Easing.InOutQuad}
                NumberAnimation {target: rl_open; property: "opacity"; duration: adas3d_DOW_RL === 1 ? 500 : 250; to: 1.0; easing.type: Easing.InOutQuad}
            }
        }

        //关门 —— 右前门
        Model {
            id: fr_close
            source: "qrc:/mesh/door_fr_close.mesh"
            visible: !fr_open.visible

            DefaultMaterial {
                id: defaultMaterial_material_fr_close
            }

            materials: [
                defaultMaterial_material_fr_close
            ]
        }

        //开门 —— 右前门
        Model{
            id:fr_open
            x: 90.7888
            y: 102.962
            z: -89.2066
            eulerRotation.y: 60
            source: "qrc:/mesh/door_fr_open.mesh"
            visible: adas3d_DOW_FR === 1 || adas3d_DOW_FR === 2

            DefaultMaterial{
                id: defaultMaterial_material_fr_open
                diffuseColor: adas3d_DOW_FR === 1 ? "yellow" : "red"
            }

            materials: [
                defaultMaterial_material_fr_open
            ]

            SequentialAnimation{
                running: true
                loops: Animation.Infinite
                NumberAnimation { target: fr_open; property: "opacity"; duration: adas3d_DOW_FR === 1 ? 500 : 250; to: 0.0; easing.type: Easing.InOutQuad}
                NumberAnimation { target: fr_open; property: "opacity"; duration: adas3d_DOW_FR === 1 ? 500 : 250; to: 1.0; easing.type: Easing.InOutQuad}
            }
        }

        //关门 —— 右后门
        Model {
            id: rr_close
            source: "qrc:/mesh/door_rr_close.mesh"
            visible: !rr_open.visible

            DefaultMaterial {
                id: defaultMaterial_material_rr_close
            }
            materials: [
                defaultMaterial_material_rr_close
            ]
        }

        //开门 —— 右后门
        Model{
            id:rr_open
            x: 89.3971
            y: 108.926
            z: 20.187
            eulerRotation.x: -9.35595e-06
            eulerRotation.y: 60
            eulerRotation.z: -1.61927e-05
            source: "qrc:/mesh/door_rr_open.mesh"
            visible: adas3d_DOW_RR === 1 || adas3d_DOW_RR === 2

            DefaultMaterial {
                id: defaultMaterial_material_rr_open
                diffuseColor: adas3d_DOW_RR === 1 ? "yellow" : "red"
            }
            materials: [
                defaultMaterial_material_rr_open
            ]

            SequentialAnimation {
                running: true
                loops: Animation.Infinite
                NumberAnimation { target: rr_open; property: "opacity"; duration: adas3d_DOW_RR === 1 ? 500 : 250; to: 0.0; easing.type: Easing.InOutQuad}
                NumberAnimation { target: rr_open; property: "opacity"; duration: adas3d_DOW_RR === 1 ? 500 : 250; to: 1.0; easing.type: Easing.InOutQuad}
            }
        }
    }

    /*——Iamge 转 Model 需要旋转开始测试部分——*/
    /*Column{
        x:1200
        y:10
        spacing: 13

        Label{
            text: "调试eulerRotation.x滑块";font.pixelSize: 15;color: "yellow"
        }
        Slider {
            id: rotationX_Slider
            height: 10
            width: 200
            value: 0
            from: -360
            to: 360
            stepSize : 1
            onValueChanged: {
                console.log(rotationX_Slider.text+":"+value)
                thisCar_RCTA_RIGHT_Mask.eulerRotation.x = value
            }
        }

        Label{
            text: "调试eulerRotation.y滑块";font.pixelSize: 15;color: "yellow"
        }
        Slider {
            id: rotationY_Slider
            height: 10
            width: 200
            value: 0
            from: -180
            to: 180
            stepSize : 1
            onValueChanged: {
                console.log(rotationY_Slider.text+":"+value)
                thisCar_RCTA_RIGHT_Mask.eulerRotation.y = value
            }
        }

        Label{
            text: "调试eulerRotation.z滑块";font.pixelSize: 15;color: "yellow"
        }
        Slider {
            id: rotationZ_Slider
            height: 10
            width: 200
            value: 0
            from: -180
            to: 180
            stepSize : 1
            onValueChanged: {
                console.log(rotationZ_Slider.text+":"+value)
                thisCar_RCTA_RIGHT_Mask.eulerRotation.z = value
            }
        }

        Label{
            text: "调试坐标x滑块";font.pixelSize: 15;color: "yellow"
        }
        Slider {
            id: x_Slider
            height: 10
            width: 200
            value: 0
            from: -180
            to: 180
            stepSize : 1
            onValueChanged: {
                console.log(x_Slider.text+":"+value)
                thisCar_RCTA_RIGHT_Mask.x = value
            }
        }

        Label{
            text: "调试坐标y滑块";font.pixelSize: 15;color: "yellow"
        }
        Slider {
            id: y_Slider
            height: 10
            width: 200
            value: 0
            from: -180
            to: 180
            stepSize : 1
            onValueChanged: {
                console.log(y_Slider.text+":"+value)
                thisCar_RCTA_LEFT_Mask.y = value
            }
        }

        Label{
            text: "调试坐标z滑块";font.pixelSize: 15;color: "yellow"
        }
        Slider {
            id: z_Slider
            height: 10
            width: 200
            value: 0
            from: -180
            to: 180
            stepSize : 1
            onValueChanged: {
                console.log(z_Slider.text+":"+value)
                thisCar_RCTA_RIGHT_Mask.z = value
            }
        }

        Label{
            text: "调试x轴缩放滑块";font.pixelSize: 15;color: "yellow"
        }
        Slider {
            id: scale_x
            height: 10
            width: 200
            value: 0
            from: 0
            to: 10
            stepSize : 0.01
            onValueChanged: {
                console.log(scale_x.text+":"+value)
                thisCar_RCTA_RIGHT_Mask.scale.x = value
            }
        }

        Label{
            text: "调试y轴缩放滑块";font.pixelSize: 15;color: "yellow"
        }
        Slider {
            id: scale_y
            height: 10
            width: 200
            value: 0
            from: 0
            to: 10
            stepSize : 0.01
            onValueChanged: {
                console.log(scale_y.text+":"+value)
                thisCar_RCTA_RIGHT_Mask.scale.y = value
            }
        }

        Label{
            text: "调试z轴缩放滑块";font.pixelSize: 15;color: "yellow"
        }
        Slider {
            id: scale_z
            height: 10
            width: 200
            value: 0
            from: 0
            to: 10
            stepSize : 0.01
            onValueChanged: {
                console.log(scale_z.text+":"+value)
                thisCar_RCTA_RIGHT_Mask.scale.z = value
            }
        }
    }*/
    /*——Iamge 转 Model 需要旋转结束测试部分——*/

    //盲区监测BSD-左侧警告
    CustomMask{
        id: thisCar_BSD_Left
        visible: adas3d_LCA_LEFT_WARN !== 0
        x: -15
        y: -46
        eulerRotation.x: 36
        scale.y: 0.28
        scale.x: 0.28
        scale.z: 0.28
        adasAnim_RightTop_LeftBot: adas3d_LCA_LEFT_WARN

        sourceImage: {
            if(adas3d_LCA_LEFT_WARN === 1){
                "./adas_image/pic_HMI_classic_default_road_BSD_yellow.png"
            }else if(adas3d_LCA_LEFT_WARN === 2){
                "./adas_image/pic_HMI_classic_default_road_BSD_red2.png"
            }else{
                ""
            }
        }
    }

    //盲区监测BSD-右侧警告
    CustomMask{
        id: thisCar_BSD_Right
        visible: adas3d_LCA_RIGHT_WARN !== 0
        x: 15
        y: -46
        eulerRotation.x: 36
        scale.z: 0.28
        scale.y: 0.28
        scale.x: 0.28
        adasAnim_LeftTop_RightBot: adas3d_LCA_RIGHT_WARN

        sourceImage: {
            if(adas3d_LCA_RIGHT_WARN === 1){
                "./adas_image/pic_HMI_classic_default_road_BSD_yellow2.png"
            }else if(adas3d_LCA_RIGHT_WARN === 2){
                "./adas_image/pic_HMI_classic_default_road_BSD_red.png"
            }else{
                ""
            }
        }
    }

    //FCTA 前方交通穿行右侧提示
    CustomMask{
        id: thisCar_FctaRight_Mask
        visible: fctaRight !== 0
        x: 30
        y: 5
        eulerRotation.x: 85
        scale.x: 0.32
        scale.y: 0.07
        adasAnim_Left_Right: 1//adas3d_RCTA_RIGHT_WARN

        sourceImage:{
            if(fctaRight === 1){
                "./adas_image/pic_HMI_classic_default_road_RCTA_FCTA4.png"  //黄色提示
            }else if(fctaRight === 2){
                "./adas_image/pic_HMI_classic_default_road_RCTA_FCTA2.png" //红色提示
            }else{
                ""
            }
        }
    }

    //FCTA 前方交通穿行左侧提示
    CustomMask{
        id: thisCar_FctaLeft_Mask
        visible: fctaLeft !== 0
        x: -33
        y: 5
        eulerRotation.x: 85
        scale.x: 0.32
        scale.y: 0.07
        adasAnim_Right_Left: 1

        sourceImage:{
            if(fctaLeft === 1){
                "./adas_image/pic_HMI_classic_default_road_RCTA_FCTA3.png" //黄色提示
            }else if(fctaLeft === 2){
                 "./adas_image/pic_HMI_classic_default_road_RCTA_FCTA.png" //红色提示
            }else{
                ""
            }
        }
    }

    //RCTA 后方交通穿行右侧提示
    CustomMask{
        id: thisCar_RCTA_RIGHT_Mask
        visible: /*left_Right_Anim_Running  ||*/ adas3d_RCTA_RIGHT_WARN !== 0
        x: 33
        y: -40
        eulerRotation.x: 95
        scale.x: 0.37000000000000016
        scale.y: 0.08
        adasAnim_Left_Right: 1//adas3d_RCTA_RIGHT_WARN

        sourceImage:{
            if(adas3d_RCTA_RIGHT_WARN === 1){
                "./adas_image/pic_HMI_classic_default_road_RCTA_FCTA4.png"  //黄色提示
            }else if(adas3d_RCTA_RIGHT_WARN === 2){
                "./adas_image/pic_HMI_classic_default_road_RCTA_FCTA2.png" //红色提示
            }else{
                ""
            }
        }
    }

    //RCTA 后方交通穿行左侧提示
    CustomMask{
        id: thisCar_RCTA_LEFT_Mask
        visible: adas3d_RCTA_LEFT_WARN !== 0
        x: -33
        y: -40
        eulerRotation.x: 98
        scale.x: 0.37000000000000016
        scale.y: 0.08
        adasAnim_Right_Left: 1

        sourceImage:{
            if(adas3d_RCTA_LEFT_WARN === 1){
                "./adas_image/pic_HMI_classic_default_road_RCTA_FCTA3.png" //黄色提示
            }else if(adas3d_RCTA_LEFT_WARN === 2){
                 "./adas_image/pic_HMI_classic_default_road_RCTA_FCTA.png" //红色提示
            }else{
                ""
            }
        }
    }

    //转向辅助-黄色标识（左侧）
    Model{
        id: thisCar_Turn_yellow1
        visible: false
        source: "#Rectangle"
        castsShadows: false //阴影
        pickable: false  //是否可选
        x: -20
        y: 38
        eulerRotation.x: 50
        scale.z: 0.3
        scale.y: 0.3
        scale.x: 0.3

        materials: DefaultMaterial {
            diffuseMap: Texture {
                source: "./adas_image/pic_HMI_classic_default_road_turn3.png"

                SequentialAnimation{
                    running: true
                    loops: Animation.Infinite
                    NumberAnimation {target: thisCar_Turn_yellow1; property: "opacity"; duration: 2000; to: 0.2; easing.type: Easing.InOutQuad}
                    NumberAnimation {target: thisCar_Turn_yellow1; property: "opacity"; duration: 2000; to: 1.0; easing.type: Easing.InOutQuad}
                }
            }
        }
    }

    //转向辅助-黄色标识（右侧）
    Model{
        id: thisCar_Turn_yellow2
        visible: false
        source: "#Rectangle"
        castsShadows: false //阴影
        pickable: false  //是否可选
        x: 20
        y: 38
        eulerRotation.x: 50
        scale.z: 0.3
        scale.y: 0.3
        scale.x: 0.3

        materials: DefaultMaterial {
            diffuseMap: Texture {
                source: "./adas_image/pic_HMI_classic_default_road_turn2.png"

                SequentialAnimation{
                    running: true
                    loops: Animation.Infinite
                    NumberAnimation {target: thisCar_Turn_yellow2; property: "opacity"; duration: 2000; to: 0.2; easing.type: Easing.InOutQuad}
                    NumberAnimation {target: thisCar_Turn_yellow2; property: "opacity"; duration: 2000; to: 1.0; easing.type: Easing.InOutQuad}
                }
            }
        }
    }

    //转向辅助-蓝色标识（左侧）
    Model{
        id: thisCar_Turn_blue1
        visible: false
        source: "#Rectangle"
        castsShadows: false //阴影
        pickable: false  //是否可选
        x: -20
        y: 38
        eulerRotation.x: 50
        scale.z: 0.3
        scale.y: 0.3
        scale.x: 0.3

        materials: DefaultMaterial {
            diffuseMap: Texture {
                source: "./adas_image/pic_HMI_classic_default_road_turn1.png"

                SequentialAnimation{
                    running: true
                    loops: Animation.Infinite
                    NumberAnimation {target: thisCar_Turn_blue1; property: "opacity"; duration: 2000; to: 0.2; easing.type: Easing.InOutQuad}
                    NumberAnimation {target: thisCar_Turn_blue1; property: "opacity"; duration: 2000; to: 1.0; easing.type: Easing.InOutQuad}
                }
            }
        }
    }

    //转向辅助-蓝色标识（右侧）
    Model{
        id: thisCar_Turn_blue2
        visible: false
        source: "#Rectangle"
        castsShadows: false //阴影
        pickable: false  //是否可选
        x: 20
        y: 38
        eulerRotation.x: 50
        scale.z: 0.3
        scale.y: 0.3
        scale.x: 0.3

        materials: DefaultMaterial {
            diffuseMap: Texture {
                source: "./adas_image/pic_HMI_classic_default_road_turn4.png"

                SequentialAnimation{
                    running: true
                    loops: Animation.Infinite
                    NumberAnimation {target: thisCar_Turn_blue2; property: "opacity"; duration: 2000; to: 0.2; easing.type: Easing.InOutQuad}
                    NumberAnimation {target: thisCar_Turn_blue2; property: "opacity"; duration: 2000; to: 1.0; easing.type: Easing.InOutQuad}
                }
            }
        }
    }

    //SR 障碍物_0
    CustomMaskArc{
        id:maskArc_SR_0
        tradius: targetObj0.arcRadius//半径
        tLineColor: targetObj0.arcColor
        tStartAngle: targetObj0.arcStartAngle //起始角度
    }

    //SR 障碍物_1
    CustomMaskArc{
        id:maskArc_SR_1
        tradius: targetObj1.arcRadius//半径
        tLineColor: targetObj1.arcColor
        tStartAngle: targetObj1.arcStartAngle //起始角度
    }

    //SR 障碍物_2
    CustomMaskArc{
        id:maskArc_SR_2
        tradius: targetObj2.arcRadius//半径
        tLineColor: targetObj2.arcColor
        tStartAngle: targetObj2.arcStartAngle //起始角度
    }

    //SR 障碍物_3
    CustomMaskArc{
        id:maskArc_SR_3
        tradius: targetObj3.arcRadius//半径
        tLineColor: "red"//targetObj3.arcColor
        tStartAngle: targetObj3.arcStartAngle //起始角度
    }

    //SR 障碍物_4
    CustomMaskArc{
        id:maskArc_SR_4
        tradius: targetObj4.arcRadius//半径
        tLineColor: targetObj4.arcColor
        tStartAngle: targetObj4.arcStartAngle //起始角度
    }

    //SR 障碍物_5
    CustomMaskArc{
        id:maskArc_SR_5
        tradius: targetObj5.arcRadius//半径
        tLineColor: targetObj5.arcColor
        tStartAngle: targetObj5.arcStartAngle //起始角度
    }

    //FCW 前车碰撞预警
    CustomMask{
        id: thisCar_RcwMask
        visible: adas3d_FCW_WARN
        x: 0
        y: -14
        z: 20
        eulerRotation.x: 81
        scale.x: 0.33
        scale.y: 0.22
        //adasAnim_Bottom_Top: true
        opacity: 0.99
        sourceImage: {
            if(adas3d_FCW_WARN === 1){
                "./adas_image/pic_HMI_classic_default_road_RCW_FCW_yellow.png" //黄色
            }else if(adas3d_FCW_WARN === 2){
                "./adas_image/pic_HMI_classic_default_road_RCW_FCW.png" //红色
            }else{
                ""
            }
        }
    }

    //RCW 追尾碰撞预警
    CustomMask{
        id: thisCar_FcwMask
        visible: adas3d_RCW_WARN
        x: 0
        y: -64
        z: 20
        eulerRotation.x : 81
        scale.x: 0.22
        scale.y: 0.16
        //adasAnim_Bottom_Top: true
        opacity: 0.99
        sourceImage: {
            if(adas3d_RCW_WARN === 1){
                "./adas_image/pic_HMI_classic_default_road_RCW_FCW_yellow.png" //黄色
            }else if(adas3d_RCW_WARN === 2){
                "./adas_image/pic_HMI_classic_default_road_RCW_FCW.png" //红色
            }else{
                ""
            }
        }
    }

    //目标0
    CusNode{
        id: target0
        x: targetObj0.positionX
        y: targetObj0.positionY
        type: targetObj0.targetObjectType
        visible: targetObj0.enable
        rotationX: 180
        rotationY: 180
        rotationZ: 0
        scaleX: 0.01
        scaleY: 0.01
        scaleZ: 0.01

        onTypeChanged: {
            if(type === 1){//smallcar小型车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 0.01
                scaleY = 0.01
                scaleZ = 0.01
            }else if(type === 2){//moto摩托车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 12
                scaleY = 12
                scaleZ = 9
            }else if(type === 3){//truck卡车
                rotationX = 90
                rotationY = 90
                rotationZ = 90
                scaleX = 0.3
                scaleY = 0.3
                scaleZ = 0.3
            }else if(type === 4){//pedestrian行人
                rotationX = 270
                rotationY = 180
                rotationZ = 0
                scaleX = 0.15
                scaleY = 0.15
                scaleZ = 0.15
            }else{

            }
        }
    }

    //目标1
    CusNode{
        id: target1
        x: targetObj1.positionX
        y: targetObj1.positionY
        type: targetObj1.targetObjectType
        rotationX: 180
        rotationY: 180
        rotationZ: 0
        scaleX: 0.01
        scaleY: 0.01
        scaleZ: 0.01
        visible: targetObj1.enable

        onTypeChanged: {
            if(type === 1){//smallcar小型车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 0.01
                scaleY = 0.01
                scaleZ = 0.01
            }else if(type === 2){//moto摩托车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 12
                scaleY = 12
                scaleZ = 9
            }else if(type === 3){//truck卡车
                rotationX = 90
                rotationY = 90
                rotationZ = 90
                scaleX = 0.3
                scaleY = 0.3
                scaleZ = 0.3
            }else if(type === 4){//pedestrian行人
                rotationX = 270
                rotationY = 180
                rotationZ = 0
                scaleX = 0.15
                scaleY = 0.15
                scaleZ = 0.15
            }else{

            }
        }
    }

    //目标2
    CusNode{
        id: target2
        x: targetObj2.positionX
        y: targetObj2.positionY
        type: targetObj2.targetObjectType
        rotationX: 90
        rotationY: 90
        rotationZ: 90
        scaleX: 0.3
        scaleY: 0.3
        scaleZ: 0.3
        visible: targetObj2.enable

        onTypeChanged: {
            if(type === 1){//smallcar小型车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 0.01
                scaleY = 0.01
                scaleZ = 0.01
            }else if(type === 2){//moto摩托车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 12
                scaleY = 12
                scaleZ = 9
            }else if(type === 3){//truck卡车
                rotationX = 90
                rotationY = 90
                rotationZ = 90
                scaleX = 0.3
                scaleY = 0.3
                scaleZ = 0.3
            }else if(type === 4){//pedestrian行人
                rotationX = 270
                rotationY = 180
                rotationZ = 0
                scaleX = 0.15
                scaleY = 0.15
                scaleZ = 0.15
            }else{

            }
        }
    }

    //目标3
    CusNode{
        id: target3
        x: targetObj3.positionX
        y: targetObj3.positionY
        type: targetObj3.targetObjectType
        rotationX: 270
        rotationY: 180
        rotationZ: 0
        scaleX: 0.15
        scaleY: 0.15
        scaleZ: 0.15
        visible: targetObj3.enable

        onTypeChanged: {
            if(type === 1){//smallcar小型车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 0.01
                scaleY = 0.01
                scaleZ = 0.01
            }else if(type === 2){//moto摩托车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 12
                scaleY = 12
                scaleZ = 9
            }else if(type === 3){//truck卡车
                rotationX = 90
                rotationY = 90
                rotationZ = 90
                scaleX = 0.3
                scaleY = 0.3
                scaleZ = 0.3
            }else if(type === 4){//pedestrian行人
                rotationX = 270
                rotationY = 180
                rotationZ = 0
                scaleX = 0.15
                scaleY = 0.15
                scaleZ = 0.15
            }else{

            }
        }
    }

    //目标4
    CusNode{
        id: target4
        x: targetObj4.positionX
        y: targetObj4.positionY
        type: targetObj4.targetObjectType
        rotationX: 270
        rotationY: 180
        rotationZ: 0
        scaleX: 0.15
        scaleY: 0.15
        scaleZ: 0.15
        visible: targetObj4.enable

        onTypeChanged: {
            if(type === 1){//smallcar小型车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 0.01
                scaleY = 0.01
                scaleZ = 0.01
            }else if(type === 2){//moto摩托车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 12
                scaleY = 12
                scaleZ = 9
            }else if(type === 3){//truck卡车
                rotationX = 90
                rotationY = 90
                rotationZ = 90
                scaleX = 0.3
                scaleY = 0.3
                scaleZ = 0.3
            }else if(type === 4){//pedestrian行人
                rotationX = 270
                rotationY = 180
                rotationZ = 0
                scaleX = 0.15
                scaleY = 0.15
                scaleZ = 0.15
            }else{

            }
        }
    }

    //目标5
    CusNode{
        id: target5
        x: targetObj5.positionX
        y: targetObj5.positionY
        type: targetObj5.targetObjectType
        rotationX: 180
        rotationY: 180
        rotationZ: 0
        scaleX: 12
        scaleY: 12
        scaleZ: 9
        visible: targetObj5.enable

        onTypeChanged: {
            if(type === 1){//smallcar小型车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 0.01
                scaleY = 0.01
                scaleZ = 0.01
            }else if(type === 2){//moto摩托车
                rotationX = 180
                rotationY = 180
                rotationZ = 0
                scaleX = 12
                scaleY = 12
                scaleZ = 9
            }else if(type === 3){//truck卡车
                rotationX = 90
                rotationY = 90
                rotationZ = 90
                scaleX = 0.3
                scaleY = 0.3
                scaleZ = 0.3
            }else if(type === 4){//pedestrian行人
                rotationX = 270
                rotationY = 180
                rotationZ = 0
                scaleX = 0.15
                scaleY = 0.15
                scaleZ = 0.15
            }else{

            }
        }
    }

    //测试定时器 rh
    Timer{
        id:ceshi
        interval: 2000
        running: false
        repeat: true
        onTriggered: {
            // console.log("******************************")
            //targetObj0111 = (targetObj0111 + 1) % 6
            //            targetObj1.targetObjectType = (targetObj1.targetObjectType + 1) % 6
            //            targetObj2.targetObjectType = (targetObj2.targetObjectType + 1) % 6
            //            targetObj3.targetObjectType = (targetObj3.targetObjectType + 1) % 6
            //            targetObj4.targetObjectType = (targetObj4.targetObjectType + 1) % 6
            //            targetObj5.targetObjectType = (targetObj5.targetObjectType + 1) % 6
        }
    }

}


/*##^##
Designer {
    D{i:0;active3dScene:0;uuid:"c6364ef7467cd9660d2efb5f89020a85"}D{i:2;uuid:"a0fed57e746b201ff69c7efe371893ef"}
D{i:1;uuid:"a0fed57e746b201ff69c7efe371893ef"}
}
##^##*/
