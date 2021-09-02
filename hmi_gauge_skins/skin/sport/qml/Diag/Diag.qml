import QtQuick 2.8
import "../Common/"

Item {
    id: diagDisplay
    width:   1920
    height:  720

    property int currentChild1Page : DiagScreen.currentChild1Page //[1:DiagMenu][3:Monitor检查][9:恢复出厂设置中]
    property int currentParentPageSelectedItem : DiagScreen.selectedItem //[1:Monitor检查][2:里程清零][3:恢复出厂设置]
    property int popTypeID         : DiagScreen.popType
    property int monitorCheckDisplay : DiagScreen.monitorCheckDisplay //Monitor Check Image Index
    property int mileageClearDisble  : DiagScreen.itemMileageClearDisble //里程清零剩余次数
    property bool popBottonOKSlecte: DiagScreen.popBottonOKSlecte
    property var monitorChkImage: [
        "../Diag/black.png",
        "../Diag/white.png",
        "../Diag/jianbian.png",
        "../Diag/colour.png",
        "../Diag/red.png",
        "../Diag/green.png",
        "../Diag/blue.png"
    ]


    visible: (0 != currentChild1Page)? true : false

    function isDiagDisplayVisible(){
        return diagDisplay.visible
    }

    Loader{
        id: loaderDIAG
        active: currentChild1Page != 0
        sourceComponent: diagCom
        onLoaded: {
            active = true
        }
    }

    Component{
        id: diagCom

        Item {
            id: diagShow
            width:   1920
            height:  720

            Rectangle{
                id: diagMenuBG
                width:   parent.width
                height:  parent.height
                color:   "#313235"
            }

            // [1:DiagMenu]
            Item{
                id: diagMenu
                visible: (1 == currentChild1Page) ? true : false

                CustomText{
                    id: diagTitle
                    anchors.left : parent.left
                    anchors.leftMargin: 919
                    anchors.top : parent.top
                    anchors.topMargin: 22
                    width:   84
                    height:  48
                    text: qsTr("Diag")
                    font.pixelSize: 40
                }

                Item {
                    id: menu_Item
                    ListView {
                        id: diagMainMenuItemList
                        width: 794
                        height: 455
                        x: 563
                        y: 137
                        model: diagMainMenuItemListModel
                        delegate: diagMainMenuItemDelegate
                    }
                    ListModel {
                        id: diagMainMenuItemListModel
                        property int mileageClearDisble: DiagScreen.itemMileageClearDisble
                        property bool completed: false
                        Component.onCompleted: {
                            append({name: "Monitor检查", myEnable: true, type: 0});
                            append({name: "里程清零(剩余"+diagMainMenuItemListModel.mileageClearDisble +"次)", myEnable: diagMainMenuItemListModel.mileageClearDisble === 0 ? false : true, type: 0});
                            append({name: "恢复出厂设置", myEnable: true, type: 0});
                            append({name: "退出", myEnable: true, type: 0});
                            completed = true;
                        }

                        // 2. Update the list model:
                        onMileageClearDisbleChanged: {
                            if(completed)
                            {
                                setProperty(1, "name", "里程清零(剩余"+diagMainMenuItemListModel.mileageClearDisble+"次)");
                                if(diagMainMenuItemListModel.mileageClearDisble === 0){
                                    setProperty(1, "myEnable", false);
                                }else{
                                    setProperty(1, "myEnable", true);
                                }
                            }
                            else{

                            }
                        }
                    }
                    Component {
                        id: diagMainMenuItemDelegate
                        Item{
                            width:   794
                            height:  65
                            CustomText{
                                id: name_Item
                                anchors.left : parent.left
                                anchors.leftMargin: 120
                                anchors.top : parent.top
                                anchors.topMargin: 6
                                width:   554
                                height:  43
                                horizontalAlignment: Text.AlignLeft
                                color: "white"
                                smooth: true
                                lineHeight: 43
                                lineHeightMode: Text.FixedHeight
                                text: name
                                font.pixelSize: 36
                                font.letterSpacing : 0
                                opacity: myEnable ? 1.0 : 0.3
                                Image{
                                    id: line_Item
                                    anchors.left : parent.left
                                    anchors.leftMargin: 0
                                    anchors.top : parent.top
                                    anchors.topMargin: 63
                                    width:   794
                                    height:  2
                                    source: "../Diag/list_line.png"
                                }
                                Image{
                                    id: arrow_Item
                                    anchors.left : parent.left
                                    anchors.leftMargin: 656
                                    anchors.top : parent.top
                                    anchors.topMargin: 21
                                    width:   18
                                    height:  21
                                    source: {
                                        if(type === 0){
                                            myEnable ? "arrow.png" : "list_arrow_disble.png"
                                        }
                                        else {
                                            ""
                                        }
                                    }
                                }
                                Image{
                                    id: selectImg_Item
                                    visible: (index === (currentParentPageSelectedItem))? true : false
                                    anchors.left : parent.left
                                    anchors.leftMargin: 19
                                    anchors.top : parent.top
                                    anchors.topMargin: 0
                                    width:   794
                                    height:  63
                                    source: "../Diag/list_select.png"
                                }
                            }
                        }
                    }


                   }
            }
        }
    }

    //POP
    Loader{
        id: popLoader
        sourceComponent: popCom
        active: popTypeID !== 0
        onLoaded: active = true
    }

    Component{
        id: popCom
        Item {
            id: popZone
            width: 1920
            height: 720
            visible: popTypeID !== 0
            Image {
                id: popBgBig
                width: 775
                height: 350
                x: 582
                y: 200
                source:"../Diag/pop_button_bg.png"
            }
            CustomText{
                id: popMessage3
                width:   324
                height:  43
                x: 808
                y: 295
                color: "white"
                smooth: true
                lineHeight: 43
                lineHeightMode: Text.FixedHeight
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 36
                font.letterSpacing : 0
                text: {
                    if(popTypeID === 1){
                        qsTr("确定清除总计里程？")
                    }else if(popTypeID === 2){
                        qsTr("确定恢复出厂设置？")
                    }else{
                        ""
                    }
                }
            }

            Item {
                id: popButton
                CustomButton{
                    x: 743
                    y: 417
                    isPressed: popBottonOKSlecte
                    txtStr: trLanguge("确定")
                }

                CustomButton{
                    x: 1018
                    y: 417
                    isPressed: !popBottonOKSlecte
                    txtStr: trLanguge("取消")
                }
            }
        }
    }

    // [3:Monitor检查]
    Loader{
        id: monitorChkLoader
        sourceComponent: monitorChkCom
        active: 2 === currentChild1Page
        onLoaded: {
            active = true
        }
    }
    Component{
        id: monitorChkCom
        Item{
            id: monitorChkClearedPage
            width: 1920
            height:  720
            visible: (2 === currentChild1Page) ? true : false
            Image{
                id: monitorChkImg
                anchors.fill: parent
                anchors.left : parent.left
                anchors.top : parent.top
                source: {
                    if(monitorCheckDisplay <= monitorChkImage.length - 1){
                        monitorChkImage[monitorCheckDisplay]
                    }else{
                        ""
                    }
                }
            }
        }

    }


    // [9:出厂设置恢复中...]
    Loader{
        id: resumingLoader
        sourceComponent: resumingCom
        active: 3 === currentChild1Page
        onLoaded: {
            active = true
        }
    }
    Component{
        id: resumingCom
        Rectangle{
            id: resumingPage
            visible: (3 === currentChild1Page)? true : false
            width:   1920
            height:  720
            color: "#313235"
            CustomText{
                anchors.left : parent.left
                anchors.leftMargin: 816
                anchors.top : parent.top
                anchors.topMargin: 331
                width:   288
                height:  43
                color: "white"
                smooth: true
                lineHeight: 43
                lineHeightMode: Text.FixedHeight
                text: qsTr("出厂设置恢复中…")
                font.pixelSize: 36
                font.letterSpacing : 0
            }
        }
    }

}
