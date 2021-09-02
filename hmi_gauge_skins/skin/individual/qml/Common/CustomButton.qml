import QtQuick 2.0

Image {
    property bool   isPressed
    property string txtStr
    property string pressImg:  "../Diag/pop_button_selected.png"
    property string normalImg: "../Diag/pop_button_normal.png"
    property string txtColor: "white"
    property real   txtPixelSize: 36

    source: isPressed ? pressImg : normalImg
    CustomText{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: txtColor
        smooth: true
        lineHeight: 43
        lineHeightMode: Text.FixedHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: txtPixelSize
        font.letterSpacing : 0
        text: qsTr(txtStr)
    }
}
