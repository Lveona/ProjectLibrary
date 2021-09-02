import QtQuick 2.0

Item {
    id: indicator_Item
    x: 119
    y: 269
    width: 100
    property real indicatorCount: 0
    property real curIndicatorIndex
    property real highLightIndex: 0     //当前高亮下标
    property real tempIndex: 0
    property real min

    property real lightLength: 33
    property real normalLenght: 9

    onIndicatorCountChanged: {
        if(indicatorCount > 5){
            indicatorList.height = normalLenght * 4 + indicatorList.spacing * 4 + 33
        }
        else{
            indicatorList.height = normalLenght * (indicatorCount - 1) + indicatorList.spacing * (indicatorCount - 1) + 33
        }
    }

    onCurIndicatorIndexChanged: {
        getHighLightIndex()
    }

    function getHighLightIndex(){
//        console.log("--",curIndicatorIndex, tempIndex,highLightIndex, min);
        if(highLightIndex === 4 && curIndicatorIndex > tempIndex){
            min = curIndicatorIndex - 4;
        }else if(highLightIndex === 0 && curIndicatorIndex < tempIndex)
        {
            min = curIndicatorIndex;
        }else{
            if(curIndicatorIndex - min < 0){
                min = highLightIndex = 0
            }else if(curIndicatorIndex - min > 4){
                highLightIndex = 4
                min = curIndicatorIndex - 4
            }else{
                highLightIndex = curIndicatorIndex - min
            }
        }
//        console.log(curIndicatorIndex, tempIndex,highLightIndex, min);
        tempIndex = curIndicatorIndex;
    }

    ListView {
        id: indicatorList
        width: 100
        spacing: 8
        model: indicatorListModel
        currentIndex: highLightIndex
        delegate: indicatorDelegate
    }
    ListModel {
        id: indicatorListModel
        property bool completed: false
        Component.onCompleted: {
            for(var i = 0; i < 5; i++)
            {
                indicatorListModel.append({"id" : i})
            }
            completed = true;
        }
    }
    Component {
        id: indicatorDelegate
        Image{
            id: ig
            width: sourceSize.width
            height: sourceSize.height
            source: index === highLightIndex ? "../Home/select.png" : "../Home/unselect.png"
        }
    }
}

