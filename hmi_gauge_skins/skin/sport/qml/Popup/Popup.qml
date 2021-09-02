import QtQuick 2.8
import "./../Common/"
//import PopupDataObject 1.0

Item{
    id: item_pop_root

    property string pop_name: PopupScreen.popupDataObject.name//pop文言
    property string pop_name_last_tyre:""
    property string pop_iconname: PopupScreen.popupDataObject.iconname//pop图片名
    property int pop_priorityvalue: PopupScreen.popupDataObject.priorityvalue//pop类型

    property string toast1_name_last: ""
    property string toast2_name_last: ""

    property string toast1_name_display: ""//先来的数据
    property string toast1_iconname_display: ""

    property string toast2_name_display: ""
    property string toast2_iconname_display: ""

    property int toastYPosition_1: 604 //上方toast
    property int toastYPosition_2: 650 //下方toast
    property int toastYPosition_3: 720 //未弹出/取消toast

    property int durationTime : 100

    property int toast1_category_display: 0 //1 red 2 yellow 3 white 4 toast red 5 toast yellow 6 toast white
    property int toast2_category_display: 0

    property string adasToastName: ""
    property string adasToastImage: ""
    property int adasToastCategoty: 0

    property int redCardNumber: PopupScreen.redCardNumber//红色报警数量
    property int yellowCardNumber: PopupScreen.yellowCardNumber//黄色报警数量

    property int redCardCurrentIndex: PopupScreen.redCardCurrentIndex//红色报警当前下标
    property int yellowCardCurrentIndex: PopupScreen.yellowCardCurrentIndex//黄色报警当前下标

    property bool yellowCardListHide: PopupScreen.yellowCardListHide//黄色卡片列表隐藏 true：隐藏

    property int tyreYPosition_1: 30
    property int tyreYPosition_2: 0
    property int tyreYPosition_3: -30

    property var volumePercent   : InterconnectScreen.volumePercent   //当前音量百分比
    property bool gapVisible: ADASScreen.accTimeGapVisible

    onPop_nameChanged: {
        if(pop_iconname === "tire_car.png")
        {
            addNewTyre.restart()
        }

        if(pop_name === "")
        {
            pop_name_last_tyre = pop_name
        }
    }

    Connections{
        target: PopupScreen
        onAddToast: {
            if(toast1_name_display === name)
            {}
            else{
                toast1_name_display = name
                toast1_category_display = category
            }
        }

        onDelToast: {
            if(toast1_name_display === name)
            {
                toast1_name_display = ""
                toast1_category_display = ""
            }
            else{}
        }
//        onAddToast: {
//            // name iconname

//            if(toast1_name_display === name || toast2_name_display === name)
//            {}
//            else{
//                if(toast1_name_display === ""){
//                    // add 1
//                    if(toast2_name_display !== ""){
//                        // 2->1 3->2
//                        // 狸猫换太子
//                        toast1_name_last = toast1_name_display = toast2_name_display
//                        toast1_iconname_display = toast2_iconname_display
//                        toast1_category_display = toast2_category_display
//                        item_toast1.y = item_toast2.y
//                        item_toast1.opacity = item_toast2.opacity
//                        item_toast2.opacity = 0

//                        toast2_name_display = name
//                        toast2_iconname_display = iconname
//                        toast2_category_display = category
//                        item_pop_root.state = "show_toast1and2"
//                    }
//                    else{//2从3上升显示
//                        toast2_name_last = toast2_name_display = name
//                        toast2_iconname_display = iconname
//                        toast2_category_display = category
//                        item_pop_root.state = "show_toas2"
//                    }
//                }
//            }
//        }
//        onDelToast: { // 超时 or 解除
//            if(toast1_name_display === name || toast2_name_display === name)
//            {
//                if(toast1_name_display === name){
//                    // del 1
//                    item_pop_root.state = "hide_toas1"
//                    toast1_name_display = ""
//                }
//                else if(toast2_name_display === name){
//                    // del 2
//                    if(toast1_name_display === "")
//                    {
//                        item_pop_root.state = "hide_toas2"
//                    }
//                    else{
//                        item_pop_root.state = "hide_toas1and2"
//                    }
//                    toast2_name_display = ""
//                }
//            }
//            else{
//            }
//        }

        onAddAdasToast:{
            if(adasToastName != name)
            {
                adasToastName = name;
                adasToastCategoty = category;
            }
            else{}
        }

        onDelAdasToast:{
            if(adasToastName === name)
            {
                adasToastName = ""
            }
        }
    }


    ParallelAnimation{
        id: addNewTyre
        PropertyAnimation{target: newTyreText; properties: "y"; from: tyreYPosition_3; to: tyreYPosition_2; duration: 500; }
        PropertyAnimation{target: oldTyreText; properties: "y"; from: tyreYPosition_2; to: tyreYPosition_1; duration: 500; }
        onStopped: {
            pop_name_last_tyre = pop_name
        }
    }

//    state: "normal"

//    states: [
//        State {
//            name: "normal"
//            PropertyChanges {
//                target: item_toast1
//                y: toastYPosition_3    // pos
//                opacity: 0
//            }
//            PropertyChanges {
//                target: item_toast2
//                y: toastYPosition_3    // pos
//                opacity: 0
//            }
//        },
//        State {
//            name: "show_toas1"
//            PropertyChanges {
//                target: item_toast1
//                y:  toastYPosition_1   // pos
//                opacity: 1
//            }
//        },
//        State {
//            name: "hide_toas1"
//            PropertyChanges {
//                target: item_toast1
//                y: toastYPosition_3
//                opacity: 0
//            }
//        },
//        State {
//            name: "show_toas2"//3->2
//            PropertyChanges {
//                target: item_toast2
//                y: toastYPosition_2    // pos
//                opacity: 1
//            }
//        },
//        State {
//            name: "hide_toas2"
//            PropertyChanges {
//                target: item_toast2
//                y:toastYPosition_3
//                opacity: 0
//            }
//            PropertyChanges {
//                target: item_toast1
//                y:toastYPosition_3
//                opacity: 0
//            }
//        },
//        State {
//            name: "show_toast1and2"
//            PropertyChanges {
//                target: item_toast1
//                y: toastYPosition_1 // pos
//                opacity: 1
//            }
//            PropertyChanges {
//                target: item_toast2
//                y:toastYPosition_2
//                opacity: 1
//            }
//        },
//        State {
//            name: "hide_toas1and2" //1->2 2->3隐藏
//            PropertyChanges {
//                target: item_toast1
//                y: toastYPosition_2
//                opacity: 1
//            }
//            PropertyChanges {
//                target: item_toast2
//                y:toastYPosition_3
//                opacity: 0
//            }
//        }
//    ]

//    transitions: [
//        Transition {
//            to: "normal"
//            NumberAnimation{ properties: "y,opacity"; duration: durationTime; }
//        },
//        Transition {
//            to: "show_toas1"
//            NumberAnimation{ properties: "y,opacity"; duration: durationTime; }
//        },
//        Transition {
//            to: "show_toas2"
//            NumberAnimation{ properties: "y,opacity"; duration: durationTime; }
//        },
//        Transition {
//            to: "hide_toas1"
//            NumberAnimation{ properties: "y,opacity"; duration: durationTime; }
//        },
//        Transition {
//            to: "hide_toas2"
//            NumberAnimation{ properties: "y,opacity"; duration: durationTime; }
//        },
//        Transition {
//            to: "show_toast1and2"
//            NumberAnimation{ properties: "y,opacity"; duration: durationTime; }
//        },
//        Transition {
//            to: "hide_toas1and2"
//            NumberAnimation{ properties: "y,opacity"; duration: durationTime; }
//        }
//    ]


    Item{
        anchors.fill: parent
        visible: !gapVisible
        //左侧C区pop tyre
        Item{
            visible: (pop_iconname === "tire_car.png") && (!yellowCardListHide)
            CustomTyre{
                id:tyreItem
            }
            Item{
                x: 146
                y: 448
                clip: true
                width: 385
                height: 30
                CustomText{
                    id: newTyreText
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 28
                    font.family:trLanguge("font")
                    text:trLanguge(pop_name)
                    color: "#cf7515"
                }
                CustomText{
                    id: oldTyreText
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 28
                    text: trLanguge(pop_name_last_tyre)
                    color: "#cf7515"
                }
            }
        }



        //左侧C区pop 非tyre
        Item{
            id:cardCMsgItem_red
            opacity: pop_name === "" ? 0 : 1
            visible: pop_iconname !== "tire_car.png" && pop_priorityvalue === 0
            x: 176
            y: 191
            width: 355
            height: 259
            CustomImage {
                id: pop_image_red
                anchors.horizontalCenter: parent.horizontalCenter
                width: 190
                height: 153
                source: "pic_areaC_warning_red.png"
            }
            CustomText {
                anchors.horizontalCenter: pop_image_red.horizontalCenter
                y: 194
                width: 365
                font.pixelSize: 28
                lineHeight: 32
                lineHeightMode: Text.FixedHeight
                wrapMode: Text.WordWrap
                font.family:trLanguge("font")
                text:trLanguge(pop_name)
            }
        }

        Item{
            id:cardCMsgItem_yellow
            opacity: pop_name === "" ? 0 : 1
            visible:( pop_iconname !== "tire_car.png") && (pop_priorityvalue === 1) && (!yellowCardListHide)
            x: 176
            y: 191
            width: 355
            height: 259
            CustomImage {
                id: pop_image_yellow
                anchors.horizontalCenter: parent.horizontalCenter
                width: 190
                height: 153
                source: "pic_areaC_warning_yellow.png"
            }
            CustomText {
                anchors.horizontalCenter: pop_image_yellow.horizontalCenter
                y: 194
                width: 365
                font.pixelSize: 28
                lineHeight: 32
                lineHeightMode: Text.FixedHeight
                wrapMode: Text.WordWrap
                text:trLanguge(pop_name)
                font.family:trLanguge("font")
            }
        }

        //    //toast信息 1
        Item {
            x:646
            y:toastYPosition_2
            width: 628
            height: 97
            id: item_toast1
            opacity: toast1_name_display === "" ? 0 : 1
            CustomImage {
                id: toastBackImg_red
                source: "pic_toast_normal_red.png"
                visible: toast1_category_display === 0
            }
            CustomImage {
                id: toastBackImg_yellow
                source: "pic_toast_normal_yellow.png"
                visible: toast1_category_display === 1 || toast1_category_display === 3
            }
            CustomImage {
                id: toastBackImg_white
                source: "pic_toast_normal_white.png"
                visible: toast1_category_display === 2
            }
            CustomImage {//音量条
                id: volume_Img_bg_white
                source: "pic_toast_normal_white.png"
                visible: toast1_category_display === 7
                CustomImage{
                    id: volumeImg
                    x: 192
                    y: 20
                    source: "../Home/icon_toast_volume.png"
                }
                Row {
                    id: volumeBarBg
                    anchors.left: volumeImg.right
                    anchors.leftMargin: 12
                    anchors.verticalCenter: volumeImg.verticalCenter
                    spacing: -13
                    Repeater {
                        id: s1
                        model: 22
                        CustomImage {
                            width: sourceSize.width
                            height: sourceSize.height
                            source: "../Home/sound_bg.png"
                        }
                    }
                }
                Row {
                    id: curVolume
                    anchors.left: volumeImg.right
                    anchors.leftMargin: 12
                    anchors.verticalCenter: volumeImg.verticalCenter
                    spacing: -13
                    Repeater {
                        model: s1.model * volumePercent / 100
                        CustomImage {
                            width: sourceSize.width
                            height: sourceSize.height
                            source: "../Home/sound_hl.png"
                        }
                    }
                }
            }
            CustomText {
                id: item_toast1_text
                anchors.top: parent.top
                anchors.topMargin: 22
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 24
                text: trLanguge(toast1_name_display)
                font.family:trLanguge("font")
                visible: toast1_name_display !== "音量"
            }
        }
    }

    //    //toast信息_2
//    Item {
//        x:646
//        y:toastYPosition_2
//        width: 628
//        height: 97
//        id: item_toast2
//        opacity: toast2_name_display === "" ? 0 : 1
//        CustomImage {
//            id: toastBackImg_red_2
//            source:"pic_toast_normal_red.png"
//            visible: toast2_category_display === 0
//        }
//        CustomImage {
//            id: toastBackImg_yellow_2
//            source: "pic_toast_normal_yellow.png"
//            visible: toast2_category_display === 1 || toast2_category_display === 3
//        }
//        CustomImage {
//            id: toastBackImg_white_2
//            source: "pic_toast_normal_white.png"
//            visible: toast2_category_display === 2
//        }
//        CustomText {
//            id: item_toast2_text
//            width: 479
//            height: 23
//            anchors.top: parent.top
//            anchors.topMargin: 22
//            anchors.horizontalCenter: parent.horizontalCenter
//            font.pixelSize: 24
//            text: toast2_name_display
//            wrapMode: Text.WordWrap
//        }
//    }

    //adas信息
    Item{
        x: 840
        y: 527
        width: 240
        height: 50
        visible: adasToastName === "" ? 0 : 1
        CustomImage {
            id: adastoastBackImg_red
            anchors.horizontalCenter: parent.horizontalCenter
            width: adas_text.implicitWidth > 262 ? adas_text.implicitWidth +20 : 262
            source:"pic_ADASTOAST_red.png"
            visible: adasToastCategoty === 4
        }
        CustomImage {
            id: adastoastBackImg_yellow
            anchors.horizontalCenter: parent.horizontalCenter
            width: adas_text.implicitWidth > 262 ? adas_text.implicitWidth +20 : 262
            source: "pic_ADASTOAST_yellow.png"
            visible: adasToastCategoty === 5
        }
        CustomImage {
            id: adastoastBackImg_white
            anchors.horizontalCenter: parent.horizontalCenter
            width: adas_text.implicitWidth > 262 ? adas_text.implicitWidth +20 : 262
            source: "pic_ADASTOAST_white.png"
            visible: adasToastCategoty === 6
        }
        CustomText {
            id:adas_text
            height: 23
            anchors.verticalCenter: adastoastBackImg_red.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 24
            font.family:trLanguge("font")
            text: trLanguge(adasToastName)
        }
    }

    CustomPageIndicator{
        id: redcard_page_point
        indicatorCount: redCardNumber//报警数量
        curIndicatorIndex: redCardCurrentIndex//当前下标
        visible: redCardNumber > 1 && pop_priorityvalue === 0
    }

    CustomPageIndicator{
        id: yellowcard_page_point
        indicatorCount: yellowCardNumber//报警数量
        curIndicatorIndex: yellowCardCurrentIndex//当前下标
        visible: (yellowCardNumber>1) && (pop_priorityvalue === 1) && (!yellowCardListHide)
    }

    property bool hardkey_down_visible: (pop_priorityvalue === 1) && (!yellowCardListHide)//长按下查看 true:显示
    property bool hardkey_up_visible: yellowCardListHide && (pop_priorityvalue === 1) //长按上查看 true:显示

    CustomText {
        x: 190
        y: 480
        height: 20
        width: 123
        font.pixelSize: 20
        text: "("+yellowCardNumber +")"+trLanguge("长按X查看")
        visible: hardkey_up_visible
        font.family:trLanguge("font")
        color: "#cf7515"
    }

    CustomText {
        x: 190
        y: 480
        height: 20
        width: 123
        font.pixelSize: 20
        text: trLanguge("长按X隐藏")
        font.family:trLanguge("font")
        visible: hardkey_down_visible
        color: "#cf7515"
    }
	Loader{
        active: gapVisible
        visible: gapVisible
        source: "../ADAS/ADASCard.qml"
        onLoaded: {
            active = true
        }
    }
}
