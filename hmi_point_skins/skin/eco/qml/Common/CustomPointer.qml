import QtQuick 2.0
import QtGraphicalEffects 1.0

Item{
    id: pointItem
    width: 1920
    height: 720
    property string pointerSrc
    property string maskSrc

    property real maskX: maskX
    property real pointerY: pointerY
    property real pointerX: pointerX
    property real pointerRotate: pointerRotate

    Rectangle{
        id: imgArea
        visible: false
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0)
        Image{
            id: imgArea2
            y: pointerY
            x: pointerX
            source: pointerSrc
            rotation: pointerRotate
        }
    }

    Rectangle{
        id: visibleArea
        visible: false
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0)
        Image{
            anchors.bottom: parent.bottom
            x: maskX
            source: maskSrc
        }
    }
    OpacityMask {
        anchors.fill: imgArea
        source: imgArea
        maskSource: visibleArea
    }
}
