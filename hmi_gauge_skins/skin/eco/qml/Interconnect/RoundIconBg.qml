import QtQuick 2.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0
//import QtQuick.Controls 1.4
Item {
    id: item
    width: radius*2
    height: width

    property string source: "qrc:/eco/qml/Interconnect/media/Audio_Progress.png"
    property real radius: 116
    property real process: 0    //0-1
    property int angleMax: 360


//    Slider {
//        y: 200
//        z: 1
//        value: 0  //当前值

//        minimumValue : 0  //最小值

//        maximumValue: 1   //最大值
//        stepSize: 0.1
//        width: 300

//        onValueChanged: process = value
//      }
    Image {
        id: bug
        source: item.source
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true
        visible: false
    }

    Shape{
        id: mask
        anchors.fill: bug
        visible: false
        antialiasing: true

        ShapePath{
            id: shapePath
            startX: radius
            startY: 0
            fillColor: "red"
            property real radius: item.radius

            //0 90   90 0  180 -90
            property real endAngle: (1-item.process)*item.angleMax + 90
            property real endx_value: radius + radius*Math.cos(shapePath.endAngle*Math.PI/180)
            property real endy_value: radius - radius*Math.sin((shapePath.endAngle)*Math.PI/180)

            PathArc {
                id: pathArc
                x: {
                    if(item.process == 0){
                        shapePath.endx_value
                    }
                    else if(item.process == 1){
                        shapePath.endx_value-1
                    }
                    else{
                        shapePath.endx_value
                    }
                }
                y: shapePath.endy_value
                radiusX: shapePath.radius
                radiusY: shapePath.radius
                useLargeArc: item.process>0.5?true:false
            }
//            PathLine{
//                x: shapePath.endx_value
//                y: shapePath.endy_value
//            }
            PathLine{
                x: shapePath.radius
                y: shapePath.radius
            }
        }
    }

    OpacityMask {
        anchors.fill: bug
        source: bug
        maskSource: mask
    }
}
