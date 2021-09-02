import QtQuick 2.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0

Item {
    id: r
    width: 1920
    height: 720

    //圆心
    property real pointX: 961
    property real pointY: 380

    property real startAngle
    property real curAngle
    property real radius

    function getx(x, angle){
        return x + radius * Math.cos(angle*Math.PI/180)
    }
    function gety(y, angle){
        return y + radius * Math.sin(angle*Math.PI/180)
    }
    function getppos(x, y, angle){
        return Qt.point(getx(x, angle), gety(y, angle))
    }

    property point ponit1: Qt.point(pointX, pointY)// 第一个点_最上面圆点,第四个点和第一个点重合
    property point ponit2: getppos(pointX, pointY, startAngle) // 第二个点_最左侧
    property point ponit3: getppos(pointX, pointY, curAngle + startAngle)

    property string headlightSrc


    Item {
        id: imgArea
        anchors.fill: parent
        visible:false
        Image {
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
                useLargeArc: curAngle>180?true:false
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
