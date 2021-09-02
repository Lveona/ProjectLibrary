import QtQuick 2.0

Item {
    width: 274
    height: 275
    property string title: ""
    property string drivingDistance: ""
    property string drivingTime: ""
    property string avgSpeed: ""
    property string avgEnergy: ""
    property bool   resetVisible: false

    Rectangle{
        y: 124
        width: 273
        height: 2
        color: "#ffffff"
        opacity: 0.4
    }

    CustomText{
        id: titleid
        font.pixelSize: 28
        font.family:trLanguge("font")
        text: title
    }

    Column{
        anchors.top: titleid.bottom
        anchors.topMargin: 27
        spacing: 24
        Row{
            spacing: 83
            Column{
                spacing: 6
                CustomText{
                    font.pixelSize: 28
                    text: drivingDistance
                }
                CustomText{
                    font.pixelSize: 20
                    font.family:trLanguge("font")
                    text: "km "+trLanguge("里程")
                }
            }
            Column{
                spacing: 6
                CustomText{
                    font.pixelSize: 28
                    text: drivingTime
                }
                CustomText{
                    font.pixelSize: 20
                    font.family:trLanguge("font")
                    text: trLanguge("行驶时间")
                }
            }
        }
        Row{
            spacing: 83
            Column{
                spacing: 6
                CustomText{
                    font.pixelSize: 28
                    text: avgSpeed
                }
                CustomText{
                    font.pixelSize: 20
                    text: "km/h"
                }
                CustomText{
                    font.pixelSize: 20
                    font.family:trLanguge("font")
                    text: trLanguge("平均速度")
                }
            }
            Column{
                spacing: 6
                CustomText{
                    font.pixelSize: 28
                    text: avgEnergy
                }
                CustomText{
                    font.pixelSize: 20
                    text: "kWh/100km"
                }
                CustomText{
                    font.pixelSize: 20
                    font.family:trLanguge("font")
                    text: trLanguge("总平均电耗")
                }
            }
        }
    }

    CustomHKTips{
        anchors.bottom: parent.bottom
        tipsVisible: resetVisible
    }
}
