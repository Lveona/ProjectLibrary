import QtQuick 2.0
import QtQuick3D 1.15
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.0

Model {
    id: thisCar_Model
    visible: true
    source: "#Rectangle"

    property string sourceImage
    property alias fcwImg: fcwImg
    property alias fcwMask: fcwMask

    property alias path1: path1
    property alias path2: path2
    property alias path3: path3
    property alias path4: path4

    property bool adasAnim_Bottom_Top: false
    property bool adasAnim_Top_Bottom: false

    //从左往右动效
    property int adasAnim_Left_Right: -1
    //从右往左动效
    property int adasAnim_Right_Left: -1
    //从右上到左下
    property int adasAnim_RightTop_LeftBot: -1
    //从左上到右下
    property int adasAnim_LeftTop_RightBot: -1

    //从下往上
    SequentialAnimation {
        id: bottom_Top
        running: adasAnim_Bottom_Top //运行
        loops: Animation.Infinite
        //并行动画
        ParallelAnimation{
            //属性动画-属性值改变播放的动画
            PropertyAnimation{target: path1; properties: "startY"; from: fcwImg.sourceSize.height; to: 0; duration: 500; }
            PropertyAnimation{target: path2; properties: "y"; from: fcwImg.sourceSize.height; to: 0; duration: 500; }
        }

        SequentialAnimation{
            loops: Animation.Infinite
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 250; from: 1.0; to: 0; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 250; from: 0; to: 1; easing.type: Easing.InOutQuad}
        }
    }

    //从上往下
    SequentialAnimation {
        id: top_Bottom
        running: adasAnim_Top_Bottom //运行
        loops: Animation.Infinite
        //并行动画
        ParallelAnimation{
            //属性动画-属性值改变播放的动画
            PropertyAnimation{target: path1; properties: "startY"; from: fcwImg.sourceSize.height; to: 0; duration: 500; }
            PropertyAnimation{target: path2; properties: "y"; from: fcwImg.sourceSize.height; to: 0; duration: 500; }
        }
    }

    //从左往右 - 黄色
    SequentialAnimation {
        id: left_Right_yellow
        running: adasAnim_Left_Right === 1 //运行
        //并行动画
        ParallelAnimation{
            PropertyAnimation{target: path2; properties: "x"; from: 0; to: fcwImg.sourceSize.width; duration: 500; }
            PropertyAnimation{target: path3; properties: "x"; from: 0; to: fcwImg.sourceSize.width; duration: 500; }
        }

        SequentialAnimation{
            loops: Animation.Infinite
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 500; from: 1.0; to: 0; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 500; from: 0; to: 1; easing.type: Easing.InOutQuad}
        }
    }

    //从左往右 - 红色
    SequentialAnimation {
        id: left_Right_red
        running: adasAnim_Left_Right === 2 //运行
        //并行动画
        ParallelAnimation{
            PropertyAnimation{target: path2; properties: "x"; from: 0; to: fcwImg.sourceSize.width; duration: 250; }
            PropertyAnimation{target: path3; properties: "x"; from: 0; to: fcwImg.sourceSize.width; duration: 250; }
        }

        SequentialAnimation{
            loops: Animation.Infinite
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 250; from: 1.0; to: 0; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 250; from: 0; to: 1; easing.type: Easing.InOutQuad}
        }
    }

    //从右往左 - 黄色
    SequentialAnimation {
        id: right_Left_yellow
        running: adasAnim_Right_Left === 1 //运行
        loops: Animation.Infinite
        //并行动画
        ParallelAnimation{
            //属性动画-属性值改变播放的动画
            PropertyAnimation{target: path1; properties: "startX"; from: fcwImg.sourceSize.width; to: 0; duration: 500; }
            PropertyAnimation{target: path4; properties: "x"; from: fcwImg.sourceSize.width; to: 0; duration: 500; }
        }

        SequentialAnimation{
            loops: Animation.Infinite
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 500; from: 1.0; to: 0; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 500; from: 0; to: 1; easing.type: Easing.InOutQuad}
        }
    }

    //从右往左 - 红色
    SequentialAnimation {
        id: right_Left_red
        running: adasAnim_Right_Left === 2 //运行
        loops: Animation.Infinite
        //并行动画
        ParallelAnimation{
            //属性动画-属性值改变播放的动画
            PropertyAnimation{target: path1; properties: "startX"; from: fcwImg.sourceSize.width; to: 0; duration: 500; }
            PropertyAnimation{target: path4; properties: "x"; from: fcwImg.sourceSize.width; to: 0; duration: 500; }
        }

        SequentialAnimation{
            loops: Animation.Infinite
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 250; from: 1.0; to: 0; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "opacity"; duration: 250; from: 0; to: 1; easing.type: Easing.InOutQuad}
        }
    }

    //从右上往左下 - 黄色（500ms）
    SequentialAnimation{
        id: rightTop_LeftBot_yellow
        running: adasAnim_RightTop_LeftBot === 1
        loops: Animation.Infinite
        ParallelAnimation{
            NumberAnimation {target: thisCar_Model; property: "scale.x"; duration: 500; from: 0; to: 0.28; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "scale.y"; duration: 500; from: 0; to: 0.28; easing.type: Easing.InOutQuad}

            NumberAnimation {target: thisCar_Model; property: "x"; duration: 500; from: -10; to: -15; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "y"; duration: 500; from: -40; to: -46; easing.type: Easing.InOutQuad}
        }

        ParallelAnimation{
            NumberAnimation {target: thisCar_Model; property: "scale.x"; duration: 500; to: 0; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "scale.y"; duration: 500; to: 0; easing.type: Easing.InOutQuad}

            NumberAnimation {target: thisCar_Model; property: "x"; duration: 500; from: -15; to: -10; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "y"; duration: 500; from: -46; to: -40; easing.type: Easing.InOutQuad}
        }
    }

    //从右上往左下 - 红色（250ms）
    SequentialAnimation{
        id: rightTop_LeftBot_red
        running: adasAnim_RightTop_LeftBot === 2
        loops: Animation.Infinite
        ParallelAnimation{
            NumberAnimation {target: thisCar_Model; property: "scale.x"; duration: 250; from: 0; to: 0.28; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "scale.y"; duration: 250; from: 0; to: 0.28; easing.type: Easing.InOutQuad}

            NumberAnimation {target: thisCar_Model; property: "x"; duration: 250; from: -10; to: -15; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "y"; duration: 250; from: -40; to: -46; easing.type: Easing.InOutQuad}
        }

        ParallelAnimation{
            NumberAnimation {target: thisCar_Model; property: "scale.x"; duration: 250; to: 0; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "scale.y"; duration: 250; to: 0; easing.type: Easing.InOutQuad}

            NumberAnimation {target: thisCar_Model; property: "x"; duration: 250; from: -15; to: -10; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "y"; duration: 250; from: -46; to: -40; easing.type: Easing.InOutQuad}
        }
    }

    //从左上往右下 - 黄色（500ms）
    SequentialAnimation{
        id: leftTop_RightBot_yellow
        running: adasAnim_LeftTop_RightBot === 1
        loops: Animation.Infinite
        ParallelAnimation{
            NumberAnimation {target: thisCar_Model; property: "scale.x"; duration: 500; from: 0; to: 0.28; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "scale.y"; duration: 500; from: 0; to: 0.28; easing.type: Easing.InOutQuad}

            NumberAnimation {target: thisCar_Model; property: "x"; duration: 500; from: 10; to: 15; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "y"; duration: 500; from: -40; to: -46; easing.type: Easing.InOutQuad}
        }
        ParallelAnimation{
            NumberAnimation {target: thisCar_Model; property: "scale.x"; duration: 500; to: 0; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "scale.y"; duration: 500; to: 0; easing.type: Easing.InOutQuad}

            NumberAnimation {target: thisCar_Model; property: "x"; duration: 500; from: 15; to: 10; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "y"; duration: 500; from: -46; to: -40; easing.type: Easing.InOutQuad}
        }
    }

    //从左上往左下 - 红色（250ms）
    SequentialAnimation{
        id: leftTop_RightBot_red
        running: adasAnim_LeftTop_RightBot === 2
        loops: Animation.Infinite
        ParallelAnimation{
            NumberAnimation {target: thisCar_Model; property: "scale.x"; duration: 250; from: 0; to: 0.28; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "scale.y"; duration: 250; from: 0; to: 0.28; easing.type: Easing.InOutQuad}

            NumberAnimation {target: thisCar_Model; property: "x"; duration: 250; from: 10; to: 15; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "y"; duration: 250; from: -40; to: -46; easing.type: Easing.InOutQuad}
        }
        ParallelAnimation{
            NumberAnimation {target: thisCar_Model; property: "scale.x"; duration: 250; to: 0; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "scale.y"; duration: 250; to: 0; easing.type: Easing.InOutQuad}

            NumberAnimation {target: thisCar_Model; property: "x"; duration: 250; from: 15; to: 10; easing.type: Easing.InOutQuad}
            NumberAnimation {target: thisCar_Model; property: "y"; duration: 250; from: -46; to: -40; easing.type: Easing.InOutQuad}
        }
    }

    Item {
        id: imgArea
        width: fcwImg.sourceSize.width
        height: fcwImg.sourceSize.height
        visible: false

        Image {
            id: fcwImg
            anchors.fill: parent
            source: sourceImage
        }

        Shape{
            id: visibleArea
            anchors.fill: imgArea
            antialiasing: true //锯齿化
            smooth: true  //平滑
            layer.enabled: true
            layer.samples: 8
            visible: false

            ShapePath {
                id: path1
                fillColor: "yellow"
                strokeColor: "transparent"
                strokeWidth: 0

                PathLine{
                    id: path2
                    x: fcwImg.sourceSize.width
                }

                PathLine{
                    id: path3
                    x: fcwImg.sourceSize.width
                    y: fcwImg.sourceSize.height
                }

                PathLine{
                    id: path4
                    y: fcwImg.sourceSize.height
                }
            }
        }

        OpacityMask { //遮挡
            id: fcwMask
            visible: !(fcwImg.source==="")
            anchors.fill: fcwImg  //填充
            source: fcwImg
            maskSource: visibleArea
        }
    }

    materials: DefaultMaterial { //材质
        diffuseMap: Texture {
            sourceItem: fcwMask
        }
    }
}
