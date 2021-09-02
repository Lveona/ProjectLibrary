import QtQuick 2.8
import qmlEnums 1.0
import QtGraphicalEffects 1.0
import QtQuick.Shapes 1.15 //放在 import QtGraphicalEffects 1.0 下面

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

    property bool homeAnim: false

    //渐变的宽度
    property int valuewidht: 0

//------------------导航互联-----------------------------------

    property bool navStatus: {
        enterLoaderOver && navigationMapMod === InterconnectScreenEnums.SMALL_MAP
    }
    property bool adasLoaderIsShow: navStatus  ;
    property bool miniAdasVisible: {
       enterLoaderOver && (navigationMapMod === InterconnectScreenEnums.BIG_MAP || navigationMapMod === InterconnectScreenEnums.AR_MAP || chargeConn)
    }

    //6 主题切换
    property int themeSetting: SettingScreen.themeSetting
    onThemeSettingChanged:{
        if(themeSetting ===  SettingScreenEnums.ECO || themeAnimationRunning)
            return ;
        startExitAnim();
    }

    //入场动效
    function startComfortAnim(){
        //背景
        bgAnim_Start.start();
        //上边框
        anim_topline_ru.start();
    }

    //出场动效
    function endComfortAnim(){
        //背景
        bgAnim_End.start();
        //上边框
        anim_topline_chu.start();
    }

    //入场背景动效
    SequentialAnimation{
        id: bgAnim_Start
        NumberAnimation{ target: powerD1Bg; properties: "opacity"; duration: 1000; from: 0.0; to: 1.0}
    }

    //出场背景动效
    SequentialAnimation{
        id: bgAnim_End
        NumberAnimation{ target: powerD1Bg; properties: "opacity"; duration: 1000; from: 1.0; to: 0.0}
    }

    //topline入场动效
    Item {
        id: item_topline
        width: img_topline.sourceSize.width
        height: img_topline.sourceSize.height
        y:25
        x:514
        z:100

        Image {
            id: img_topline
            anchors.fill: parent
            source:  "qrc:/eco/qml/Home/topline.png"
            visible: false
        }

        Shape{
            id: topline_Shape
            anchors.fill: img_topline
            antialiasing: true //锯齿化
            smooth: true  //平滑
            layer.enabled: true
            layer.samples: 8
            visible: false

            //左侧渐变区域
            ShapePath {
                id: gradual_left
                strokeStyle: ShapePath.SolidLine
                fillGradient: LinearGradient {
                    x1: gradual_left_2.x
                    y1: 0
                    x2: gradual_left.startX
                    y2: 0
                    GradientStop { position: 0.0; color: "#FF0000";}
                    GradientStop { position: 1; color: "transparent";}
                }
                strokeColor: "transparent"
                strokeWidth: 0
                startX: gradual.startX - valuewidht
                startY: img_topline.sourceSize.height
                PathLine{
                    id: gradual_left_2; x: gradual_left.startX + valuewidht; y:img_topline.sourceSize.height
                }
                PathLine{
                    id:gradual_left_3; x: gradual_left.startX + valuewidht; y: 0
                }
                PathLine{
                    id:gradual_left_4; x: gradual_left.startX; y: 0
                }
            }

            //图片显示区域
            ShapePath {
                id: gradual
                strokeStyle: ShapePath.SolidLine
                fillColor: "#FF0000"
                strokeColor: "transparent"
                strokeWidth: 0
                startX: img_topline.sourceSize.width / 2
                startY: img_topline.sourceSize.height
                PathLine{
                    id:gradual_2
                    x: img_topline.sourceSize.width/2
                    y:img_topline.sourceSize.height
                }
                PathLine{
                    id:gradual_3
                    x: img_topline.sourceSize.width/2
                    y: 0
                }
                PathLine{
                    id:gradual_4
                    x: img_topline.sourceSize.width / 2
                    y: 0
                }
            }

            //右侧渐变区域
            ShapePath {
                id: gradual_right
                strokeStyle: ShapePath.SolidLine
                fillGradient: LinearGradient {
                    x1: gradual_right.startX
                    y1: 0
                    x2: gradual_right_2.x
                    y2: 0
                    GradientStop { position: 0.0; color: "#FF0000";}
                    GradientStop { position: 1; color: "transparent";}
                }

                strokeColor: "transparent"
                strokeWidth: 0
                startX: gradual_2.x
                startY: img_topline.sourceSize.height
                PathLine{
                    id:gradual_right_2; x: gradual_right.startX + valuewidht; y:img_topline.sourceSize.height
                }
                PathLine{
                    id:gradual_right_3; x: gradual_right.startX + valuewidht; y: 0
                }
                PathLine{
                    id:gradual_right_4; x: gradual_right.startX; y: 0
                }
            }

            SequentialAnimation {
                id: anim_topline_ru
//                running: anim_topline //运行
                PropertyAnimation{target: root; properties: "valuewidht"; from: 0; to: 100; duration: 100; }
                ParallelAnimation{
                    //属性动画-属性值改变播放的动画
                    PropertyAnimation{target: gradual; properties: "startX"; from: img_topline.sourceSize.width/2; to: 0; duration: 1000; }
                    PropertyAnimation{target: gradual_4; properties: "x"; from: img_topline.sourceSize.width/2; to: 0; duration: 1000; }

                    PropertyAnimation{target: gradual_2; properties: "x"; from: img_topline.sourceSize.width/2; to:  img_topline.sourceSize.width; duration: 1000; }
                    PropertyAnimation{target: gradual_3; properties: "x"; from: img_topline.sourceSize.width/2; to:  img_topline.sourceSize.width; duration: 1000; }
                }

                onStopped: {
                    homeloader.item.homeAnimStart()
                    scene3DAllAnimStart();
                }

                //只是为了测试循环初始化 需要注掉
//                ParallelAnimation{
//                //属性动画-属性值改变播放的动画
//                 PropertyAnimation{target: gradual; properties: "startX"; to: img_topline.sourceSize.width/2;  duration: 0; }
//                 PropertyAnimation{target: gradual_4; properties: "x"; to: img_topline.sourceSize.width/2; duration: 0; }

//                 PropertyAnimation{target: gradual_2; properties: "x"; to: img_topline.sourceSize.width/2;  duration: 0; }
//                 PropertyAnimation{target: gradual_3; properties: "x"; to: img_topline.sourceSize.width/2;  duration: 0; }
//                }
            }

            SequentialAnimation {
//                running: true
//                loops: Animation.Infinite
                //初始化 注掉
//                PropertyAnimation{target: root; properties: "valuewidht"; from: 0; to: 100; duration: 0; }

                ParallelAnimation{
                    id: anim_topline_chu
                    //属性动画-属性值改变播放的动画
                    PropertyAnimation{target: gradual; properties: "startX"; from: 0; to: img_topline.sourceSize.width/2; duration: 3000; }
                    PropertyAnimation{target: gradual_4; properties: "x"; from: 0; to: img_topline.sourceSize.width/2; duration: 3000; }

                    PropertyAnimation{target: gradual_2; properties: "x"; to: img_topline.sourceSize.width/2; from:  img_topline.sourceSize.width; duration: 3000; }
                    PropertyAnimation{target: gradual_3; properties: "x"; to: img_topline.sourceSize.width/2; from:  img_topline.sourceSize.width; duration: 3000; }
                }

                PropertyAnimation{target: root; properties: "valuewidht"; from: 100; to: 0; duration: 100; }
            }
        }

        OpacityMask {
            id:fcwMask
            anchors.fill: img_topline
            source: img_topline
            maskSource: topline_Shape
        }
    }


