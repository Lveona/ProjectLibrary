#version 430

uniform highp float height;
uniform highp float width;

uniform highp float settingCurve;
uniform highp float settingCurvePlus;

uniform highp mat4 modelviewMat;
uniform highp mat4 projectMat;

uniform highp mat4 qt_Matrix;
uniform highp float qt_Opacity;

in highp vec4 qt_Vertex;
in highp vec2 qt_MultiTexCoord0;

out highp vec2 qt_TexCoord0;
out highp float deltaCurve;


void main() {
    qt_TexCoord0 = qt_MultiTexCoord0;

    highp vec4 ret_Vertex = qt_Vertex;

    if(qt_Vertex.y > 75.0){
//        highp float deltaX = (qt_Vertex.y - 0.25 * height) * (qt_Vertex.y - 0.25 * height) * settingCurve;
//        ret_Vertex.x = qt_Vertex.x - deltaX / 500.0;
//        deltaLeft = (qt_Vertex.y - 0.25 * height) * (qt_Vertex.y - 0.25 * height) * settingCurve;
//        deltaRight = (qt_Vertex.y - 0.25 * height) * (qt_Vertex.y - 0.25 * height) * settingCurvePlus;
//        ret_Vertex.x = qt_Vertex.x - deltaRight / 500.0;

        highp float deltaLeft = (qt_Vertex.y - 0.25 * height) * (qt_Vertex.y - 0.25 * height) * settingCurve;
        highp float deltaRight = (qt_Vertex.y - 0.25 * height) * (qt_Vertex.y - 0.25 * height) * settingCurvePlus;
        deltaCurve = deltaLeft / 500.0*(0.6990-qt_Vertex.x/300.0)/0.398 + deltaRight / 500.0*(qt_Vertex.x/300.0-0.3010)/0.398;

        ret_Vertex.x = qt_Vertex.x - deltaCurve;
    }

    gl_Position = projectMat * modelviewMat * ret_Vertex;

}
