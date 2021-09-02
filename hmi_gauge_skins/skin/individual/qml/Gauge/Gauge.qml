import QtQuick 2.8
//import QtQuick.Controls 1.4
import qmlEnums 1.0
import "./../Common/"

Item {
    id: gauge
    visible: true
    width: 1920
    height: 720


//    property string gear:GaugeScreen.gear     //0-240

//    property string m :gear.substring(0,1)

//    property string num :gear.substring(1,1)

//    property string rotationSpeed:GaugeScreen.rotationSpeedValue   //0-7000

//    property string waterTemp:GaugeScreen.waterTemp
//    property string oilValue:GaugeScreen.oilValue

//    property real waterTempAnim: 0
//    property real oilValueAnim: 0

//    property real waterTempAnimTime: 0
//    property real oilValueAnimTime: 0

//    function changeWaterTemp(){
//        waterTempAnimTime = Math.abs(Number(waterTemp) - Number(waterTempAnim)) / 100 * 3000
//        waterTempAnim = Number(waterTemp)
//    }
//    function changeOilValue(){
//        oilValueAnimTime = Math.abs(Number(oilValue) - Number(oilValueAnim)) / 100 * 3000
//        oilValueAnim = Number(oilValue)
//    }

//    onWaterTempChanged: {
//        changeWaterTemp()
//    }
//    onOilValueChanged: {
//       changeOilValue()
//    }

//    Behavior on waterTempAnim {
//        id: behaviorWaterTempAnim
//        NumberAnimation { duration: waterTempAnimTime; easing.type: Easing.OutQuad; }
//    }
//    Behavior on oilValueAnim {
//        id: behaviorOilValueAnim
//        NumberAnimation { duration: oilValueAnimTime; easing.type: Easing.OutQuad; }
//    }

//    property bool waterTempWarning: GaugeScreen.waterTempWarning
//    property bool oilWarning: GaugeScreen.oilValueWarning

//    property var qmlPowerMode: Manager.receiveCtrlPowerMode
//    onQmlPowerModeChanged: {
//        if(qmlPowerMode === ManagerEnums.QML_POWERMODE_D1){
//            animAboutOilAndWater()
//        }
//    }

//    function animAboutOilAndWater(){
//        behaviorWaterTempAnim.enabled = behaviorOilValueAnim.enabled = false
//        waterTempAnim = oilValueAnim = 0

//        behaviorWaterTempAnim.enabled = behaviorOilValueAnim.enabled = true

//        changeWaterTemp()
//        changeOilValue()
//    }

//    Item{
//        x:405
//        y:70
//        width: imgQuan.width
//        height: imgQuan.height
//        anchors.centerIn: parent
//        //visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1

//        Image {
//            id: imgQuan
//            source: "quanBg.png"
//        }

//        Point{
//            id: left
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.bottom: parent.bottom
//            pointAngle: Number(oilValueAnim)
//            isWarning: oilWarning
//        }

//        Point{
//            id: right
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.bottom: parent.bottom
//            pointAngle: Number(waterTempAnim)
//            direction: -1
//            isWarning: waterTempWarning
//        }
//    }

//    Item{
//        width: imgGearBg.width
//        height: imgGearBg.height
//        anchors.horizontalCenter: parent.horizontalCenter
//        y: 599
//        //visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1

//        Image{
//           id: imgGearBg
//           source: "gearBg.png"
//        }

//        Image{
//            id:imgGear
//            source: {
//                if(GaugeScreen.gear !== "")
//                {
//                    if(gear==="--")
//                    {
//                        "Circle_Icon_Gear_Null.png"
//                    }
//                    else
//                    {
//                        "Circle_Icon_Gear_"+ gear.subString(0,1)+".png"
//                    }
//                }
//                else{""}
//            }
//        }
//    }

//    Item {
//        //visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
//        Image {
//            id: water
//            x:1240
//            y:507-30
//            source: "Circle_Icon_Water.png"
//        }
//        Image {
//            id: temp
//            x:627
//            y:507-30
//            source: "Circle_Icon_Oil.png"
//        }
//    }

}
