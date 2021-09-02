import QtQuick 2.8
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.1

Item {
    id: root
    width: View.width
    height: View.height

    Connections{
        target: Hmibox
        onUpdateDatas: {
            updateData()
        }
    }

    Component.onCompleted: {
        if(listModels.count == 0)
            updateData()
    }


    function updateData(){
        var datas = Hmibox.getQmlDatas()
//         console.log("--^^^^^^^^^^^^^^^--------", data, datas.length)


        if(datas.length !== listModels.count)
        {
            listModels.clear()
            gIndex1 = 0
        }

        for(var i in datas)
        {
//            console.log("--^^^^^^^^^^^^^^^--------")
//            console.log(datas[i].idName, datas[i].idValue, datas[i].structName,
//                        datas[i].isChecked)

            var findIdName = false
            var findMsg = false

            var map = {}
            map["idName"] = datas[i].idName
            map["idValue"] = datas[i].idValue
            map["structName"] = datas[i].structName
            map["isChecked"] = datas[i].isChecked

//            if(filter != "") if(map["idName"].toLowerCase().indexOf(filter.toLowerCase()) != -1) findIdName = true

            var signales = new Array
            for(var j in datas[i].signales)
            {
//                console.log("----------")
//                console.log(datas[i].signales[j].name,
//                            datas[i].signales[j].bit,
//                            datas[i].signales[j].value)
                var map2 = {}
                map2["name"] = datas[i].signales[j].name
                map2["bit"] = datas[i].signales[j].bit
                map2["value"] = datas[i].signales[j].value

                signales.push(map2)
            }

            map["signales"] = signales

//            console.log("AAAAAAAAAAAA ", listModels.count , i)

            if(listModels.count <= i)
            {
                listModels.append(map)
            }
            else{
                listModels.set(i, map)
            }
        }
    }

    property var gIndex1: -1
//    property var gIndex2: -1

    ListModel{
        id: listModels
    }

    ListView{
        id: listView
        y: itemTitle.height
        width: 615
        height: parent.height-itemTitle.height
        model: listModels
        spacing: 0
        clip: true
//        currentIndex: gIndex1
//        onContentYChanged: console.log(contentY)

        delegate: Component{
            Item{
                id: citem
                width: listView.width
                height: isOpen ? 30 + listViewMsg.height : 30

//                property alias listViewMsg: listViewMsg
                property bool isOpen: true

                property var myIndex: gIndex1

                onMyIndexChanged: {
                    if(index == gIndex1)
                    {

                    }
                    else{
                        citem.isOpen = false
                    }
                }

                MouseArea{
                    width: parent.width
                    height: 30
                    onPressed: {
//                        console.log("click ", idName, idValue, structName, isChecked)
                        gIndex1 = index
                        citem.isOpen = !citem.isOpen
//                        timer.restart()
                    }
                }
//                Rectangle{
//                    width: parent.width
//                    height: 30
//                    color: gIndex1 == index ? "blue" : "white"
//                    opacity: 0.2
//                }

                Rectangle{
                    width: parent.width
                    height: 30
                    color: gIndex1 == index ? "blue" : (index % 2 == 0 ? "white" : Qt.rgba(248/255, 248/255, 248/255, 1) )
                    opacity: gIndex1 == index ? 0.5 : 1.0
                }

                Rectangle{
                    width: parent.width
                    height: 1
                    y: 30
                    color: Qt.rgba(235/255, 235/255, 235/255, 1)
                }

                Row{
                    id: item
                    width: parent.width
                    height: 30
                    spacing: 0

                    property bool selfCheck: false

                    Rectangle{
                        width: 200
                        height: 30
                        color: Qt.rgba(0,0,0,0)
                        border.width: 0
                        border.color: "black"

                        Text {
                            id: t1
                            text: idName
                            color: "black"
                            anchors.verticalCenter: parent.verticalCenter
                            x: 2
                            font.family: "微软雅黑"
                        }
                    }

                    Rectangle{
                        width: 50
                        height: 30
                        color: Qt.rgba(0,0,0,0)
                        border.width: 0
                        border.color: "black"

                        Text {
                            text: idValue
                            color: "black"
                            anchors.centerIn: parent
                            font.family: "微软雅黑"
                        }
                    }

                    Rectangle{
                        width: 250
                        height: 30
                        color: Qt.rgba(0,0,0,0)
                        border.width: 0
                        border.color: "black"

                        Text {
                            text: structName
                            color: "black"
                            anchors.centerIn: parent
                            font.family: "微软雅黑"
                        }
                    }

                    Rectangle{
                        width: 100
                        height: 30
                        anchors.verticalCenter: parent.verticalCenter
                        color: Qt.rgba(0,0,0,0)
                        border.width: 0
                        border.color: "black"

                        Rectangle{
                            anchors.centerIn: parent
                            width: 20
                            height: width
                            color: isChecked == 1 ? "green": "red"
                            radius: 50
                        }
                        MouseArea{
                            anchors.fill: parent
                            onPressed: {
//                                console.log("click isChecked", idName, idValue, structName, isChecked)
//                                listView.currentIndex = index
//                                item.selfCheck = !item.selfCheck
                                Hmibox.setSend(idName, isChecked == 0 ? 1:0)
                            }
                        }
                    }


                }

                // msg
                ListView{
                    id: listViewMsg
                    model: listModels.get(index).signales
                    height: listViewMsg.count * 30
                    spacing: 0
                    y: 30
                    visible: gIndex1 == index && citem.isOpen
                    width: parent.width

                    delegate: Component{

                        Item{
                            width: listViewMsg.width
                            height: 30

                            Rectangle{
                                width: parent.width
                                height: 30
                                color: index % 2 == 0 ? "white" : Qt.rgba(248/255, 248/255, 248/255, 1)
                                opacity: 1.0
                            }

                            Rectangle{
                                width: parent.width - 100
                                anchors.horizontalCenter: parent.horizontalCenter
                                height: 1
                                y: 29
                                color: "orange"
                            }

                            Row{
                                id: itemDel
                                width: listViewMsg.width
                                height: 30
                                spacing: 0

                                property bool isEdit: false

                                Rectangle{
                                    width: 200
                                    height: 30
                                    color: Qt.rgba(0,0,0,0)

                                    Text {
                                        id: t11
                                        text: name
                                        color: "black"
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.right: parent.right
                                        anchors.rightMargin: 2
                                        font.family: "微软雅黑"
                                    }
                                }

                                Rectangle{
                                    width: 50
                                    height: 30
                                    color: Qt.rgba(0,0,0,0)

                                    Text {
                                        id: t12
                                        text: bit
                                        color: "black"
                                        anchors.centerIn: parent
                                        font.family: "微软雅黑"
                                    }
                                }

                                Rectangle{
                                    width: 250
                                    height: 30
                                    color: Qt.rgba(0,0,0,0)

                                    TextEdit{
                                        id: t13
                                        anchors.fill: parent
                                        color: "red"
                                        text: value
                                        selectByMouse: true
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.family: "微软雅黑"

                                        Keys.enabled: true
                                        Keys.onPressed: {
                                            if (event.key == Qt.Key_Enter || event.key == Qt.Key_Return) {
    //                                            console.log("setValue");
                                                itemDel.isEdit = false
                                                Hmibox.setValue(idName, name, t13.text)
                                                event.accepted = true;
                                            }
                                        }
                                        onFocusChanged: {
                                            if(!focus)
                                            {
                                                if(value != t13.text)
                                                {
                                                    itemDel.isEdit = false
                                                     Hmibox.setValue(idName, name, t13.text)
                                                }
                                            }
                                        }
                                        onTextChanged: {
                                            if(focus)
                                            {
                                                itemDel.isEdit = true
                                            }
                                        }
                                    }

                                }

                                Rectangle{
                                    width: 100
                                    height: 30
                                    color: Qt.rgba(0,0,0,0)

                                    Text {
                                        id: t14
                                        text: itemDel.isEdit ? "编辑中/请按回车确认" : ""
                                        color: "red"
                                        font.pixelSize: 10
                                        anchors.centerIn: parent
                                        font.family: "微软雅黑"
                                    }
                                }
                            }

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

    Row{
        id: itemTitle
        width: parent.width
        height: 30
        spacing: 0

        Rectangle{
            width: 200
            height: 30
            color: Qt.rgba(0,0,0,0)
            border.width: 0
            border.color: "black"

            Text {
                id: t1
                text: "idName"
                color: "black"
                anchors.verticalCenter: parent.verticalCenter
                x: 2
                font.family: "微软雅黑"
            }
        }

        Rectangle{
            width: 50
            height: 30
            color: Qt.rgba(0,0,0,0)
            border.width: 0
            border.color: "black"

            Text {
                text: "idValue"
                color: "black"
                anchors.centerIn: parent
                font.family: "微软雅黑"
            }
        }

        Rectangle{
            width: 250
            height: 30
            color: Qt.rgba(0,0,0,0)
            border.width: 0
            border.color: "black"

            Text {
                text: "structName"
                color: "black"
                anchors.centerIn: parent
                font.family: "微软雅黑"
            }
        }

        Rectangle{
            width: 100
            height: 30
            color: Qt.rgba(0,0,0,0)
            border.width: 0
            border.color: "black"

            Text {
                text: "报文状态"
                color: "black"
                anchors.centerIn: parent
                font.family: "微软雅黑"
            }
        }
    }
    Rectangle{
        width: itemTitle.width
        height: 1
        y: itemTitle.y + itemTitle.height
        color: Qt.rgba(235/255, 235/255, 235/255, 1)
    }


    // search
    Column{
        width: 100
        height: 60
        x: listView.width + 10
        spacing: 10

        Text {
//            id: name
            text: "快速搜索"
            color: "gray"
            font.family: "微软雅黑"
        }

        Rectangle{
            width: 150
            height: 30
            color: Qt.rgba(0,0,0,0)
            border.width: 1
            border.color: "gray"
            clip: true

            TextInput{
               id: tinput
               anchors.centerIn: parent
               width: 100-4
               height: 26
               color: "black"
               selectByMouse: true
               font.pixelSize: 20

               onTextChanged: {
//                   console.log(tinput)
//                   updateData(text, true)
                   Hmibox.setSearch(text)
               }
            }
        }


        MyButton{
            text: "Animation"
            onMyPress: Hmibox.setPow("0")
        }

        MyButton{
            text: "D1"
            onMyPress: Hmibox.setPow("1")
        }

        MyButton{
            text: "D2"
            onMyPress: Hmibox.setPow("2")
        }

    }
}
