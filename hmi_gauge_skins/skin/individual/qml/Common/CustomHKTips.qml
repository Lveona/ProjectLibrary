import QtQuick 2.0

Row{
    width: 123
    height: 20
    spacing: 3
    visible: tipsVisible

    property bool   tipsVisible: false
    property string direction: "down"
    property string keyText: "复位"

    CustomText{
        font.pixelSize: 20
        text: "长按"
        opacity: 0.3
    }
    Image{
        source: {
            if(direction === "down")
            {
                "../CarInfo/icon_areaC_down.png"
            }else if(direction === "up")
            {
                "../CarInfo/icon_areaC_up.png"
            }else{
                ""
            }
        }
    }
    CustomText{
        font.pixelSize: 20
        text: keyText
        opacity: 0.3
    }
}
