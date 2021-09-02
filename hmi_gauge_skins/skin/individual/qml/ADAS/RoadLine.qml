import QtQuick 2.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0

Item {
    id: item
    width: 447
    height: 287

    property string roadLineColor :""
    property bool running :false
    Rectangle{
        id: rect
        anchors.fill: parent
        color: roadLineColor
        visible: false
    }

    Frame{
        id:imgRoadLine
        startCount:0
        anchors.fill: parent
        path:"ADAS_RoadLine_White_"
        maxCount:24
        running: item.running
        visible: false
    }

    OpacityMask {
        anchors.fill: rect
        source: rect
        maskSource: imgRoadLine
    }


}
