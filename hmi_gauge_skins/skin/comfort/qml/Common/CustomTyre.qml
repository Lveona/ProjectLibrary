import QtQuick 2.0

Item{
    width: 330
    height: 338
    x: 177
    y: 147

    property string warningMsg: ""
    property string lfPressure: CarInfoScreen.carInfoTyreLFPressure
    property string lfTemp: CarInfoScreen.carInfoTyreLFTemp
    property bool lfWarn: PopupScreen.tempwarning_LF

    property string lrPressure: CarInfoScreen.carInfoTyreLRPressure
    property string lrTemp: CarInfoScreen.carInfoTyreLRTemp
    property bool lrWarn: PopupScreen.tempwarning_LR

    property string rfPressure: CarInfoScreen.carInfoTyreRFPressure
    property string rfTemp: CarInfoScreen.carInfoTyreRFTemp
    property bool rfWarn: PopupScreen.tempwarning_RF

    property string rrPressure: CarInfoScreen.carInfoTyreRRPressure
    property string rrTemp: CarInfoScreen.carInfoTyreRRTemp
    property bool rrWarn: PopupScreen.tempwarning_RR

    //warning message
    CustomText{
        id: warningMsgId
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: tyreBg.bottom
        anchors.topMargin: 20
        color: "#ff0000"
        font.pixelSize: 28
        text: warningMsg
    }

    //bg
    Image{
        id: tyreBg
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        source: "../CarInfo/tyre_bg.png"
    }
    //fl
    Image{
        id: flLine
        anchors.left: tyreBg.left
        anchors.leftMargin: -80
        anchors.top: tyreBg.top
        anchors.topMargin: 23
        source: lfWarn ? "../CarInfo/tyre_left_line_red.png" : "../CarInfo/tyre_left_line.png"
        CustomText{
            anchors.right: flLine.right
            anchors.rightMargin: 61
            anchors.top: flLine.top
            anchors.topMargin: -9
            font.pixelSize: 24
            text: lfPressure + (lfPressure === "--" ? "" : " bar")
            color: lfWarn ? "#ff0000" : "#ffffff"
        }
        CustomText{
            anchors.right: flLine.right
            anchors.rightMargin: 61
            anchors.bottom: flLine.bottom
            anchors.bottomMargin: -8
            font.pixelSize: 24
            text: lfTemp + (lfTemp === "--" ? "" : "℃")
            color: lfWarn ? "#ff0000" : "#ffffff"
        }
        Image{
            x: 87
            y:8
            source: lfWarn ? "../CarInfo/pic_areaC_car_warningtire.png" : "../CarInfo/pic_areaC_car_normaltire.png"
        }
    }
    //rl
    Image{
        id: rlLine
        anchors.left: tyreBg.left
        anchors.leftMargin: -80
        anchors.top: tyreBg.top
        anchors.topMargin: 167
        source: lrWarn ? "../CarInfo/tyre_left_line_red.png" : "../CarInfo/tyre_left_line.png"
        CustomText{
            anchors.right: rlLine.right
            anchors.rightMargin: 61
            anchors.top: rlLine.top
            anchors.topMargin: -9
            font.pixelSize: 24
            text: lrPressure + (lrPressure === "--" ? "" : " bar")
            color: lrWarn ? "#ff0000" : "#ffffff"
        }
        CustomText{
            anchors.right: rlLine.right
            anchors.rightMargin: 61
            anchors.bottom: rlLine.bottom
            anchors.bottomMargin: -8
            font.pixelSize: 24
            text: lrTemp + (lrTemp === "--" ? "" : "℃")
            color: lrWarn ? "#ff0000" : "#ffffff"
        }
        Image{
            x:87
            y:8
            source: lrWarn ? "../CarInfo/pic_areaC_car_warningtire.png" : "../CarInfo/pic_areaC_car_normaltire.png"
        }
    }
    //fr
    Image{
        id: frLine
        anchors.right: tyreBg.right
        anchors.rightMargin: -80
        anchors.top: tyreBg.top
        anchors.topMargin: 23
        source: rfWarn ? "../CarInfo/tyre_right_line_red.png" : "../CarInfo/tyre_right_line.png"
        CustomText{
            anchors.right: frLine.right
            anchors.rightMargin: -33
            anchors.top: frLine.top
            anchors.topMargin: -9
            font.pixelSize: 24
            text: rfPressure + (rfPressure === "--" ? "" : " bar")
            color: rfWarn ? "#ff0000" : "#ffffff"
        }
        CustomText{
            anchors.right: frLine.right
            anchors.rightMargin: -33
            anchors.bottom: frLine.bottom
            anchors.bottomMargin: -8
            font.pixelSize: 24
            text: rfTemp + (rfTemp === "--" ? "" : "℃")
            color: rfWarn ? "#ff0000" : "#ffffff"
        }
        Image{
            x: 1
            y:8
            source: rfWarn ? "../CarInfo/pic_areaC_car_warningtire.png" : "../CarInfo/pic_areaC_car_normaltire.png"
        }
    }
    //rr
    Image{
        id: rrLine
        anchors.right: tyreBg.right
        anchors.rightMargin: -80
        anchors.top: tyreBg.top
        anchors.topMargin: 167
        source: rrWarn ? "../CarInfo/tyre_right_line_red.png" : "../CarInfo/tyre_right_line.png"
        CustomText{
            anchors.right: rrLine.right
            anchors.rightMargin: -33
            anchors.top: rrLine.top
            anchors.topMargin: -9
            font.pixelSize: 24
            text: rrPressure + (rrPressure === "--" ? "" : " bar")
            color: rrWarn ? "#ff0000" : "#ffffff"
        }
        CustomText{
            anchors.right: rrLine.right
            anchors.rightMargin: -33
            anchors.bottom: rrLine.bottom
            anchors.bottomMargin: -8
            font.pixelSize: 24
            text: rrTemp + (rrTemp === "--" ? "" : "℃")
            color: rrWarn ? "#ff0000" : "#ffffff"
        }
        Image{
            x:1
            y:8
            source: rrWarn ? "../CarInfo/pic_areaC_car_warningtire.png" : "../CarInfo/pic_areaC_car_normaltire.png"
        }
    }
}

