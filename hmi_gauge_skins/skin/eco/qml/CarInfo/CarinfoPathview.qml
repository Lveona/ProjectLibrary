import QtQuick 2.8
import "./../Common/"

Item{
    id: item1
    width: 1920
    height: 720

    property int moveDuration: 10
    property int listMoveDirect: Manager.isCarInfoFaultChildDirect //1:down;-1:up
    property int isCarInfoFaultChildIndex: Manager.isCarInfoFaultChildIndex
    property int onePageCount: 3
    property real oneHeight: 64
    property real oneWidth: 239
    property int hightlightIndex: 0
    property int currentIndexPathView: 1    //映射对应的 isCarInfoFaultChildIndex = currentIndexPathView-1
    property int listLength: popupFaultQueryList.length

    //screen必须先set listMoveDirect，后set listIndex
    onIsCarInfoFaultChildIndexChanged: {
        updateList()
    }

    onListLengthChanged: {
        resetList()
    }

    function updateList(){
        handle(listMoveDirect, isCarInfoFaultChildIndex)
    }

    function resetList(){
            hightlightIndex = 0
            imgFocus1.y = 0
            currentIndexPathView = 1
    }

    Component.onCompleted: {
        //防止换主题时候在切换列表，要主动获取一次数据
        updateList()
    }

    ListModel{
        id: listModelSpeedWarning
    }

    Component{
        id: delegeteLine
        Item{
            id: delegeteItem
            width: oneWidth
            height: oneHeight
            property bool isSelect: index === currentIndexPathView
            CustomText {
                id:txtDelegate
                font.family:trLanguge("font")
                text: trLanguge(String(modelData.name).replace("\n",","))
                font.pixelSize: 28
                color: "white"
                width: oneWidth
                height: oneHeight
                elide: Text.ElideRight
                anchors.horizontalCenter: parent.horizontalCenter
                opacity: delegeteItem.isSelect?1:0.5
            }
        }
    }

    Column{
        visible: listLength===2
        x: 126
        y: 345
        CustomText {
            id:txtDelegate0
            font.family:trLanguge("font")
            text: trLanguge(String(popupFaultQueryList[0].name).replace("\n",","))
            font.pixelSize: 28
            color: "white"
            width: oneWidth
            height: oneHeight
            elide: Text.ElideRight
            opacity: 0 === isCarInfoFaultChildIndex?1:0.5
        }
        CustomText {
            id:txtDelegate1
            font.family:trLanguge("font")
            text: trLanguge(String(popupFaultQueryList[1].name).replace("\n",","))
            font.pixelSize: 28
            color: "white"
            width: oneWidth
            height: oneHeight
            elide: Text.ElideRight
            opacity: 1 === isCarInfoFaultChildIndex?1:0.5
        }
    }

    CustomText {
        id:txtDelegate2
        x: 126
        y: 345
        visible: listLength===1
        font.family:trLanguge("font")
        text: trLanguge(String(popupFaultQueryList[0].name).replace("\n",","))
        font.pixelSize: 28
        color: "white"
        width: oneWidth
        height: oneHeight
        elide: Text.ElideRight
        opacity: 0 === isCarInfoFaultChildIndex?1:0.5
    }

    function handle(dir, index){    //dir:down=1,up=-1
        //hightlight
        if(dir === 0) return;

        var hightMove = true
        if(dir === 1)
        {
            if(hightlightIndex >= onePageCount-1)
            {
                hightMove = false
            }
            else{
                hightlightIndex++
                imgFocus1.y = oneHeight*hightlightIndex
                hightMove = true
            }
        }
        else{
            if(hightlightIndex > 0)
            {
                hightlightIndex--
                imgFocus1.y = oneHeight*hightlightIndex
                hightMove = true
            }
            else{
                hightMove = false
            }
        }

        if(dir === 1)
        {
            //down key
            if(!hightMove)
            {
                listView1.incrementCurrentIndex()
            }
            else{
            }
            currentIndexPathView = (currentIndexPathView+1)%listLength
        }
        else{
            //up key
            if(!hightMove)
            {
                listView1.decrementCurrentIndex()
            }
            else{
            }
            if(currentIndexPathView-1<0)
            {
                currentIndexPathView = listLength - Math.abs(currentIndexPathView-1)%listLength
            }
            else{
                currentIndexPathView = (currentIndexPathView-1)%listLength
            }
        }
    }

    Item{
        id: itemClip
        x: 126
        y: 345
        width:oneWidth
        height: oneHeight*3
        clip: true

        PathView {
            id: listView1
            width: oneWidth
            model: popupFaultQueryList
            delegate: delegeteLine
            pathItemCount: onePageCount+2
            interactive: false
            visible: listLength > 2

            path: Path {
                startX: oneWidth/2
                startY: -oneHeight/2
                PathQuad { x: oneWidth/2; y: oneHeight*0+oneHeight/2; controlX: oneWidth/2; controlY: oneHeight*0+oneHeight/2 }
                PathQuad { x: oneWidth/2; y: oneHeight*1+oneHeight/2; controlX: oneWidth/2; controlY: oneHeight*1+oneHeight/2 }
                PathQuad { x: oneWidth/2; y: oneHeight*2+oneHeight/2; controlX: oneWidth/2; controlY: oneHeight*2+oneHeight/2 }
                PathQuad { x: oneWidth/2; y: oneHeight*3+oneHeight/2; controlX: oneWidth/2; controlY: oneHeight*3+oneHeight/2 }
                PathQuad { x: oneWidth/2; y: oneHeight*4+oneHeight/2; controlX: oneWidth/2; controlY: oneHeight*4+oneHeight/2 }
            }
        }

        Image{
            id: imgFocus1
            width: oneWidth
            height: oneHeight
            source: "ECU_List_Highlight.png"
            visible: listLength > 0
            Behavior on y{
                NumberAnimation{duration: moveDuration;}
            }
        }
    }
}
