import QtQuick 2.8
import "./qml/Common"

Item {
    width: 1920
    height: 720
    visible: (0 != isLcdUpdate)? true : false

    property int isLcdUpdate: Manager.lcdUpdateScreenIndex  //【0：无升级】【1：pop提示是否确认升级LCD】【2：升级成功/失败】【3：升级进度】
    property int popID: Manager.lcdUpdatePopID  //【0：升级成功】【1：升级失败】
    property bool popBottonOKSlecte: Manager.lcdUpdateButtonOKSlecte
    property int lcdUpdateProcess:Manager.lcdUpdateProcess*451/100

    // Pop弹出时的遮罩区
    Rectangle{
        id: maskBG
        width:   parent.width
        height:  parent.height
        color:   "#000000"
    }


    // POP
    Item {
        id: popZone

        //确认升级pop背景
        Image {
            id: popBgBig
            width: 775
            height: 350
            x: 582
            y: 200
            visible: ( 1 === isLcdUpdate || 3 === isLcdUpdate) ? true : false
            source: "./qml/Diag/pop_bg.png"
        }

        //升级成功/失败pop背景
        Image {
            id: popBgSmall
            width: 775
            height: 150
            x: 582
            y: 200
            visible: ( 2 === isLcdUpdate ) ? true : false
            source: "./qml/Diag/pop_bg.png"
        }

        //确认升级pop文言
        CustomText{
            id: popMessage1
            width:   324
            height:  43
            x: 808
            y: 295
            visible: ( 1 === isLcdUpdate ) ? true : false
            color: "white"
            smooth: true
            lineHeight: 43
            lineHeightMode: Text.FixedHeight
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 36
            font.letterSpacing : 0
            text: qsTr("确定进行LCD屏幕升级？")
        }

        //升级中pop文言
        CustomText{
            id: popMessage2
            width:   324
            height:  43
            x: 808
            y: 295
            visible: ( 3 === isLcdUpdate ) ? true : false
            color: "white"
            smooth: true
            lineHeight: 43
            lineHeightMode: Text.FixedHeight
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 36
            font.letterSpacing : 0
            text: qsTr("LCD屏幕升级中...")
        }

        //升级进度
        Item {
            id: lcdUpdating
            visible: ( 3 === isLcdUpdate ) ? true : false

            Rectangle{
                id: lcdUpdate_bg
                x: 743
                y: 417
                width: 451
                height: 30
                color: "#313235"
            }

            Image {
                id: lcdUpdate_Process
                width: lcdUpdateProcess
                height: 30
                x: 743
                y: 417
                source: "./qml/updateIcon/rectangle.png"
            }

        }

        //升级成功/失败pop文言
        CustomText{
            id: popMessage3
            width:   278
            height:  43
            x: 831
            y: 247
            visible: ( 2 === isLcdUpdate ) ? true : false
            color: "white"
            smooth: true
            lineHeight: 43
            lineHeightMode: Text.FixedHeight
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 36
            font.letterSpacing : 0
            text: {
                    switch(popID){
                    case 0:
                        qsTr("LCD屏幕升级成功")
                        break;
                    case 1:
                        qsTr("LCD屏幕升级失败")
                        break;
                    }
            }
        }

        Item {
            id: popButton
            visible: ( 1 === isLcdUpdate ) ? true : false
            Image {
                id: popButtonOK
                width: 176
                height: 68
                x: 743
                y: 417
                source: {
                    if(popBottonOKSlecte == true)
                    {
                        "./qml/Diag/pop_button_selected.png"
                    }
                    else
                    {
                        "./qml/Diag/pop_button_normal.png"
                    }
                }
                CustomText{
                    id: popButtonOKText
                    width:   72
                    height:  43
                    anchors.top: parent.top
                    anchors.topMargin: 9
                    anchors.left: parent.left
                    anchors.leftMargin: 52
                    color: "white"
                    smooth: true
                    lineHeight: 43
                    lineHeightMode: Text.FixedHeight
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 36
                    font.letterSpacing : 0
                    text: qsTr("确定")
                }
            }
            Image {
                id: popButtonCancel
                width: 176
                height: 68
                x: 1018
                y: 417
                source: {
                    if(popBottonOKSlecte == false)
                    {
                        "./qml/Diag/pop_button_selected.png"
                    }
                    else
                    {
                        "./qml/Diag/pop_button_normal.png"
                    }
                }
                CustomText{
                    id: popButtonCanelText
                    width:   72
                    height:  43
                    anchors.top: parent.top
                    anchors.topMargin: 8
                    anchors.left: parent.left
                    anchors.leftMargin: 52
                    color: "white"
                    smooth: true
                    lineHeight: 43
                    lineHeightMode: Text.FixedHeight
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 36
                    font.letterSpacing : 0
                    text: qsTr("取消")
                }
            }
        }
    }

}
