import QtQuick 2.0

Item {
    id: frame
//    width: anc.width
//    height: anc.height

    function addZero(v)
    {
        if(v<10)
            return '0'+v
        return v
    }
    function onStart()
    {

    }
    function onPause()
    {

    }
    function onReStart()
    {

    }
    function onStop()
    {

    }

    property string path: "ADAS_RoadLine_White_"
    property int maxCount: 24

    property int startCount: 0
    property int count: startCount
    property int interval: 60
    property bool running: false
    property bool isOnce: false

    Image {
        id: anc
        source: path+addZero(count)+".png"
        cache: true
        sourceSize.width: 447
        sourceSize.height: 287
    }

    Timer{
        interval: frame.interval
        repeat: true
        running: frame.running
        onTriggered:{
            if(count>=maxCount)
            {
                if(isOnce)
                {
                    running = false
                    return
                }
                count = startCount
            }
            else{
                count++
            }
        }
    }
}
