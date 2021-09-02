import QtQuick 2.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0

Item {
    id: r
    width: 1920
    height: 720
    property var point1: point1
    property var point2: point2
    property var point3: point3
    property var point4: point4
    property var curValue: carValue
    property var maxValue: maxValue

    property string headlightSrc
    property real headlightX: 0
    property real headlightY: 0

    Item{
        id: imgArea
        visible:false
        anchors.fill: parent
        Image {
            y: headlightY
            x: headlightX
            source: headlightSrc
        }
    }

    Shape{
        id: visibleArea
        anchors.fill: parent
        antialiasing: true
        smooth: true
        layer.enabled: true
        layer.samples: 8
        visible: false
        ShapePath {
            startX: point1.x
            startY: point1.y
            fillColor: "red"
            strokeColor: "transparent"
            strokeWidth: 0
            PathLine{
                id: pathLine_2
                x: point2.x
                y: point2.y
            }
            PathLine{
                x: point2.x - (point2.x - point3.x) * (curValue/ maxValue)
                y: point2.y - (point2.y - point3.y) * (curValue/ maxValue)
            }
            PathLine{
                x: point1.x - (point1.x - point4.x) * (curValue/ maxValue)
                y: point1.y - (point1.y - point4.y) * (curValue/ maxValue)
            }
        }
    }

    OpacityMask {
        visible: !(imgArea.source==="")
        anchors.fill: imgArea
        source: imgArea
        maskSource: visibleArea
    }

}
