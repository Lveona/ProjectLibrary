import QtQuick 2.8
//import QtQuick.Controls 1.0
import qmlEnums 1.0

Item {
    id: root
//    visible: Manager.hmiScreenState
    width: 1920
    height: 720

    /***************************************************************加载字体***************************************************************/
    Timer{
        interval: 10
        running: true
        onTriggered: {
            console.log("point start load font")
            fontloader.source = fontPath + "Eurostile_LT_Extended.ttf"
        }
    }

    FontLoader{
        id:fontloader
        onStatusChanged: {
            if(FontLoader.Ready == status){
                console.log("point finish load font")
                loader.source = Qt.binding(function(){ return SkinManager.currentSkin })
            }
        }
    }
    /***************************************************************************************************************************************/

    property bool outAnimationState: false
    onOutAnimationStateChanged:{
        if(outAnimationState) {
            //卸载并加载RCC
            //SkinManager.changeskin(Manager.themeSetting)
            SkinManager.changeskin(themeBackIndex)
        }
    }

    //全局变量用于 在进行主题动画时发生主题切换时不打断当前动画
    property bool themeAnimationRunning: false
    //全局变量用于 在进行主题动画时发生主题切换时 记忆当前要切换的主题坐标
    property int themeBackIndex: ManagerEnums.NONE

    property int initThemeSetting: Manager.themeSetting
    onInitThemeSettingChanged:{
        if(initThemeSetting > ManagerEnums.NONE &&
                initThemeSetting < ManagerEnums.MAXTHEM) {
            themeAnimationRunning = true;
            SkinManager.changeskin(initThemeSetting);
        }
    }

    Loader{
        id: loader
        //source: SkinManager.currentSkin
        onLoaded: {
            console.log("point load rcc sucess.")
            if(initThemeSetting === -99) {


            } else {
                initThemeSetting = -99;
                Manager.notify_cluster_manager("start"); // init
            }
        }
    }

}
