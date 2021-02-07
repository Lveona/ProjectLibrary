import QtQuick 2.0
import "../Common"

Item {

    property var chargeValue: HomeScreen.chargeValue//剩余电量值
    property var chargeAnimState : HomeScreen.chargeAnimState //剩余电量动画是否执行
    property var chargeColor : HomeScreen.chargeColor //进度条颜色

    property real socMax: 100
    property real animStart   : 0
    property real socAnimTime   : 0

    property real chargeValueAnim:0
    property string elecPercentTxt: ""

    onChargeAnimStateChanged: {
        socAnimFunc()
    }

    onChargeValueChanged: {
        socAnimFunc()
    }

    function socAnimFunc(){
        var t = chargeValue
        if(chargeValue === "--"){
            t = 0
        }
        elecPercentTxt = chargeValue
        animStart = t/100
        chargeValueAnim = animStart
        if(chargeAnimState){
            socAnimTime = t / socMax * 5000
            socChargeAnim.restart()
        }else{
            if(socChargeAnim.running){
                socChargeAnim.stop()
            }
        }
    }

    //电量Animation
    SequentialAnimation{
        id: socChargeAnim
        loops: Animation.Infinite
        PropertyAnimation{target:home; property: "chargeValueAnim"; from: animStart; to: 1; duration: socAnimTime; }
        PropertyAnimation{target:home; property: "chargeValueAnim"; to: animStart; duration: socAnimTime; }
    }

    //电量
    Loader{
        id: socLoader
        active: true//Manager.receiveCtrlPowerMode == ManagerEnums.QML_POWERMODE_D1
        sourceComponent: socComponent
        onLoaded: {
            active = true
            socAnimFunc()
        }
    }
    Component{
        id: socComponent
        Item{
            id: socItm
            anchors.fill: parent

            property alias itemBlue: itemBlue
            property alias socProgressGray: socProgressGray

            //低电量报警
            Image{ x: 1095; y: 625;
                source: "lowPowerWar_gray.png"
            }

            CustomText{
                anchors.right: elecPercent.left
                y: 626
                font.pixelSize: 30
                text: elecPercentTxt
            }
            CustomText{
                id: elecPercent
                x: 1295; y: 627
                font.pixelSize: 30
                text: "%"
            }
            Image {
                id: socProgressGray
                source:"progressBar_gray.png"
                x: 1091
                y: 657

                Item{
                    id: itemBlue
                    height: socProgress.height
                    width: chargeValue === "--" ? 0 : chargeValueAnim*socProgressGray.sourceSize.width
                    anchors.verticalCenter: parent.verticalCenter
                    clip: true
                    anchors.left: parent.left

                    Image {
                        id: socProgress
                        anchors.left: parent.left
                        source: if(chargeColor === COLORTYPEEnums.COLORTYPEQML_RED){
                                    "progressBar_red.png"
                                }else if(chargeColor === COLORTYPEEnums.COLORTYPEQML_YELLOW){
                                    "progressBar_yellow.png"
                                }else if(chargeColor === COLORTYPEEnums.COLORTYPEQML_GREEN){
                                    "progressBar_green.png"
                                }else{
                                    "progressBar_headlight.png"
                                }
                    }
                }
            }
        }
    }
}
