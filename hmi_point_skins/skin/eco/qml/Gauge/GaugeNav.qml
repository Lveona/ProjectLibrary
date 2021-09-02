import QtQuick 2.0
import qmlEnums 1.0
import "./../Common/"

Item {
    id: gaugeNav
    width: 1920
    height: 720
    CustomText {
        x:17
        y:583
        width:165
        height:52
        text:Math.floor(digitSpeedAnim)
        font.pixelSize: 70
    }

    CustomText {
        x:198
        y:614
        width: 94
        height: 24
        opacity: 0.6
        color: "#e3e3e3"
        text:"km/h"
        font.pixelSize: 30
    }

    CustomText {
        x:1616
        y:619
        width: 125
        height: 17
        opacity: 0.6
        color: "#e3e3e3"
        text:"PWR(%)"
        font.pixelSize: 24
    }

    CustomText {
        x:1736
        y:585
        width:167
        height:52
        text:Math.floor(powerAnim)
        font.pixelSize: 70
    }
    SequentialAnimation{
        id:naviShowAni
        onStarted: {
            gaugeNav.opacity = 0.0;
        }
        PauseAnimation {
            duration: 5000
        }
        PropertyAnimation{
             target:gaugeNav;property: "opacity"; from: 0.0; to: 1.0; duration: 1000; easing.type: Easing.Linear;}
        PauseAnimation {
            duration: 1000
        }
    }
    SequentialAnimation{
        id:naviHideAni
        onStarted: {
            gaugeNav.opacity =1.0;
        }
        PauseAnimation {
            duration: 1000
        }
        PropertyAnimation{
            target:gaugeNav; property: "opacity"; from: 1.0; to: 0.0; duration: 1000; easing.type: Easing.Linear;}
        PauseAnimation {
            duration: 1000
        }
    }

    function naviShow(){
        naviHideAni.start()
    }
    function naviHide(){
        naviShowAni.start()
    }
}
