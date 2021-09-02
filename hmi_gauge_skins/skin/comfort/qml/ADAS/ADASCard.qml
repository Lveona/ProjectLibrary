import QtQuick 2.0

Item {
    width: 1920
    height: 720

    property bool gapVisible: ADASScreen.accTimeGapVisible

    //跟车距
    Image{
        id: followBg
        x: 237
        y: 208
        source: "../Popup/pic_HMI_classic_default_road_followcar_base.png"
        ListView {
            id: gapList
            width: followBg.sourceSize.width
            y: 80
            height: 800
            spacing: 10
            model: gapListModel
            delegate: gapListCom
        }
        ListModel {
            id: gapListModel
            property bool completed: false

            property real accTimeGap: ADASScreen.accTimeGap

            Component.onCompleted: {
                for(var i = 0; i < accTimeGap; i++)
                {
                    gapListModel.append({"id" : i})
                }
                completed = true;
            }

            onAccTimeGapChanged: {
                if(completed){
                    gapListModel.clear()
                    for(var i = 0; i < accTimeGap; i++)
                    {
                        gapListModel.append({"id" : i})
                    }
                }
            }
        }
        Component {
            id: gapListCom
            Image{
                id: ig
                width: sourceSize.width
                height: sourceSize.height
                source: "../Popup/pic_HMI_classic_default_road_followcar_bar.png"
            }
        }
    }
}