//------------------导航互联-----------------------------------

    property int isPowerMode: Manager.receiveCtrlPowerMode
    onIsPowerModeChanged: {
        printwarn(" onIsPowerModeChanged:"+isPowerMode);
//        if(isPowerMode == ManagerEnums.QML_POWERMODE_D1){
//            startD1Anim();
//        } else if(isPowerMode === ManagerEnums.QML_POWERMODE_D2){
//            startD2Anim();
//        }

        if(!isComponent){
            printwarn(" isComponent return");
            return;
        }

        if(!enterLoaderOver){
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
            //enterLoaderOver = false;
            //Manager.showAnimOver = enterLoaderOver;
            startD2Anim();
        }
    }

    function startD1Anim(){
        printwarn(" startD1Anim ");
        //透明度初始
        powerD1Bg.opacity = 0.0
        //homeAllAnim 初始化
        homeloader.item.opacity = 0.0
        //scene3D透明度 初始化
        scene3DOpacity = 0.0
        //topline透明度初始
        valuewidht = 0
        gradual.startX = img_topline.sourceSize.width/2;
        gradual_4.x = img_topline.sourceSize.width/2
        gradual_2.x = img_topline.sourceSize.width/2
        gradual_3.x = img_topline.sourceSize.width/2

        homeloader.active = true;
        adasLoader.item.roadsChanged();

    }

    function startD2Anim(){
        printwarn(" startD2Anim ");
        //topline初始
        valuewidht = 100
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

        Image{ //黑色背景
            id: blackBg
            source: "qml/black.png"
            asynchronous: true
            visible: navigationMapMod === InterconnectScreenEnums.SMALL_MAP
            sourceSize.width: 1920
            sourceSize.height: 720
            opacity: 1.0
            Component.onCompleted: {
                printwarn("bgbg Component.onCompleted")
            }
        }

        Image{
            id: powerD1Bg
            source: "qml/homeBg.png"
            asynchronous: true
            visible: navigationMapMod === InterconnectScreenEnums.SMALL_MAP
            sourceSize.width: 1920
            sourceSize.height: 720
            opacity: 0.0 //加载初始状态
            Component.onCompleted: {
                printwarn("bgbg Component.onCompleted")
            }
        }

        Image{
            id: navD1Bg
            source: "qml/pic_HMI_Nav_default_bg.png"
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
                item.roadsChanged()
            }
            asynchronous: true
        }

        // scene3D车模Loader
        Loader{
            id: scene3Dloader
            source: "../../Scene3D.qml"
            active: enterLoaderOver
            visible: enterLoaderOver
            onLoaded: {
                active = true
                printwarn("scene3DLoader Ready")
                scene3Dloader.active = true
            }
            asynchronous: true
        }

        Loader{
            id: popupLoader
//            parent: root1
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

        //导航页面、充电页面、运动主题下显示ADAS小窗
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
        if(themeSetting !==  SettingScreenEnums.ECO) {
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
