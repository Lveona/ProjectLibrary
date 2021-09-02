import QtQuick 2.0
import QtQuick3D 1.15
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.0

Item {
    property int x
    property int y
    property string sourceSrc
    property alias fcwImg:fcwImg

    property alias path1:path1
    property alias path2:path2
    property alias path3:path3
    property alias path4:path4

    //从下往上
    SequentialAnimation {
           id: adasAnim_Bottom_Top
           running: false //运行
           loops: Animation.Infinite
           //并行动画
           ParallelAnimation{
               //属性动画-属性值改变播放的动画
               PropertyAnimation{target: path1; properties: "startY"; from: fcwImg.sourceSize.height; to: 0; duration: 1000; }
               PropertyAnimation{target: path2; properties: "y"; from: fcwImg.sourceSize.height; to: 0; duration: 1000; }
           }
           ParallelAnimation{
               PropertyAnimation{target: path1; properties: "startY"; from: 0; to: fcwImg.sourceSize.height; duration: 1000; }
               PropertyAnimation{target: path2; properties: "y"; from: 0; to: fcwImg.sourceSize.height; duration: 1000; }
           }
       }

    //从上往下
    SequentialAnimation {
           id: adasAnim_Top_Bottom
           running: true //运行
           loops: Animation.Infinite
           //并行动画
           ParallelAnimation{
               PropertyAnimation{target: path1; properties: "startY"; from: 0; to: fcwImg.sourceSize.height; duration: 1000; }
               PropertyAnimation{target: path2; properties: "y"; from: 0; to: fcwImg.sourceSize.height; duration: 1000; }
           }
           ParallelAnimation{
               //属性动画-属性值改变播放的动画
               PropertyAnimation{target: path1; properties: "startY"; from: fcwImg.sourceSize.height; to: 0; duration: 1000; }
               PropertyAnimation{target: path2; properties: "y"; from: fcwImg.sourceSize.height; to: 0; duration: 1000; }
           }
       }

    //从左往右
    SequentialAnimation {
           id: adasAnim_Left_Right
           running: false //运行
           loops: Animation.Infinite
           //并行动画
           ParallelAnimation{
               //属性动画-属性值改变播放的动画
               PropertyAnimation{target: path2; properties: "x"; from: fcwImg.sourceSize.width; to: 0; duration: 1000; }
               PropertyAnimation{target: path3; properties: "x"; from: fcwImg.sourceSize.width; to: 0; duration: 1000; }
           }
           ParallelAnimation{
               PropertyAnimation{target: path2; properties: "x"; from: 0; to: fcwImg.sourceSize.width; duration: 1000; }
               PropertyAnimation{target: path3; properties: "x"; from: 0; to: fcwImg.sourceSize.width; duration: 1000; }
           }
       }

    //从右往左
    SequentialAnimation {
           id: adasAnim_Right_Left
           running: false //运行
           loops: Animation.Infinite
           //并行动画         
           ParallelAnimation{
               //属性动画-属性值改变播放的动画
               PropertyAnimation{target: path1; properties: "startX"; from: fcwImg.sourceSize.width; to: 0; duration: 1000; }
               PropertyAnimation{target: path4; properties: "x"; from: fcwImg.sourceSize.width; to: 0; duration: 1000; }
           }
           ParallelAnimation{
               PropertyAnimation{target: path1; properties: "startX"; from: 0; to: fcwImg.sourceSize.width; duration: 1000; }
               PropertyAnimation{target: path4; properties: "x"; from: 0; to: fcwImg.sourceSize.width; duration: 1000; }
           }
       }

       Item {
           id: imgArea
           width: fcwImg.sourceSize.width
           height: fcwImg.sourceSize.height
           visible:false
           Image {
               id: fcwImg
               source: sourceSrc
           }
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
           visible: !(imgArea.source==="")
           anchors.fill: imgArea  //填充
           source: imgArea
           maskSource: visibleArea
       }

       Model{
           id:thisCar_FCW
           visible: true
           source: "#Rectangle"


           materials: DefaultMaterial { //
               diffuseMap: Texture {
                   sourceItem: fcwMask
               }
           }
       }
}
