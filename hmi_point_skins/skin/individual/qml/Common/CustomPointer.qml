import QtQuick 2.0
import QtGraphicalEffects 1.0

Item{
    id: pointItem

    property real radius
    property real center_x
    property real center_y

    property real visibleArea_x: 0
    property real visibleArea_y: 0

    property real pointerOffset_x: 0
    property real startAngle
    property real curAngle
    property string pointerSrc
    property string maskSrc

    x: center_x - radius
    y: center_y - radius
    width: radius*2
    height: width


    Rectangle{
        id: imgArea
        visible: false
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0)
//        color: "red"
        Image{
            id: imgArea2
//            visible: false
            x: pointItem.width/2 + pointerOffset_x
            y: pointItem.height/2-height/2
            source: pointerSrc
            transform: Rotation{
                angle: curAngle + startAngle
                axis.x : 0
                axis.y : 0
                axis.z : 1
                origin.x : -pointerOffset_x
                origin.y : imgArea2.height/2
            }
        }
    }



    Rectangle{
        id: visibleArea
        visible: false
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0)
        Image{
//            id: visibleArea
//            visible: false
            x: visibleArea_x - pointItem.x
            y: visibleArea_y - pointItem.y
            source: maskSrc
        }
    }
//    Image{
////            id: visibleArea
////            visible: false
//        x: visibleArea_x - pointItem.x
//        y: visibleArea_y - pointItem.y
//        source: maskSrc
//    }

    OpacityMask {
        anchors.fill: imgArea
        source: imgArea
        maskSource: visibleArea
    }
}
