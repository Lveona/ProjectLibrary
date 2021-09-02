import QtQuick 2.8
import qmlEnums 1.0

Item {
    id: root
    visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1//true
    width: 1920
    height: 720
    scale: 1
    objectName: "root"
    opacity:1

    MouseArea{
        anchors.fill: parent
        enabled:platform === "win"
        property real sx: 0
        onPressed: {
            sx = mouseX
        }

        onPositionChanged: {
            root.x += -(sx-mouseX)
            sx = mouseX
        }
    }

    //主题切换
    property int themeSetting: Manager.themeSetting
    property bool isThemeSetting: false

    onThemeSettingChanged:{
        //3 QML 中当主题切换
        if(themeSetting === ManagerEnums.SPORT || themeAnimationRunning) //防止重复出场动画
            return ;
        startExitAnim();
    }

    property bool enterAnimFromManager: Manager.enterAnimStart
    onEnterAnimFromManagerChanged:{
        if(enterAnimFromManager){
            startEnterAnim();
        }
    }

//    property bool isUpdate: LangugeManage.langugeChengeSW==="CN"       //CN=true,EN=false
//    property string changeNofity: LangugeManage.langugeChengeSW


//    property bool enterAnim: false


//    onEnterAnimFromManagerChanged: {
//        //gauge通知point入场动画开始
//        if(enterAnimFromManager){
//            timerLoader.restart()
//            enterAnim = true
//        }
//        //动画同步由 gauge 发送该信号恢复初始状态
//        outAnimationState = false;
//    }

//    //因为point快,特意慢一会,便于启动时候同步
//    Timer{
//        id: timerLoader
//        interval: 300
//        onTriggered: {
//            enterAnim = true
//        }

//    }

    function printwarn(log)
    {
        Manager.qmlPrintLog(log)
    }

    function addZero(value){
        if(value<10){
            return '0'+value
        }
        else{
            return value
        }
    }

    Component.onCompleted: {
    }

    Item{
        id: rectBg
        anchors.fill: parent
        visible: Manager.hmiVisible && Manager.hmiScreenState

        Loader{
            id: telltaleloader
            active: true
//            visible: enterAnim && isGaugeLoaded
            source: "qml/Telltale/Telltales.qml"
            onLoaded: {
                printwarn("point telltaleloader Ready")
                gaugeloader.active = true
//                Manager.isLoaderOver = true; //画面加载完通知Manager自检开始
            }
            asynchronous: true
        }

        Loader{
            id: gaugeloader
            active: false
            //visible: enterAnim
            source: "qml/Gauge/Gauge.qml"
            onLoaded: {
                printwarn("point gaugeloader Ready")
                active = true
                if(Manager.navigationMapMod ===  ManagerEnums.SMALL_MAP){
                    if(!isThemeSetting){
                        isThemeSetting = true;
                        item.gaugeAnim_start()
                    }
                }
            }
            asynchronous: true
        }

    }

    function startEnterAnim() {
        //Gauge来的信号 入场动画开始执行
        //Gauge 入场动画开始执行
        if(Manager.navigationMapMod === ManagerEnums.SMALL_MAP){
            if(!isThemeSetting&&gaugeloader.status === Loader.Ready)
            {
                gaugeloader.item.gaugeAnim_start();
                isThemeSetting = true

            }
            //enterAnim.restart();


        }
    }

    function handleEnterAnimOver(){
        console.log("qml 入场动画执行完毕")
        outAnimationState = false;
        themeAnimationRunning = false;
        //判断当前主题不同步 再次执行出场动画切换主题
        if(themeSetting !==  ManagerEnums.SPORT) {
            console.log("因主题不同步重新执行出场动画")
            startExitAnim();
        }
    }

    function startExitAnim() {
        isThemeSetting = true
        themeBackIndex = themeSetting;
        themeAnimationRunning = true;
        gaugeloader.item.endEnterAnim();
        //exitAnim.restart();
    }

//    PropertyAnimation {
//        target: root
//        property :"opacity"
//        id : enterAnim
//        running: false
//        from: 0
//        to : 1
//        onStarted: {
//            console.log("入场动画开始执行")
//        }

//        onStopped: {
//            root.opacity = 1;
//            handleEnterAnimOver();
//        }
//        duration : 3000
//    }

//    PropertyAnimation  {
//        id : exitAnim
//        target: root
//        property :"opacity"
//        running: false
//        from: 1
//        to : 0
//        onStarted: {
//            console.log("出场动画开始执行")
//        }

//        onStopped:{
//            root.opacity = 0;
//            console.log("出场动画执行完毕")
//            outAnimationState = true;
//        }
//        duration : 3000
//    }
}
