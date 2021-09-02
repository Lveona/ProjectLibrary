import QtQuick 2.8
import qmlEnums 1.0

Item {
    id: root
    visible: isPowerMode === ManagerEnums.QML_POWERMODE_D1
    width: 1920
    height: 720
    scale: 1
    objectName: "root"
    opacity: 0

    MouseArea{
        anchors.fill: parent
        enabled: platform === "win"
        property real sx: 0
        onPressed: {
            sx = mouseX
        }

        onPositionChanged: {
            rectBg.x += -(sx-mouseX)
            sx = mouseX
        }
    }

    property bool isComponent: false
    property bool isUpdate: LangugeManage.langugeChengeSW==="CN"       //CN=true,EN=false
    property string changeNofity: LangugeManage.langugeChengeSW

    property bool enterLoaderOver: false
    property string limitSpeed: PopupScreen.limitSpeed
    property var miniAdas: ADASScreen.miniAdasVisible

//------------------导航互联-----------------------------------

    property bool navStatus: {
        enterLoaderOver && navigationMapMod === InterconnectScreenEnums.SMALL_MAP
    }
    property bool adasLoaderIsShow: navStatus  ;
    property bool miniAdasVisible: {
       enterLoaderOver && (navigationMapMod === InterconnectScreenEnums.BIG_MAP || navigationMapMod === InterconnectScreenEnums.AR_MAP || chargeConn) && miniAdas
    }

    //6 主题切换
    property int themeSetting: SettingScreen.themeSetting
    onThemeSettingChanged:{
        if(themeSetting ===  SettingScreenEnums.COMFORT || themeAnimationRunning)
            return ;
        startExitAnim();
    }

//------------------导航互联-----------------------------------

    property int isPowerMode: Manager.receiveCtrlPowerMode
    onIsPowerModeChanged: {
        printwarn(" onIsPowerModeChanged:"+isPowerMode);
        if(isPowerMode == ManagerEnums.QML_POWERMODE_D1){
            startD1Anim();
        }

        if(!isComponent){
            printwarn(" isComponent return");
            return;
        }

        if(enterLoaderOver){
            printwarn(" enterLoaderOver return");
            return;
        }
//        //入场动画执行中
//        if(enterAnimStateStart){
//            printwarn(" enterAnimStateStart return");
//            return;
//        }

        if(isPowerMode === ManagerEnums.QML_POWERMODE_D1){
            startD1Anim();
        }
        else if(isPowerMode === ManagerEnums.QML_POWERMODE_D2){
            enterLoaderOver = false;
            Manager.showAnimOver = enterLoaderOver;
            startD2Anim();
        }
    }

    function startD1Anim(){
        printwarn(" startD1Anim ");
        homeloader.active = true;
    }

    function startD2Anim(){
        printwarn(" startD2Anim ");
//        startLoaderDoorStatus();
    }

    property int sceneNumberBackup: 0

    function printwarn(log)
    {
        Manager.qmlPrintLog(log)
    }

    function trLanguge(v)
    {
        var s = isUpdate?qsTr(v):qsTr(v)
        s = s.replace("xx",limitSpeed)
        s = s.replace("\\n", "\n")
        return s
    }
    function trLangugeDayDisPop(v,u)
    {
        var s = trLanguge(v);//isUpdate?qsTr(v):qsTr(v)
        s = s.replace("\\n", "\n")
        s = s.replace("\\n", "\n")

        if(v === "正在拨号给 XXX")
        {
        s = s.replace("XXX", u)
        }else if(v === "近XXXkm电耗")
        {
        s = s.replace("XXX", u)
        }

        return s
    }

    function trLangugeForWarnList(v)
    {
        var s = isUpdate?qsTr(v):qsTr(v)
        s = s.replace("\\n", " ")
        return s
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
        printwarn("gauge Component.onCompleted")
        isComponent = true
    }

    Item{
        id: rectBg
        width: 1920
        height: 720

        Image{
            id: powerD1Bg
            source: "qml/homeBg.png"
            asynchronous: true
            visible: navigationMapMod === InterconnectScreenEnums.SMALL_MAP
            sourceSize.width: 1920
            sourceSize.height: 720
            Component.onCompleted: {
                printwarn("bgbg Component.onCompleted")
            }
        }

        Image{
            id: navD1Bg
            source: "qml/NAV_BG_BLACK.png"
            asynchronous: true
            visible: navigationMapMod !== InterconnectScreenEnums.SMALL_MAP
            sourceSize.width: 1920
            sourceSize.height: 720
            Component.onCompleted: {
                printwarn("nav Component.onCompleted")
            }

            Image {
                id: navBaseLineBG
                x:1
                y:518
                width: 1910
                height: 156
//                visible: false
                source: "qml/pic_HMI_Nav_default_baseline.png"
            }
        }

        Loader{
            id: adasLoader
            source: "qml/ADAS/ADAS.qml"
            active: enterLoaderOver
            visible: adasLoaderIsShow//enterLoaderOver
            onLoaded: {
                active = true
                printwarn("adasLoader Ready")
                interconnectLoader.active = true
            }
            asynchronous: true
        }

        Loader{
            id: popupLoader
            z: 2
            source: "qml/Popup/Popup.qml"
            visible: enterLoaderOver
            onLoaded: {
                active = true
                printwarn("popupLoader Ready")
                carInfoLoader.active = true;
            }
            asynchronous: true
        }


        Loader{
            id: homeloader
            z: 1
            active: true
            visible: enterLoaderOver
            source: "qml/Home/Home.qml"
            onLoaded: {
                active = true
                printwarn("homeloader Ready")
                popupLoader.active = true;
            }
            asynchronous: true
        }

        Loader{
            id: carInfoLoader
            z:1
            source: "qml/CarInfo/CarInfo.qml"
            visible: enterLoaderOver
            onLoaded: {
                active = true
                printwarn("carInfoLoader Ready")
                adasLoader.active = true;
            }
            asynchronous: true
        }

        Loader{
            id: interconnectLoader
            source: "qml/Interconnect/Interconnect.qml"
            visible: enterLoaderOver
            onLoaded: {
                active = true
                printwarn("interconnectLoader Ready")

                //3 gauge 入场动画开始执行
                startEnterAnim();
            }
            asynchronous: true
        }

        //充电画面
        Loader{
            id: chargeConnLoader
            source: "qml/Charging/Charging.qml"
            visible: chargeConn
            active: chargeConn
            onLoaded: {
                active = true
                printwarn("chargeConnLoader Ready")
            }
        }

        Loader{
            id:miniAdasLoader
            z:2
            source: "qml/ADAS/MiniADAS.qml"
            visible: miniAdasVisible
            active: miniAdasVisible
            onLoaded: {
                active = true
                printwarn("miniAdasLoader Ready")
            }
        }


        Loader{
            id: diagloader
            z: 10
            visible: enterLoaderOver
            source: "qml/Diag/Diag.qml"
        }
    }

    Loader{
        id: updateloader
        active: 4 !== Update_Thread.messageType
        z: 11
        source: "UpdateScreen.qml"
        onLoaded: {
            active = true
        }
    }

    function startEnterAnim() {
        //4 通知 Point 执行入场动画
        Manager.enterAnimStart = true
        //Gauge 入场动画开始执行
        enterAnim.restart();
    }

    function handleEnterAnimOver(){
        console.log("qml 入场动画执行完毕")
        outAnimationState = false;
        themeAnimationRunning = false;
        //判断当前主题不同步 再次执行出场动画切换主题
        if(themeSetting !==  SettingScreenEnums.COMFORT) {
            console.log("因主题不同步重新执行出场动画")
            startExitAnim();
        }
    }

    function startExitAnim() {
        themeBackIndex = themeSetting;
        themeAnimationRunning = true;
        exitAnim.restart();
    }

    PropertyAnimation {
        target: root
        property :"opacity"
        id : enterAnim
        running: false
        from: 0
        to : 1
        easing.type: Easing.Linear
        onStarted: {
            enterLoaderOver = true;
            console.log("入场动画开始执行" + root.opacity)
        }

        onStopped: {
            root.opacity = 1;
            handleEnterAnimOver();
        }
        duration : 3000
    }

    PropertyAnimation  {
        id : exitAnim
        target: root
        property :"opacity"
        running: false
        from: 1
        to : 0
        onStarted: {
            console.log("出场动画开始执行")
            Manager.enterAnimStart = false;
        }

        onStopped:{
            // 7 出场动画执行完毕切换RCC
            root.opacity = 0;
            console.log("出场动画执行完毕")
            outAnimationState = true;
        }
        duration : 3000
    }

}
