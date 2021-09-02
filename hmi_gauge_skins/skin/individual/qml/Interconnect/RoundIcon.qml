import QtQuick 2.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0

Item {
    id: item
    width: radius*2
    height: width

    property string source
    property real radius: 200

    Image {
        id: bug
        source: item.source
        anchors.fill: parent
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

            PathArc {
                id: pathArc
                x: shapePath.startX-1
                y: shapePath.startY
                radiusX: shapePath.radius
                radiusY: shapePath.radius
                useLargeArc: true
            }
        }
    }

    OpacityMask {
        anchors.fill: bug
        source: bug
        maskSource: mask
    }
}
