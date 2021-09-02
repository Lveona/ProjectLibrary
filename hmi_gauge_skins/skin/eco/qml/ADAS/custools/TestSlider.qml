import QtQuick 2.0
//import QtQuick.Controls 2.0

Row {
    id: r
    width: 200
    height: 40

    property string label
    property real s: -100
    property real e: 100
    property var value
    property string tcolor: "white"

    spacing: 50
    signal vc(var v)


    Text {
        id: text_road
        width: 80
        text: label
        font.pixelSize: 12
        color: tcolor
        anchors.verticalCenter: parent.verticalCenter
    }

    Slider {
        id: slider_curvature
        height: 10
        width: 200
        value: r.value
        from: s
        to: e
        stepSize : 1
        onValueChanged: {
            console.log(text_road.text+":"+value)
            text_road.text = label + ": " + value
            vc(value)
        }
//        anchors.left: parent.left
        anchors.top: text_road.bottom
        anchors.topMargin: 10
    }

}
