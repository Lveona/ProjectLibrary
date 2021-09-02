import QtQuick 2.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0

Item {
    id: r
    width: radius*2
    height: width
    x: center_x - radius
    y: center_y - radius

    property real startAngle
    property real curAngle
    property real radius
    property real center_x
    property real center_y
    property real startX_value: {
        radius + radius * Math.cos(curAngle * Math.PI/180)
    }
    property real startY_value: {
        radius + (radius) *  Math.sin(curAngle * Math.PI/180)
    }

    function getx(r, angle){
        return r + r * Math.cos(angle*Math.PI/180)
    }
    function gety(r, angle){
        return r + r * Math.sin(angle*Math.PI/180)
    }
    function getppos(r, angle){
        return Qt.point(getx(r, angle), gety(r, angle))
    }

    property point ponit1: Qt.point(radius, radius)// 第一个点_最上面圆点,第四个点和第一个点重合
    property point ponit2: getppos(radius, startAngle) // 第二个点_最左侧
    property point ponit3: getppos(radius, curAngle + startAngle)

    property string headlightSrc
    property real headlightX: 0
    property real headlightY: 0


    Item {
        id: imgArea
        anchors.fill: parent
        visible:false
        Image {
            x: headlightX - r.x
            y: headlightY - r.y
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
            startX: ponit2.x
            startY: ponit2.y
            fillColor: "red"
            strokeColor: "transparent"
            strokeWidth: 0
            PathArc {
                id: pathArc
                x: ponit3.x
                y: ponit3.y
                radiusX: radius
                radiusY: radius
//                    useLargeArc: true//s.value>180?true:false
            }
            PathLine{
                id: pathLine_2
                x: ponit1.x
                y: ponit1.y
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
