import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.1

Item {
    id: root
    width: 800
    height: 600

    Component.onCompleted: {
        HMIBox.init()
    }

    Connections{
        target: HMIBox
        onUpdateData: {
//            var ids = HMIBox.getIdList()
            updateData("")
        }
        onNewFileFinished: {
            dialog.visible = true
        }
    }

    function updateData(filter)
    {
        var msgs = HMIBox.getHeadMsgList()

        listModel.clear()

        for ( var m in msgs )
        {
//                console.log(msgs[m], msgs[m].idName)
            if (msgs[m].idName == "-1" ) continue

            var map = {}
            map["idName"] = msgs[m].idName
            map["idValue"] = msgs[m].idValue
            map["name"] = msgs[m].name
            map["repeat_id"] = 0
            listModel.append(map)
        }
    }

    function checkIdRepeat()
    {
        var flag = false
        var start = 0

        // merge
        for ( var i = 0; i < listModel.count; i++)
        {
            listModel.setProperty(i, "repeat_id", 0)

            for ( var m = i+1; m < listModel.count; m++)
            {
                if ( listModel.get(i).idValue == listModel.get(m).idValue )
                {
                    listModel.setProperty(i, "repeat_id", 1)
                    start = start == 0 ? i : start
                    flag = true
                    break
                }
            }
        }

        listView.currentIndex = start

        return flag
    }

    function clearIdRepeat()
    {
        // merge
        // merge
        for ( var i = listModel.count - 1; i >= 0; i--)
        {
            listModel.setProperty(i, "repeat_id", 0)

            for ( var m = i-1; m >= 0; m--)
            {
                if ( listModel.get(i).idValue == listModel.get(m).idValue )
                {
                    listModel.remove(i)
                    break
                }
            }
        }
    }

    Text {
        id: title
        color: "red"
        z: 10
        text: HMIBox.errorText
        font.family: "微软雅黑"
    }

    ListModel{ id: listModel }

    property var gIndex1: 0

    Item{
        visible: title.text === "" ? true : false
        anchors.fill: parent

        Column{
            anchors.fill: parent
            spacing: 5

            Row{
               id: row
               spacing: 5
               height: btn.height
               width: parent.width

               MyButton{
                   id: btn
                   text: "生成DBCData和dynamic_create.h"
                   onMyPress: {
                       if(checkIdRepeat())
                       {
                           title2.visible = true
                           return
                       }
                       else{
                           title2.visible = false
                       }
                       var list = new Array
                       for ( var i = 0; i < listModel.count; i++)
                       {
                           var map = {}
                           map["idName"] = listModel.get(i).idName
                           map["idValue"] = listModel.get(i).idValue
                           map["name"] = listModel.get(i).name
                           list.push(map)
                       }

                       HMIBox.newDBC(list)
                   }
               }

               MyButton{
                   id: btn2
                   width: 200
                   text: "一键清除重复id"
                   onMyPress: {
                       clearIdRepeat()
                   }
               }

               Text {
                   id: title2
                   color: "red"
                   height: row.height
                   verticalAlignment: Text.AlignVCenter
                   text: "有重复id,请检查红色文字"
                   font.family: "微软雅黑"
                   visible: false
               }
            }



            ListView{
                id: listView
                width: 666
                height: parent.height - row.height - 5
                clip: true
                model: listModel
                spacing: 0
                delegate: Component{
                    Item{
                        width: listView.width
                        height: 30

                        MouseArea{
                            width: parent.width
                            height: 30
                            onPressed: {
                                //                                console.log("click ", idName, idValue, structName, isChecked)
                                gIndex1 = index
                            }
                        }

                        Rectangle{
                            width: parent.width
                            height: 30
                            color: index % 2 == 0 ? "white" : Qt.rgba(248/255, 248/255, 248/255, 1)
                            opacity: 1.0
                        }

                        Rectangle{
                            width: parent.width
                            height: 1
                            color: Qt.rgba(235/255, 235/255, 235/255, 1)
                        }

                        Row{
                            id: item
                            width: parent.width
                            height: 30
                            spacing: -1

                            Rectangle{
                                width: 300
                                height: 30
                                color: Qt.rgba(0,0,0,0)
                                border.width: 0
                                border.color: "black"

                                TextEdit {
                                    id: t1
                                    anchors.fill: parent
                                    text: idName
                                    color: repeat_id ? "red" : "black"
                                    anchors.verticalCenter: parent.verticalCenter
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.leftMargin: 2
                                    font.family: "微软雅黑"
                                    selectByMouse: true
                                    onTextChanged: {
                                        listModel.setProperty(index, "idName", text)
                                    }
                                }
                            }

                            Rectangle{
                                width: 50
                                height: 30
                                color: Qt.rgba(0,0,0,0)
                                border.width: 0
                                border.color: "black"

                                TextEdit {
                                    text: idValue
                                    anchors.fill: parent
                                    selectByMouse: true
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    font.family: "微软雅黑"
                                    color: repeat_id ? "red" : "black"
                                    onTextChanged: {
                                        listModel.setProperty(index, "idValue", Number(text))
                                    }
                                }
                            }

                            Rectangle{
                                width: 300
                                height: 30
                                color: Qt.rgba(0,0,0,0)
                                border.width: 0
                                border.color: "black"

                                Text {
                                    text: name
                                    color: "black"
                                    anchors.centerIn: parent
                                    font.family: "微软雅黑"
                                }
                            }
                        }
                    }
                }

                ScrollBar.vertical: ScrollBar {
                    id: vbar
                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    policy: ScrollBar.AlwaysOn
                }
            }
        }
    }


    MessageDialog{
        id: dialog
        visible: false
        text: "生成DBCData和dynamic_create.h"
    }
}
