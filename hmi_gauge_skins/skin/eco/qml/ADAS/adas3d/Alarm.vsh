#version 320 es

uniform highp float height;
uniform highp float width;

uniform highp float settingLane1Pos;
uniform highp float settingLane2Pos;

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

//    if(qt_Vertex.y > 75.0){
//        highp float deltaX = (qt_Vertex.y - 0.25 * height) * (qt_Vertex.y - 0.25 * height) * settingCurve;
//        ret_Vertex.x = qt_Vertex.x - deltaX / 500.0;
//        deltaLeft = (qt_Vertex.y - 0.25 * height) * (qt_Vertex.y - 0.25 * height) * settingCurve;
//        deltaRight = (qt_Vertex.y - 0.25 * height) * (qt_Vertex.y - 0.25 * height) * settingCurvePlus;
//        ret_Vertex.x = qt_Vertex.x - deltaRight / 500.0;

    highp float startY  = 100.0;

    //rh UI提供曲率对应车道线弯曲效果
    highp float tempY = 0.0;
    highp float imgHeight = 100.0;
    highp float aMax = 50.0*50.0; // 橫向最大偏移

    if(qt_Vertex.y < 44.0)    // 下边线
    {
        tempY = 0.0;
    }
    else if(qt_Vertex.y < 100.0)   //中心位置
    {
        tempY = aMax - (100.0 - qt_Vertex.y) * (100.0 - qt_Vertex.y);
    }
    else if(qt_Vertex.y < 300.0)    // 上边线
    {
        tempY = aMax - (qt_Vertex.y - 100.0) * (qt_Vertex.y - 100.0);
    }
    else
    {
        tempY = 0.0;
    }

    highp float deltaLeft = tempY * settingCurve;
    highp float deltaRight = tempY * settingCurvePlus;

    //宽：600
    deltaCurve = deltaLeft / 200.0*(settingLane2Pos - qt_Vertex.x/600.0)/0.318 + deltaRight / 200.0*(qt_Vertex.x/600.0 - settingLane1Pos)/0.318;
    //deltaCurve = deltaLeft / 500.0*(0.6990-qt_Vertex.x/300.0)/0.398 + deltaRight / 500.0*(qt_Vertex.x/300.0-0.3010)/0.398;

    ret_Vertex.x = qt_Vertex.x + deltaCurve;

    gl_Position = projectMat * modelviewMat * ret_Vertex;

}
