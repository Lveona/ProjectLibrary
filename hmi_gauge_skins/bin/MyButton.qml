import QtQuick 2.0

Item {
    id: btn
    width: 100
    height: 30

    signal myPress

    property bool isPressed: false
    property string text


    BorderImage {
        id: name
        width: btn.width; height: btn.height

        border.left: 10; border.top: 10
        border.right: 10; border.bottom: 10
        horizontalTileMode: BorderImage.Stretch
        verticalTileMode: BorderImage.Stretch

        source: "qrc:/hmibox/btn1.png"
        opacity: isPressed ? 0.7 : 1.0
    }

    Text{
        anchors.centerIn: parent
        font.family: "微软雅黑"
        text: btn.text
        color: "white"
    }

    MouseArea{
        anchors.fill: parent
        onPressed: {
            isPressed = true
            myPress()
        }
        onReleased: isPressed = false
        onCanceled: isPressed = false
    }
}

