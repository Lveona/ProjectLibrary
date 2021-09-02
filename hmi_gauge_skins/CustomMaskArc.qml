import QtQuick 2.0
import QtQuick3D 1.15
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.0

Model {
    id: thisCar_Model_Arc
    visible: true
    source: "#Rectangle"

    property var tradius
    property string tLineColor
    property var tStartAngle

    property bool adasAnim_MaskArc: true

    SequentialAnimation{
        id: anim_MaskArc
        running: adasAnim_MaskArc
        loops: Animation.Infinite
        NumberAnimation {target: aaaa; property: "opacity"; duration: 1000; from: 1.0; to: 0; easing.type: Easing.InOutQuad}
        NumberAnimation {target: aaaa; property: "opacity"; duration: 1000; from: 0; to: 1; easing.type: Easing.InOutQuad}
    }


    function gety(r, angle){
        return r + r * Math.sin(angle*Math.PI/180)
    }

    function getx(r, angle){
        return r + r * Math.cos(angle*Math.PI/180)
    }

    function getppos(r, angle){
        return Qt.point(getx(r, angle), gety(r, angle))
    }

    property point ponit1: getppos(tradius, tStartAngle) // 第二个点_最左侧
    property point ponit2: getppos(tradius, tStartAngle + 30)

    materials: DefaultMaterial { //材质
        diffuseMap: Texture {
            sourceItem: Item {
                width: 100
                height: 200

                Shape{
                    id:aaaa
                    anchors.fill: parent
                    antialiasing: true
                    smooth: true
                    layer.enabled: true
                    layer.samples: 8

                    ShapePath {
                        startX: ponit1.x
                        startY: ponit1.y
                        fillColor: "transparent"
                        strokeColor: tLineColor
                        strokeWidth: 1

                        PathArc {
                            x: ponit2.x
                            y: ponit2.y
                            radiusX: tradius
                            radiusY: tradius
                        }
                    }
                }
            }
        }
    }
}
