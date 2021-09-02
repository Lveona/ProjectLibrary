import QtQuick 2.15
import QtQuick3D 1.15

Node {
    id: node
    x: 0
    y: 0
    z: 0
    scale.x: 1//node.type == 2 ? 0.5 : 1
    scale.y: 1//node.type == 2 ? 0.5 : 1
    scale.z: 0.5//node.type == 2 ? 0.5 : 1

    //车道前车类型：【0：不显示】【1：R8】【2：摩托车】【3：行人】【4：小型车】【5：卡车】 carbody.mesh
    property var nodeList: ["", "smallcar.mesh","moto.mesh","truck.mesh","pedestrian.mesh","carbody.mesh"]



    property alias posX: node.x
    property alias posY: node.y
    property alias posZ: node.z

    property alias rotationX: node.eulerRotation.x
    property alias rotationY: node.eulerRotation.y
    property alias rotationZ: node.eulerRotation.z

    property alias scaleX: node.scale.x
    property alias scaleY: node.scale.y
    property alias scaleZ: node.scale.z
    property alias isVisible: node.visible

    property var type: 0
    property var diffuseColor: "#ffffffff"

    Model {
        id: model
        source: nodeList[node.type] !== "" ?
            "qrc:/mesh/" + nodeList[node.type] : ""

        DefaultMaterial {
            id: defaultMaterial_material
            diffuseColor: node.diffuseColor
        }
        materials: [
            defaultMaterial_material
        ]
    }
}
