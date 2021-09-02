import QtQuick 2.0

Item{
    id:itemScroll

    property int scrollSpeed: 15
    property alias txtInfo: txtInfo

    clip: true
    CustomText{
      id:txtInfo
      onContentWidthChanged: {
          if(width>itemScroll.width){animScroll.running=false;x=0;animScroll.running=true;}
          else{animScroll.running=false;x=(((itemScroll.width-width)/2))}
      }
    }
    SequentialAnimation{
      id: animScroll
      loops: Animation.Infinite
      PropertyAnimation{ target: txtInfo; property: "x"; from: 0; to: -(txtInfo.width); duration: (txtInfo.width)*scrollSpeed; }
      PropertyAnimation{ target: txtInfo; property: "x"; from: itemScroll.width; to: 0; duration: (itemScroll.width)*scrollSpeed; }
    }
}
