import QtQuick 2.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0

Item {
    id: point
    width: 1116
    height: width

    property real pointAngle: 0
    property int direction: 1  //1:left, -1:right
    property bool isWarning: false
    Item{
        id: item
        anchors.fill: parent
        visible: false
        Image{
            id: img
            anchors.bottom: parent.bottom
            source: {
                if(direction===1)
                {
                    isWarning?"leftRed.png":"left.png"
                }
                else{
                    isWarning?"rightRed.png":"right.png"
                }
            }
        }
    }

    Shape{
        id: shape
        width: point.width
        height: width
        smooth: true
        visible: false
        antialiasing: true

        ShapePath {
            id: shapePath

            property real radius: point.width/2
            property real startAngle: 270 - point.direction*5
            property real endAngle: startAngle - point.direction*pointAngle
            property real startX_value: radius + radius*Math.cos(shapePath.startAngle*Math.PI/180)
            property real startY_value: radius - radius*Math.sin((shapePath.startAngle)*Math.PI/180)
            property real endx_value: radius + radius*Math.cos(shapePath.endAngle*Math.PI/180)
            property real endy_value: radius - radius*Math.sin((shapePath.endAngle)*Math.PI/180)

            onEndAngleChanged: {
//                console.log(direction, pointAngle, endAngle)
//                console.log("sx", direction, startX, "sy", startY)
//                console.log("ex", direction, endx_value, "ey", endy_value)
            }

            startX: startX_value
            startY: startY_value
            fillColor: "red"
            strokeColor: "yellow"//"transparent"
            strokeWidth: 1

            PathArc {
                id: pathArc
                x: shapePath.endx_value
                y: shapePath.endy_value
                radiusX: shapePath.radius
                radiusY: shapePath.radius
                useLargeArc: false  //point.direction!==1
            }
            PathLine{
                x: shapePath.radius
                y: shapePath.radius
            }
        }

        //使用虚化图片，消除图片边缘的锯齿
        Image {
            id: imgMask
            x: point.direction == 1?(shape.width/2-width):shape.width/2
            y: shape.height - height
            source: point.direction == 1?"quanBgMaskL.png":"quanBgMaskR.png"
            transform: Rotation{
                origin.x: point.direction == 1?imgMask.width:0
                origin.y: 720-558
                angle: {
                    if(point.direction == 1)
                        pointAngle + 270 - shapePath.startAngle
                    else
                        - pointAngle + 270 - shapePath.startAngle
                }
            }
        }
    }

    OpacityMask {
        id:mask
        anchors.fill: item
        source: item
        maskSource: shape
    }
}
