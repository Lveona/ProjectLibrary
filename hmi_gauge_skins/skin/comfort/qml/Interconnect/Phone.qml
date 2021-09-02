import QtQuick 2.8
import "../Common/"

Item {
    id: allZone
    width: 1920
    height: 720

    property bool btConnectStatus: InterconnectScreen.phoneDataObject.btConnectStatus
    property string call_title: InterconnectScreen.phoneDataObject.currentPage===0?InterconnectScreen.phoneDataObject.callOneName:InterconnectScreen.phoneDataObject.callTwoName
    property string call_new_title: InterconnectScreen.phoneDataObject.currentPage===0?InterconnectScreen.phoneDataObject.callTwoName:InterconnectScreen.phoneDataObject.callOneName
    property string call_state: InterconnectScreen.phoneDataObject.currentPage===0?InterconnectScreen.phoneDataObject.callOneState:InterconnectScreen.phoneDataObject.callTwoState
    property string call_new_state:InterconnectScreen.phoneDataObject.currentPage===0?InterconnectScreen.phoneDataObject.callTwoState:InterconnectScreen.phoneDataObject.callOneState
    property bool activeOnly: InterconnectScreen.phoneDataObject.activeOnly
    property bool hungAndActive: InterconnectScreen.phoneDataObject.hungAndActive
    property int call_Mode: InterconnectScreen.phoneDataObject.callMode
    property bool call_hold: InterconnectScreen.phoneDataObject.hold
    property int call_status: InterconnectScreen.phoneDataObject.callOneStatus
    property int call_new_status:InterconnectScreen.phoneDataObject.callTwoStatus

    property string oneHeadIcon: InterconnectScreen.phoneDataObject.currentPage===0?InterconnectScreen.phoneDataObject.oneHeadIcon:InterconnectScreen.phoneDataObject.twoHeadIcon
    property string twoHeadIcon: InterconnectScreen.phoneDataObject.currentPage===0?InterconnectScreen.phoneDataObject.twoHeadIcon:InterconnectScreen.phoneDataObject.oneHeadIcon
    onBtConnectStatusChanged: {
//        printwarn(btConnectStatus);
    }


    //呼叫界面
    Image {
        id: imgBG
        x:1558
        y:321
        source: "phone/Phone_BG_OnCall_1Line.png"
        visible: call_Mode == 1 && call_status != 5
    }

    Image {
        id: img_hung_up_BG
        x:1558
        y:321
        source: "phone/Phone_BG_EndCall_1Line.png"
        visible: call_Mode == 1 && call_status == 5
        opacity: 0.5
    }

    //头像icon
    RoundIcon{
        id: img_head
        x:1613
        y:376
        width: 125
        height: 125
        radius: 62.5
        source: oneHeadIcon
        visible: call_Mode == 1
    }


    //联系人or电话号码
    CustomText{
        id: txtTitle
        x: 1619
        y: 231
        width: 114
        height: 38
        text: call_title
        font.pixelSize: 38
        font.bold: true
        elide: Text.ElideRight
        visible: call_Mode == 1 && call_status != 5
    }

    CustomText{
        id: hungUpTxtTitle
        x: 1619
        y: 231
        width: 114
        height: 38
        text: call_title
        font.pixelSize: 38
        font.bold: true
        elide: Text.ElideRight
        visible: call_Mode == 1 && call_status == 5
        opacity: 0.5
    }

    //状态
    CustomText{
        anchors.horizontalCenter: txtTitle.horizontalCenter
        y:279
        text: trLanguge(call_state)
        font.pixelSize: 24
        opacity: 0.5
        font.bold: true
        visible: call_Mode == 1
    }

    //短按挂断
    CustomText{
        id: txt_bottom
        x:1620
        y:586
        visible: activeOnly
        font.pixelSize: 20
        opacity: 0.7
        text: "短按       挂断"
        width: 112
        height: 20
    }
    Image {
        id: icon_phone
        anchors.centerIn: txt_bottom
        visible: activeOnly
        source: "phone/Phone_Tips_Icon.png"
    }

    CustomText{
        id: txt_hung
        x:1556
        y:586
        font.pixelSize: 20
        opacity: 0.7
        visible: hungAndActive
        text: "短按       接听   ,  长按       挂断"

    }
    Image {
        id: icon_hungPhone
        x:1601
        y:586
        visible: hungAndActive
        source: "phone/Phone_Tips_Icon.png"
    }
    Image {
        id: icon_activePhone
        x:1735
        y:586
        visible: hungAndActive
        source: "phone/Phone_Tips_Icon.png"
    }




    //新通话界面
        Image {
            id:new_call_BG
            x:1639
            y:353
            width: 195
            height: 220
            visible: call_Mode == 2 && call_new_status != 5
            source: "phone/Phone_BG_OnCall_2Line_Front.png"
        }

        Image {
            id:new_hung_up_call_BG
            x:1639
            y:353
            width: 195
            height: 220
            visible: call_Mode == 2 && call_new_status == 5
            source: "phone/Phone_BG_EndCall_2Line_Front.png"
            opacity: 0.5
        }
      //新联系人
        CustomText{
            id:new_call_title
            x:1641
            y:250
            width:190
            height: 38
            text:call_new_title
            font.pixelSize: 30
            font.bold: true
            elide: Text.ElideRight
            visible: call_Mode == 2 && call_new_status != 5

        }

        CustomText{
            id:new_hung_up_call_title
            x:1641
            y:250
            width:190
            height: 38
            text:call_new_title
            font.pixelSize: 30
            font.bold: true
            elide: Text.ElideRight
            visible: call_Mode == 2 && call_new_status == 5
            opacity: 0.5
        }
        //新状态
        CustomText{
            id:new_call_state
            anchors.horizontalCenter: new_call_title.horizontalCenter
            y:291
            text: trLanguge(call_new_state)
            font.pixelSize: 24
            opacity: 0.5
            font.bold: true
            visible: call_Mode == 2

        }
        //新头像
        RoundIcon {
            id: new_image_icon
            x:1685
            y:398
            width: 104
            height: 105
            radius: 52
            source: twoHeadIcon
            visible: call_Mode == 2
        }
        //原通话界面
        Image {
            id:back_call_BG
            x:1524
            y:395
            width: 127
            height: 155
            source: "phone/Phone_BG_OnCall_2Line_Back.png"
            visible: call_Mode == 2
        }
        //原联系人
        CustomText {
            id:back_call_title
            x:1499
            y:326
            width: 180
            height: 20
            text:call_title
            font.pixelSize: 20
            font.bold: true
            opacity: 0.2
            visible: call_Mode == 2
        }
        //原通话状态
        CustomText{
            id:back_call_state
            anchors.horizontalCenter: back_call_title.horizontalCenter
            y:355
            text: trLanguge(call_state)
            font.pixelSize: 20
            opacity: 0.2
            font.bold: true
            visible: call_Mode == 2

        }
        //原头像
        RoundIcon {
            id: back_image_icon
            x:1556
            y:427
            width: 73
            height: 74
            opacity: 0.2
            radius: 37
            source: oneHeadIcon
            visible: call_Mode == 2
        }

        CustomText{
            id: two_txt_hung
            x:1500
            y:586
            font.pixelSize: 20
            opacity: 0.7
            visible: call_hold
            text: "短按       接听并保留  , 长按       挂断新来电"

        }
        Image {
            id: two_icon_hungPhone
            x:1577
            y:586
            visible: call_hold
            source: "phone/Phone_Tips_Icon.png"
        }
        Image {
            id: two_nactivePhone
            x:1761
            y:586
            visible: call_hold
            source: "phone/Phone_Tips_Icon.png"
        }


}
