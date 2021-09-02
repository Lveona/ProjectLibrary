import QtQuick 2.0

Item {
    width: 1920;
    height: 1070;
    Rectangle{
        width: 640
        height: 1080
        color: "blue"
    }


    Timer{
        running: true
        interval: 20
        onTriggered: {
             console.log("rvctttttttttttttttttttttt start load font")
//            fontloaderCn.source = "file:////usr/share/neusoft/fonts/FZLanTingHeiS-R-GB.ttf"
//            fontloaderCn.source = "qrc:/fonts/FZLanTingHeiS-R-GB.ttf"
            fontloaderCn.source = "file:///E:/ReverseQT/DC/hmi/fonts/FZLanTingHeiS-R-GB.ttf"
        }
    }


property bool isFontLoad: false
    FontLoader{
        id: fontloaderCn
        //source: "/usr/share/neusoft/fonts/FZLanTingHeiS-R-GB.ttf"
        onStatusChanged: {
            if(FontLoader.Ready == status){
                console.log("rvctttttttttt finish load font CN:-", fontloaderCn.name, "-00")
//                loader_iradar.active = true

                timer1.restart()
            }
        }
    }

    Timer{
        id: timer1
        interval: 2000
        onTriggered: {
            loader_iradar.active = true
        }
    }


    Loader {
        id: loader_iradar;
        active: false

        onActiveChanged: {
            if(active)
            {
                console.log("loader_iradar load==", active)
                active = true
            }
        }

        sourceComponent: Component{
            Column{
                width: 200
                height: 200
                Text {
                    font.pixelSize: 30
                    //font.family: "FZLanTingHeiS-R-GB"  //"FZLanTingHeiS-R-GB"
                    //font.family: "Eurostile LT ExtendedTwo"
                //    font.family: "Source Han Sans CN"

                    smooth: true
                    renderType: Text.NativeRendering
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("123abc请注意周围环境")
                    font.family: fontloaderCn.name
                }

                Text {
                    font.pixelSize: 30
                    //font.family: "FZLanTingHeiS-R-GB"  //"FZLanTingHeiS-R-GB"
                    //font.family: "Eurostile LT ExtendedTwo"
                //    font.family: "Source Han Sans CN"

                    smooth: true
                    renderType: Text.NativeRendering
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: "FZLanTingHeiS-R-GB"
                    text: ("123abc请注意周围环境")
                }
            }


        }
    }
}
