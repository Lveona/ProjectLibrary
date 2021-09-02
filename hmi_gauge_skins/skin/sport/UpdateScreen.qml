import QtQuick 2.8
import "./qml/Common"

Item {
    width: 1920
    height: 720
    x: 0
    y: 0

    property int updateTitleType:     Update_Thread.messageType
    property int updateProcess:       Update_Thread.processStep * 900 /100

    visible: (4 != updateTitleType)? true : false

    onVisibleChanged: {
        //update显示point不显示
        Manager.updateScreenVisible = visible
    }
    Component.onCompleted: {
        Manager.updateScreenVisible = visible
    }

    Rectangle{
        id: updateMianBg
        anchors.fill: parent
        color: "#313235"
    }

    Item{
        width: 1920
        height: 720
        x: 0
        y: 200

        Item {
            id: updateBarCell
            visible: (2 === updateTitleType || 3 === updateTitleType || 7 === updateTitleType) ? false : true
            Rectangle{
                id: updateBarBg
                width: 900
                height: 30
                x: 510
                y: 398
                color: "#505050"
            }

            Image {
                id: updateBar
                width: updateProcess
                height: 30
                x: 510
                y: 398
                source: "rectangle.png"
            }
        }

        CustomText{
            id: updateTitle
            width: 440
            height: 96
            anchors.horizontalCenter: parent.horizontalCenter
            y: 205
//            font.family: "Source Han Sans CN Regular"
            renderType: Text.NativeRendering
            font.pixelSize: 40
            color: "white"
            smooth: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: {
                if ( 0 === updateTitleType ) {
                    "Upgrade reading…" /*qsTr("升级读取中…")*/
                } else if ( 1 === updateTitleType ) {
                    "during upgrade…\n" + "please wait patiently，Do not power off! \n"+Update_Thread.fileNum /*qsTr("升级中…\n" + "请耐心等待，请勿断电! ")*/
                }
                else if (2 === updateTitleType ){
                    "update successed！"+ "\n" + "The system will restart automatically after 2 seconds！" /*qsTr("升级成功！"+ "\n" + "系统2秒后将自动重启！")*/
                }
                else if(5 === updateTitleType){
                    "Upgrade check…"  /*qsTr("升级校验中…")*/
                }
                else if(6 === updateTitleType){
                    "Upgrade check successed!"  /*qsTr("升级校验中…")*/
                }
                else if(3 === updateTitleType){
                    "No upgrade file available"  /*没有可用的升级文件*/
                }
                else if(7 === updateTitleType){
                    "Upgrade failed"  /*升级失败*/
                }
                else { // Nothing
                    qsTr("")
                }
            }
        }

    }


}
