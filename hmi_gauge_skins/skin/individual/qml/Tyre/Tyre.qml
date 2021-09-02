import QtQuick 2.8
import "../Common/"
import qmlEnums 1.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0

Item {
    id: adas
    width: 1920
    height: 720
    //visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1

    property string     carInfoTyreLFPressure  :  CarInfoScreen.carInfoTyreLFPressure
    property string     carInfoTyreRFPressure  :  CarInfoScreen.carInfoTyreRFPressure
    property string     carInfoTyreLRPressure  :  CarInfoScreen.carInfoTyreLRPressure
    property string     carInfoTyreRRPressure  :  CarInfoScreen.carInfoTyreRRPressure

    property string     carInfoTyreLFTemp  :  CarInfoScreen.carInfoTyreLFTemp
    property string     carInfoTyreRFTemp  :  CarInfoScreen.carInfoTyreRFTemp
    property string     carInfoTyreLRTemp  :  CarInfoScreen.carInfoTyreLRTemp
    property string     carInfoTyreRRTemp  :  CarInfoScreen.carInfoTyreRRTemp

    property bool     carInfoTyreLFWarning  :  CarInfoScreen.carInfoTyreLFWarning
    property bool     carInfoTyreRFWarning  :  CarInfoScreen.carInfoTyreRFWarning
    property bool     carInfoTyreLRWarning  :  CarInfoScreen.carInfoTyreLRWarning
    property bool     carInfoTyreRRWarning  :  CarInfoScreen.carInfoTyreRRWarning

    property bool     carInfoTyresLFWarning  :  CarInfoScreen.carInfoTyresLFWarning
    property bool     carInfoTyresRFWarning  :  CarInfoScreen.carInfoTyresRFWarning
    property bool     carInfoTyresLRWarning  :  CarInfoScreen.carInfoTyresLRWarning
    property bool     carInfoTyresRRWarning  :  CarInfoScreen.carInfoTyresRRWarning

    property bool     carInfoTyreLFVisible  :  CarInfoScreen.carInfoTyreLFVisible
    property bool     carInfoTyreRFVisible  :  CarInfoScreen.carInfoTyreRFVisible
    property bool     carInfoTyreLRVisible  :  CarInfoScreen.carInfoTyreLRVisible
    property bool     carInfoTyreRRVisible  :  CarInfoScreen.carInfoTyreRRVisible

    property bool     carInfoTyreTempLFWarning  :  CarInfoScreen.carInfoTyreTempLFWarning
    property bool     carInfoTyreTempRFWarning  :  CarInfoScreen.carInfoTyreTempRFWarning
    property bool     carInfoTyreTempLRWarning  :  CarInfoScreen.carInfoTyreTempLRWarning
    property bool     carInfoTyreTempRRWarning  :  CarInfoScreen.carInfoTyreTempRRWarning

    property bool     carInfoTyreTempLFVisible  :  CarInfoScreen.carInfoTyreTempLFVisible
    property bool     carInfoTyreTempRFVisible  :  CarInfoScreen.carInfoTyreTempRFVisible
    property bool     carInfoTyreTempLRVisible  :  CarInfoScreen.carInfoTyreTempLRVisible
    property bool     carInfoTyreTempRRVisible  :  CarInfoScreen.carInfoTyreTempRRVisible


    property int isMidAreaScreenIndex: Manager.isMidAreaScreenIndex
    property string   tyrePressureUnit             : "kPa"
    property string   tyreTempUnit             : "℃"

    Loader{
        id: loaderTyre
        active: isMidAreaScreenIndex===3
        sourceComponent: comTyre
        onLoaded: {
            active = true
        }
    }

    Component{
        id: comTyre
        Item{
            width: 1920
            height: 720
            visible: isMidAreaScreenIndex===3
            Image {
                x: 639; y: 202
                source: "ADAS_BG_Tire.png"
            }
            Image {
                x: 908; y: 312
                source: "ADAS_IMG_Tire_Car.png"
            }
            CustomText{
                x: 895.7; y: 233
                font.pixelSize: 32
                text: trLanguge("胎压检测")
                opacity: 0.7
            }
            //press
            CustomText{//左前
                id:lfPreUnitTxt
                x:820;y:329
                font.pixelSize: 20
                text: tyrePressureUnit
                color: carInfoTyreLFWarning?"red":"white"
                visible: carInfoTyreLFVisible
                CustomText{
                    anchors.right: parent.left
                    anchors.rightMargin: 6
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -2
                    font.pixelSize: 26
                    text: carInfoTyreLFPressure
                    color: carInfoTyreLFWarning?"red":"white"
                }
            }

            CustomText{//左后
                id:lrPreUnitTxt
                x:820;y:488
                font.pixelSize: 20
                text: tyrePressureUnit
                color: carInfoTyreLRWarning?"red":"white"
                visible: carInfoTyreLRVisible
                CustomText{
                    anchors.right: parent.left
                    anchors.rightMargin: 6
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -2
                    font.pixelSize: 26
                    text: carInfoTyreLRPressure
                    color: carInfoTyreLRWarning?"red":"white"
                }
            }

            CustomText{//右前
                id:rfPreTxt
                x: 1063; y: 324
                font.pixelSize: 26
                text: carInfoTyreRFPressure
                color: carInfoTyreRFWarning?"red":"white"
                visible: carInfoTyreRFVisible
                CustomText{
                    anchors.left: parent.right
                    anchors.leftMargin: 6
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 2
                    font.pixelSize: 20
                    text: tyrePressureUnit
                    color: carInfoTyreRFWarning?"red":"white"
                }
            }

            CustomText{//右后
                id:rrPreTxt
                x: 1063; y: 483
                font.pixelSize: 26
                text: carInfoTyreRRPressure
                color: carInfoTyreRRWarning?"red":"white"
                visible: carInfoTyreRRVisible
                CustomText{
                    anchors.left: parent.right
                    anchors.leftMargin: 6
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 2
                    font.pixelSize: 20
                    text: tyrePressureUnit
                    color: carInfoTyreRRWarning?"red":"white"
                }
            }
            //temp
            CustomText{//左前
                id:lftempUnitTxt
                x:836;y:360
                font.pixelSize: 20
                text: tyreTempUnit
                color: carInfoTyreTempLFWarning?"red":"white"
                visible: carInfoTyreTempLFVisible
                CustomText{
                    anchors.right: parent.left
                    anchors.rightMargin: 3
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -2
                    font.pixelSize: 26
                    text: carInfoTyreLFTemp
                    color: carInfoTyreTempLFWarning?"red":"white"
                }
            }

            CustomText{//左后
                id:lrtempUnitTxt
                x:836;y:519
                font.pixelSize: 20
                text: tyreTempUnit
                color: carInfoTyreTempLRWarning?"red":"white"
                visible: carInfoTyreTempLRVisible
                CustomText{
                    anchors.right: parent.left
                    anchors.rightMargin: 3
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -2
                    font.pixelSize: 26
                    text: carInfoTyreLRTemp
                    color: carInfoTyreTempLRWarning?"red":"white"
                }
            }

            CustomText{//右前
                id:rftempTxt
                x: 1066; y: 355
                font.pixelSize: 26
                text: carInfoTyreRFTemp
                color: carInfoTyreTempRFWarning?"red":"white"
                visible: carInfoTyreTempRFVisible
                CustomText{
                    anchors.left: parent.right
                    anchors.leftMargin: 3
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 2
                    font.pixelSize: 20
                    text: tyreTempUnit
                    color: carInfoTyreTempRFWarning?"red":"white"
                }
            }

            CustomText{//右后
                id:rrtempTxt
                x: 1066; y: 514
                font.pixelSize: 26
                text: carInfoTyreRRTemp
                color: carInfoTyreTempRRWarning?"red":"white"
                visible: carInfoTyreTempRRVisible
                CustomText{
                    anchors.left: parent.right
                    anchors.leftMargin: 3
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 2
                    font.pixelSize: 20
                    text: tyreTempUnit
                    color: carInfoTyreTempRRWarning?"red":"white"
                }
            }

            //icon
            Image{//左前
               x: 871; y: 327
               source: carInfoTyresLFWarning?"ADAS_IMG_Tire_FL_Warning.png":"ADAS_IMG_Tire_FL_Normal.png"
               visible: true
            }
            Image{//左后
               x: 871; y: 485
               source: carInfoTyresLRWarning?"ADAS_IMG_Tire_BL_Warning.png":"ADAS_IMG_Tire_BL_Normal.png"
               visible: true
            }
            Image{//右前
               x: 1000; y: 327
               source: carInfoTyresRFWarning?"ADAS_IMG_Tire_FR_Warning.png":"ADAS_IMG_Tire_FR_Normal.png"
               visible: true
            }
            Image{//右后
               x: 1000; y: 485
               source: carInfoTyresRRWarning?"ADAS_IMG_Tire_BR_Warning.png":"ADAS_IMG_Tire_BR_Normal.png"
               visible: true
            }
            //line
//            Rectangle{//左前
//                x: 163; y: 338
//                width: 19; height: 1
//            }
//            Rectangle{//左后
//                x: 163; y: 505
//                width: 19; height: 1
//            }
//            Rectangle{//右前
//                x: 314; y: 338
//                width: 19; height: 1
//            }
//            Rectangle{//右后
//                x: 314; y: 505
//                width: 19; height: 1
//            }
        }
    }
}
