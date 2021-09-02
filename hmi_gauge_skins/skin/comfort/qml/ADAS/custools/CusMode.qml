import QtQuick 2.0
import QtQuick3D 1.15
import QtQuick3D.Materials 1.15

Model {
    id: cusMode
    source: "#Rectangle"
    pickable: false
    receivesShadows: false
    castsShadows: false
    tessellationMode: Model.NoTessellation //
    property var sourceSrc

    materials: DefaultMaterial {
        vertexColorsEnabled: false //
        diffuseMap: Texture {
            source: sourceSrc
            scaleU: 1 //
        }
    }


//    property alias name: ts.label
//    property alias min: ts.s
//    property alias max: ts.e
//    property alias val: ts.value
//    TestSlider{
//        id: ts
//        onVc: cameraYchange(v)
//    }
}
