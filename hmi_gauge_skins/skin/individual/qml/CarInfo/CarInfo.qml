import QtQuick 2.8
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0

import qmlEnums 1.0
import "../Common"

Item {
    width: 1920
    height: 720
    visible: isCardShown
    property bool isCardShown: CarInfoScreen.isCardShown//isCardShown
    property string remainRange: CarInfoScreen.remainRange//续航里程
    property int isCarInfoChildIndex: CarInfoScreen.isCarInfoChildIndex
    property int cardIndicatorNum: 4//CarInfoScreen.cardIndicatorNum
    property bool isWarningState: Manager.isWarningState

    property string afterStartDrivingDistance:  CarInfoScreen.afterStartDrivingDistance
    property string afterStartDrivingTime:      CarInfoScreen.afterStartDrivingTime
    property string afterStartAvgSpeed:         CarInfoScreen.afterStartAvgSpeed
    property string afterStartAvgEnergy:        CarInfoScreen.afterStartAvgEnergy

    property string afterResetDrivingDistance:  CarInfoScreen.afterResetDrivingDistance
    property string afterResetDrivingTime:      CarInfoScreen.afterResetDrivingTime
    property string afterResetAvgSpeed:         CarInfoScreen.afterResetAvgSpeed
    property string afterResetAvgEnergy:        CarInfoScreen.afterResetAvgEnergy
    property var chargeDay:                     CarInfoScreen.chargeDay
    property var chargeHour:                    CarInfoScreen.chargeHour
    property var chargeOdo:                     CarInfoScreen.chargeOdo
    property var avgAPCValue:                   CarInfoScreen.averageAPC

    property double pointNumber_0:          87
    property double pointNumber_1:          87
    property double pointNumber_2:          87
    property double pointNumber_3:          87
    property double pointNumber_4:          87
    property double pointNumber_5:          87
    property double pointNumber_6:          87
    property double pointNumber_7:          87
    property int pointDistance: 44

    Timer{
        running: true
        repeat: true
        interval: 500
        onTriggered: {
            var list = CarInfoScreen.qmlInstanceList()  //value

            var paintHeight = 87
            var valueMax =99.9
            var valueMaxPre = valueMax-avgAPCValue
            var valueMin = -20
            var valueMinPre = avgAPCValue-valueMin
            //10 上下加10,防止线，球被裁切
            if(valueMax === 0 ) return;
            if(valueMaxPre === 0) return;
            if(valueMinPre === 0) return;
            // This is available in all editors
            pointNumber_0 = list[0]>avgAPCValue?Number((Number(valueMax-list[0]) / valueMaxPre) * paintHeight).toFixed(1): Number(paintHeight + (Number(avgAPCValue-list[0]) / valueMinPre) * paintHeight).toFixed(1)
            pointNumber_1 = list[1]>avgAPCValue?Number((Number(valueMax-list[1]) / valueMaxPre) * paintHeight).toFixed(1): Number(paintHeight + (Number(avgAPCValue-list[1]) / valueMinPre) * paintHeight).toFixed(1)
            pointNumber_2 = list[2]>avgAPCValue?Number((Number(valueMax-list[2]) / valueMaxPre) * paintHeight).toFixed(1): Number(paintHeight + (Number(avgAPCValue-list[2]) / valueMinPre) * paintHeight).toFixed(1)
            pointNumber_3 = list[3]>avgAPCValue?Number((Number(valueMax-list[3]) / valueMaxPre) * paintHeight).toFixed(1): Number(paintHeight + (Number(avgAPCValue-list[3]) / valueMinPre) * paintHeight).toFixed(1)
            pointNumber_4 = list[4]>avgAPCValue?Number((Number(valueMax-list[4]) / valueMaxPre) * paintHeight).toFixed(1): Number(paintHeight + (Number(avgAPCValue-list[4]) / valueMinPre) * paintHeight).toFixed(1)
            pointNumber_5 = list[5]>avgAPCValue?Number((Number(valueMax-list[5]) / valueMaxPre) * paintHeight).toFixed(1): Number(paintHeight + (Number(avgAPCValue-list[5]) / valueMinPre) * paintHeight).toFixed(1)
            pointNumber_6 = list[6]>avgAPCValue?Number((Number(valueMax-list[6]) / valueMaxPre) * paintHeight).toFixed(1): Number(paintHeight + (Number(avgAPCValue-list[6]) / valueMinPre) * paintHeight).toFixed(1)
            pointNumber_7 = list[7]>avgAPCValue?Number((Number(valueMax-list[7]) / valueMaxPre) * paintHeight).toFixed(1): Number(paintHeight + (Number(avgAPCValue-list[7]) / valueMinPre) * paintHeight).toFixed(1)

//            console.log(pointNumber_0,pointNumber_1,pointNumber_2,pointNumber_3,pointNumber_4,pointNumber_5,pointNumber_6,pointNumber_7)
//            console.log(avgAPCValue)
            pointNumber_0 += 10
            pointNumber_1 += 10
            pointNumber_2 += 10
            pointNumber_3 += 10
            pointNumber_4 += 10
            pointNumber_5 += 10
            pointNumber_6 += 10
            pointNumber_7 += 10
        }
    }
    /********************************************指示器********************************************/
    CustomPageIndicator{
        id: cpi
        indicatorCount: cardIndicatorNum
        curIndicatorIndex: isCarInfoChildIndex
        visible: cardIndicatorNum > 1 && !isWarningState
    }

    /********************************************C区********************************************/
    //能耗
    Loader{
        id:energyLoader
        sourceComponent: energyCom
        active:isCarInfoChildIndex === 0
        visible: isCarInfoChildIndex === 0 && !isWarningState
        onLoaded: {
            active = true
        }
    }
    Component{
        id:energyCom
        Item{
            CustomText{
                id:energyTitle
                x:192
                y:146
                width: 457
                height: 26
                font.pixelSize: 28
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHLeft
                font.family:trLanguge("font")
                text:trLangugeDayDisPop("近XXXkm电耗","100")
            }

            CustomText{
                id:lastEnergyText
                x:190
                y:377
                width: 119
                height: 22
                font.pixelSize: 22
                opacity: 0.3
                horizontalAlignment: Text.AlignHLeft
                font.family:trLanguge("font")
                text:trLanguge("距上次充电")
            }
            CustomText{
                id:lastEnergyValue
                x:190
                y:410
                width: 243
                height: 30
                font.pixelSize: 28
                horizontalAlignment: Text.AlignHLeft
                font.family:trLanguge("font")
                text:chargeDay+trLanguge("天")+chargeHour+trLanguge("小时")+"|"+chargeOdo+"km"
            }
            Shape{
                id: shapeZone_line
                x: itemShape.x
                y:180
                width: 307+20
                height: 180
                antialiasing: true
                smooth: true
                layer.enabled: true
                layer.samples: 8
                visible: true
                ShapePath{
                    id: shpath
                    startX: 307
                    startY: pointNumber_7
                    strokeWidth: 3
                    fillColor: "transparent"
                    strokeColor: "#ccbda9"
                    capStyle: ShapePath.RoundCap
                    PathCurve {
                        id: electricityline_01;
                        x: shpath.startX-pointDistance
                        y: pointNumber_6
                    }
                    PathCurve {
                        id: electricityline_02;
                        x: shpath.startX-pointDistance*2
                        y: pointNumber_5
                    }
                    PathCurve {
                        id: electricityline_03;
                        x: shpath.startX-pointDistance*3
                        y: pointNumber_4
                    }
                    PathCurve {
                        id: electricityline_04;
                        x: shpath.startX-pointDistance*4
                        y: pointNumber_3
                    }
                    PathCurve {
                        id: electricityline_05;
                        x: shpath.startX-pointDistance*5
                        y: pointNumber_2
                    }
                    PathCurve {
                        id: electricityline_06;
                        x: shpath.startX-pointDistance*6
                        y: pointNumber_1
                    }
                    PathCurve {
                        id: electricityline_07;
                        x: shpath.startX-pointDistance*7
                        y: pointNumber_0
                    }

                }

            }
            Item{
                id: itemShape
                x:199
                y:180
                width: 307
                height: 180

                Item {
                    id: carInfoFuelComsump_EC
                    width: 307
                    height: 170
                    visible: false
                    Image {
                        y:0
                        width: 307
                        height: 170
                        id: carInfoFuelComsump_ECBgColor
                        source: "pic_areaC_electric_bgramp.png";
                    }
                }

                Shape{
                    id: shapeZone_EC
                    width: 307
                    height: 170
                    antialiasing: true
                    smooth: true
                    layer.enabled: true
                    layer.samples: 8
                    visible: false
                    ShapePath {
                        id: shapePath_EC
                        startX: 307
                        startY: pointNumber_7
                        strokeWidth: 3
                        fillColor: "#E28712"
                        strokeColor: "black"
                        capStyle: ShapePath.RoundCap
                        PathCurve {
                            id: electricity_01;
                            x: shpath.startX-pointDistance
                            y: pointNumber_6
                        }
                        PathCurve {
                            id: electricity_02;
                            x: shpath.startX-pointDistance*2
                            y: pointNumber_5
                        }
                        PathCurve {
                            id: electricity_03;
                            x: shpath.startX-pointDistance*3
                            y: pointNumber_4
                        }
                        PathCurve {
                            id: electricity_04;
                            x: shpath.startX-pointDistance*4
                            y: pointNumber_3
                        }
                        PathCurve {
                            id: electricity_05;
                            x: shpath.startX-pointDistance*5
                            y: pointNumber_2
                        }
                        PathCurve {
                            id: electricity_06;
                            x: shpath.startX-pointDistance*6
                            y: pointNumber_1
                        }
                        PathCurve {
                            id: electricity_07;
                            x: shpath.startX-pointDistance*7
                            y: pointNumber_0
                        }
                        //固定点右边
                        PathLine {
                            id: electricity_right;
                            x: electricity_07.x
                            y: 180
                        }
                        //固定点底边
                        PathLine {
                            id: electricity_bottom;
                            x: shapePath_EC.startX
                            y: 180
                        }
                    }
                }
                OpacityMask {
                    width: 307
                    height: 170
                    source: carInfoFuelComsump_EC
                    maskSource: shapeZone_EC
                }
            }
            Image {
                id: carInfoFuelComsump_ECCurrentPoint
                width: 47
                height: 50
                source: "icon_areaC_electric_light.png"
                x: shpath.startX+177
                y: pointNumber_7+152
            }
            Item{
                id:energyMainPic
                x:146
                y:190
                width: 380
                height: 180
                Image{
                    id:energyBg
                    width: 380
                    height: 180
                    source: "pic_areaC_electric_bgline.png"
                }
                CustomText{
                    id:averageAPCText
                    x:44
                    y:66
                    width: 39
                    height: 20
                    font.pixelSize: 20
                    opacity: 0.3
                    font.family:trLanguge("font")
                    text:trLanguge("平均")
                }
                CustomText{
                    id:averageAPCValue
                    x:46
                    y:90
                    font.pixelSize: 20
                    opacity: 0.3
                    font.family:trLanguge("font")
                    text:avgAPCValue+"kwh/100km"
                }

                Image{
                    id:energyAvePic
                    x:13
                    y:87
                    width: 367
                    height: 2
                    source: "pic_areaC_electric_averageline.png"
                }
            }
        }
    }


    //自启动后
    Loader{
        id: afterStartLoader
        sourceComponent: afterStartCom
        active: isCarInfoChildIndex === 1
        visible: isCarInfoChildIndex === 1 && !isWarningState
        onLoaded: {
            active = true;
        }
    }
    Component{
        id: afterStartCom
        CustomCarInfo{
            x: 187
            y: 162
            title: trLanguge("启动后")
            drivingDistance: afterStartDrivingDistance
            drivingTime: afterStartDrivingTime
            avgSpeed: afterStartAvgSpeed
            avgEnergy: afterStartAvgEnergy
        }
    }

    //自复位后
    Loader{
        id: afterResetLoader
        sourceComponent: afterResetCom
        active: isCarInfoChildIndex === 2
        visible: isCarInfoChildIndex === 2 && !isWarningState
        onLoaded: {
            active = true;
        }
    }
    Component{
        id: afterResetCom
        CustomCarInfo{
            x: 187
            y: 162
            title: trLanguge("复位后")
            drivingDistance: afterResetDrivingDistance
            drivingTime: afterResetDrivingTime
            avgSpeed: afterResetAvgSpeed
            avgEnergy: afterResetAvgEnergy
            resetVisible: true
        }
    }

    //C3胎压胎温
    Loader{
        id: tyreLoader
        sourceComponent: tyreCom
        active: isCarInfoChildIndex === 3
        visible: isCarInfoChildIndex === 3 && !isWarningState
        onLoaded: {
            active = true;
        }
    }
    Component{
        id: tyreCom
        CustomTyre{}
    }

    /********************************************C区********************************************/

    //续航里程
    Loader{
        id: rechargeMileageLoader
        sourceComponent: rechargeMileageComponent
        onLoaded: {
            active = true
        }
    }
    Component{
        id: rechargeMileageComponent
        Item{
            width: parent.width
            height: 31
            y: 672

            Image{
                id: rg
                x:301
                width: 42
                height: 31
                source: Number(remainRange) >= 100 ? "remain_range.png" : "remain_range_yellow.png"
            }

            CustomTextEn{
                anchors.left: rg.right
                anchors.verticalCenter: rg.verticalCenter
                font.pixelSize: 32
                color: "#C4BAB4";
                text: remainRange + "km"
            }
        }
    }

}
