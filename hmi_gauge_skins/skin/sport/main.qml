import QtQuick 2.8
import qmlEnums 1.0
import QtGraphicalEffects 1.0
import QtQuick.Shapes 1.0
Item {
    id: root
    visible: isPowerMode === ManagerEnums.QML_POWERMODE_D1
    width: 1920
    height: 720
    scale: 1
    objectName: "root"
    opacity: 1.0

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
    //渐变的宽度
    property int valuewidht: 0

//------------------导航互联-----------------------------------

    property bool navStatus: {
        enterLoaderOver && navigationMapMod === InterconnectScreenEnums.SMALL_MAP
    }
    property bool adasLoaderIsShow: navStatus  ;
    property bool miniAdasVisible: {
       enterLoaderOver && (navigationMapMod === InterconnectScreenEnums.BIG_MAP || navigationMapMod === InterconnectScreenEnums.AR_MAP || chargeConn || themeSetting === SettingScreenEnums.SPORT)
    }

    //6 主题切换
    property int themeSetting: SettingScreen.themeSetting
    property bool isThemeSetting: false
    property int navigationMapMod: InterconnectScreen.navigationMapMod //地图模式
    property int navigationStatus: InterconnectScreen.navigationStatus //小地图下模式
    property int mediaPlayState: InterconnectScreen.mediaDataObject.playState;
    property bool isSmallMapShow:navigationMapMod === InterconnectScreenEnums.SMALL_MAP
                    && (navigationStatus === InterconnectScreenEnums.CRUISE_STATE ?
                    mediaPlayState !== MediaDataObjectEnums.PLAYING
                    && mediaPlayState !== MediaDataObjectEnums.PAUSE ? true : false :true)
    onThemeSettingChanged:{
        if(themeSetting ===  SettingScreenEnums.SPORT || themeAnimationRunning)
            return ;
        if(SettingScreen.currentPage === 3)
        {
            naviout.start();
        }else{
            startExitAnim();
        }
    }
    onNavigationMapModChanged: {
        if(InterconnectScreen.navigationMapMod === InterconnectScreenEnums.SMALL_MAP){
            naviout.start()

        } else if(SettingScreen.currentPage === 2){
            anim_chu.start();

        }
    }
    //topline动效
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
            source:  "qrc:/sport/qml/Home/topline.png"
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
            ParallelAnimation{
                id: anim_ru
                onStopped: {
                    homeloader.item.homeAnimStart();
                    enterLoaderOver =true;
                }
                //topline 入场动效
                SequentialAnimation {
                    id: anim_topline_ru
                    PropertyAnimation{target: root; properties: "valuewidht"; from: 0; to: 100; duration: 100; }
                    ParallelAnimation{
                        //属性动画-属性值改变播放的动画
                        PropertyAnimation{target: gradual; properties: "startX"; from: img_topline.sourceSize.width/2; to: 0; duration: 1000; }
                        PropertyAnimation{target: gradual_4; properties: "x"; from: img_topline.sourceSize.width/2; to: 0; duration: 1000; }

                        PropertyAnimation{target: gradual_2; properties: "x"; from: img_topline.sourceSize.width/2; to:  img_topline.sourceSize.width; duration: 1000; }
                        PropertyAnimation{target: gradual_3; properties: "x"; from: img_topline.sourceSize.width/2; to:  img_topline.sourceSize.width; duration: 1000; }
                    }
                }
                ParallelAnimation{
                    id: anim_bottomline_ru
                    //bottom line入场
                    PropertyAnimation{target: bottomLeftMask; property: "width"; from: bottomLeftMask.width; to: 0; duration: 500;  }

                    PropertyAnimation{target: bottomRightMask; property: "width"; from: bottomRightMask.width; to: 0; duration: 500; }
                    PropertyAnimation{target: bottomRightMask; property: "x"; from:1129; to: 1920; duration: 500; }
                }
            }
            ParallelAnimation{
                id: anim_Navi_ru
                //topline 入场动效
                SequentialAnimation {
                    PropertyAnimation{target: root; properties: "valuewidht"; from: 0; to: 100; duration: 100; }
                    ParallelAnimation{
                        //属性动画-属性值改变播放的动画
                        PropertyAnimation{target: gradual; properties: "startX"; from: img_topline.sourceSize.width/2; to: 0; duration: 1000; }
                        PropertyAnimation{target: gradual_4; properties: "x"; from: img_topline.sourceSize.width/2; to: 0; duration: 1000; }

                        PropertyAnimation{target: gradual_2; properties: "x"; from: img_topline.sourceSize.width/2; to:  img_topline.sourceSize.width; duration: 1000; }
                        PropertyAnimation{target: gradual_3; properties: "x"; from: img_topline.sourceSize.width/2; to:  img_topline.sourceSize.width; duration: 1000; }
                    }
                }
                onStopped: {
                    console.log("abcd")
                    homeloader.item.homeAnimStart();
                }
            }

            ParallelAnimation{
                id: anim_chu
                onStopped: {
                    if(isThemeSetting){
                        outAnimationState = true;
                    }
                    SettingScreen.currentPage = 0;
                    if(navigationMapMod !== InterconnectScreenEnums.SMALL_MAP){
                        naviIn.start()
                    }
                    if(themeSetting !==  SettingScreenEnums.SPORT && !themeAnimationRunning)
                    {
                        SkinManager.changeskin(themeSetting)
                        naviIn.start()
                    }else if(navigationMapMod === InterconnectScreenEnums.SMALL_MAP){
                        anim_ru_sport_start();
                    }
                }
                //topline 出场动效
                SequentialAnimation {
                    id: anim_topline_chu
                    ParallelAnimation{
                        //属性动画-属性值改变播放的动画
                        PropertyAnimation{target: gradual; properties: "startX"; from: 0; to: img_topline.sourceSize.width/2; duration: 500; }
                        PropertyAnimation{target: gradual_4; properties: "x"; from: 0; to: img_topline.sourceSize.width/2; duration: 500; }

                        PropertyAnimation{target: gradual_2; properties: "x"; to: img_topline.sourceSize.width/2; from:  img_topline.sourceSize.width; duration: 500; }
                        PropertyAnimation{target: gradual_3; properties: "x"; to: img_topline.sourceSize.width/2; from:  img_topline.sourceSize.width; duration: 500; }
                    }

                    PropertyAnimation{target: root; properties: "valuewidht"; from: 100; to: 0; duration: 100; }
                }
                ParallelAnimation{
                    id: anim_bottomline_chu
                    //bottom line出场
                    PropertyAnimation{target: bottomLeftMask; property: "width";from: 0;  to: 791; duration: 500;  }

                    PropertyAnimation{target: bottomRightMask; property: "width"; from: 0; to: 791;  duration: 500; }
                    PropertyAnimation{target: bottomRightMask; property: "x"; from: 1920;   to:1129;  duration: 500; }
                }
            }
            ParallelAnimation{
                id: anim_Navi_chu
                onStopped: {
                    if(isThemeSetting){
                        outAnimationState = true;
                    }
                    SettingScreen.currentPage = 0;
                    if(navigationMapMod !== InterconnectScreenEnums.SMALL_MAP){
                        naviIn.start()
                    }
                    if(themeSetting !==  SettingScreenEnums.SPORT && !themeAnimationRunning)
                    {
                        SkinManager.changeskin(themeSetting)
                        naviIn.start()
                    }else if(navigationMapMod === InterconnectScreenEnums.SMALL_MAP){
                        anim_ru_sport_start();
                    }
                }
                //topline 出场动效
                SequentialAnimation {
                    ParallelAnimation{
                        //属性动画-属性值改变播放的动画
                        PropertyAnimation{target: gradual; properties: "startX"; from: 0; to: img_topline.sourceSize.width/2; duration: 500; }
                        PropertyAnimation{target: gradual_4; properties: "x"; from: 0; to: img_topline.sourceSize.width/2; duration: 500; }

                        PropertyAnimation{target: gradual_2; properties: "x"; to: img_topline.sourceSize.width/2; from:  img_topline.sourceSize.width; duration: 500; }
                        PropertyAnimation{target: gradual_3; properties: "x"; to: img_topline.sourceSize.width/2; from:  img_topline.sourceSize.width; duration: 500; }
                    }

                    PropertyAnimation{target: root; properties: "valuewidht"; from: 100; to: 0; duration: 100; }
                }
            }
        }
        OpacityMask {
            id:fcwMask
            anchors.fill: img_topline
            source: img_topline
            maskSource: topline_Shape
        }
    }
    //topline出场动效
    function anim_topline_chu_Start(){
        if(SettingScreen.currentPage === 3){
            anim_Navi_chu.start()
        }else{
            anim_chu.start()
        }
    }
    function anim_ru_sport_start(){
        SettingScreen.currentPage = 2;
        anim_ru.start();
    }
    function anim_ru_navi_start(){
        SettingScreen.currentPage = 3;
        anim_Navi_ru.start();
    }
    function navD1BgHide_start(){
        navD1BgHide.start();
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
        if(homeloader.status === Loader.Ready){
            homeloader.item.opacity = 0.0
        }
        enterLoaderOver = true;
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
            source: isSmallMapShow?"qml/pic_HMI_classic_default_bg.png":"qml/homeBg.png"
            asynchronous: true
            visible: (SettingScreen.currentPage === 1||SettingScreen.currentPage === 2||SettingScreen.currentPage === 0)
            sourceSize.width: 1920
            sourceSize.height: 720
            Component.onCompleted: {
                printwarn("bgbg Component.onCompleted")
            }
        }
        Image{
            id: bottomLineImg
            visible: SettingScreen.currentPage !== 3
            x:0
            y:615
            width: 1920
            height: 105
            source: "qml/pic_HMI_sport_baseline.png"
        }

        Image {
            id: bottomLeftMask
            x:0
            y:615
            width:791
            height:105
            source: "qml/black_bg.png"
        }

        Image {
            id: bottomRightMask
            x:1129
            y:615
            width:791
            height:105
            source: "qml/black_bg.png"
        }

        Image{
            id: navD1Bg
            source: "qml/NAV_BG_BLACK.png"
            asynchronous: true
            visible: SettingScreen.currentPage === 3
            sourceSize.width: 1920
            sourceSize.height: 720
            Component.onCompleted: {
                printwarn("nav Component.onCompleted")
            }
        }
        Image {
            id:mask_top
            source: "qml/Interconnect/Navi/mask_top.png"
            visible:SettingScreen.currentPage===3
        }
        Image {
            id: navBaseLineBG
            x:1
            y:518
            width: 1910
            height: 156
            visible:SettingScreen.currentPage === 3
            source: "qml/pic_HMI_Nav_default_baseline.png"
        }

        Image {
            id: navBaseLineBGMask1
            x:0
            y:518
            visible: SettingScreen.currentPage === 3
            source: "qml/black_bg.png"
        }

        Image {
            id: navBaseLineBGMask2
            x:955
            y:518
            visible:SettingScreen.currentPage === 3
            source: "qml/black_bg.png"
        }
        Loader{
            id: popupLoader
            parent: rootMain
            z: 2
            source: "qml/Popup/Popup.qml"
            visible: enterLoaderOver
            active: false
            onLoaded: {
                active = true
                printwarn("popupLoader Ready")
                carInfoLoader.active = true;
            }
            asynchronous: true
        }



        Loader{
            id: carInfoLoader
            z:1
            source: "qml/CarInfo/CarInfo.qml"
            visible: enterLoaderOver
            active: false
            onLoaded: {
                active = true
                printwarn("carInfoLoader Ready")
                interconnectLoader.active = true;
            }
            asynchronous: true
        }

        Loader{
            id: interconnectLoader
            source: "qml/Interconnect/Interconnect.qml"
            visible: enterLoaderOver
            active: false
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
            z: 3
            parent: rootMain
            source: "qml/Charging/Charging.qml"
            visible: chargeConn
            active: chargeConn
            onLoaded: {
                active = true
                printwarn("chargeConnLoader Ready")
            }
        }

        Loader{
            id: homeloader
            z: 3
			parent: rootMain
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
            parent: rootMain
            z: 10
            visible: enterLoaderOver
            source: "qml/Diag/Diag.qml"
        }
    }

    Loader{
        id: updateloader
        active: 4 !== Update_Thread.messageType
        z: 11
        parent: rootMain
        source: "UpdateScreen.qml"
        onLoaded: {
            active = true
        }
    }

    function startEnterAnim() {
        //4 通知 Point 执行入场动画
        Manager.enterAnimStart = true
        isThemeSetting = true
        //Gauge 入场动画开始执行
        if(homeloader.status === Loader.Ready){
            homeloader.item.opacity = 0.0
            enterLoaderOver = true;

        }
        if(navigationMapMod === InterconnectScreenEnums.SMALL_MAP)
        {
            anim_ru_sport_start();
        }else{
            navD1Bg.opacity = 1.0
            naviIn.start();
        }
    }

    function handleEnterAnimOver(){
        console.log("qml 入场动画执行完毕")
        outAnimationState = false;
        enterLoaderOver = true;
        themeAnimationRunning = false;
        isThemeSetting = true

        //判断当前主题不同步 再次执行出场动画切换主题
        if(themeSetting !==  SettingScreenEnums.SPORT) {
            console.log("因主题不同步重新执行出场动画")
            startExitAnim();
        }
    }

    function startExitAnim() {
        themeBackIndex = themeSetting;
        themeAnimationRunning = true;
        homeloader.item.homeAnimEnd()  //home出场动效
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
    //导航入场
    SequentialAnimation{
        id:naviIn
        onStarted:{
            navD1Bg.opacity = 1.0
            homeloader.item.opacity = 0.0
            SettingScreen.currentPage = 3;
            bottomLeftMask.width =0;
            bottomRightMask.width =0;
            if(naviout.running)
            {
                naviout.stop();
            }
            anim_ru_navi_start();
        }
        onStopped: {
            themeAnimationRunning = false;
        }
        ParallelAnimation{
            //左侧黑块
            NumberAnimation {
                target: navBaseLineBGMask1
                from: 1000
                to: 0
                property: "width"
                duration: 1000
            }
            //右侧黑块
            NumberAnimation {
                target: navBaseLineBGMask2
                from: 955
                to: 1910
                property: "x"
                duration: 1000
            }
            NumberAnimation {
                target: navBaseLineBGMask2
                from: 955
                to: 0
                property: "width"
                duration: 1000
            }
        }
    }
    //画面渐隐
    NumberAnimation {
        id:navD1BgHide;
        onStopped: {
             handleEnterAnimOver();
        }
        target: navD1Bg; duration: 1000; properties: "opacity"; from: 1.0; to: 0.0;
    }

    //画面渐显+topline
    NumberAnimation {
        id:navD1BgShow ;
        onStopped: {
            homeloader.item.homeAnimEnd();
        }
        target: navD1Bg;
        duration: 1000;
        properties: "opacity";
        from: 0.0;
        to: 1.0;
    }

    //导航出场
    SequentialAnimation{
        id:naviout
        onStarted: {
            if(naviIn.running)
            {
                naviIn.stop();
            }
            navD1BgShow.start();
        }
        //等待home出场
        PauseAnimation {
            duration: 1000
        }
        ParallelAnimation{
            //左侧黑块
            NumberAnimation {
                target: navBaseLineBGMask1
                from: 0
                to: 1000
                property: "width"
                duration: 1000
            }
            //右侧黑块
            NumberAnimation {
                target: navBaseLineBGMask2
                from:1910
                to:  955
                property: "x"
                duration: 1000
            }
            NumberAnimation {
                target: navBaseLineBGMask2
                from: 0
                to: 955
                property: "width"
                duration: 1000
            }
        }
    }
}
