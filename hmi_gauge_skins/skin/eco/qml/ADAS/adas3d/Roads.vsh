#version 320 es

uniform highp float height;
uniform highp float width;

uniform highp float settingTime;

uniform highp float settingCurve;
//uniform highp float settingCurveC0;
//uniform highp float settingCurveC1;
//uniform highp float settingCurveC2;
//uniform highp float settingCurveC3;
//X = C3*Y^3+C2*Y^2+C1*Y+C0

uniform highp mat4 modelviewMat;
uniform highp mat4 projectMat;

uniform highp mat4 qt_Matrix;
uniform highp float qt_Opacity;

in highp vec4 qt_Vertex;
in highp vec2 qt_MultiTexCoord0;

out highp vec2 qt_TexCoord0;


void main() {
    qt_TexCoord0 = qt_MultiTexCoord0;

    highp vec4 ret_Vertex = qt_Vertex;

    //二选一
//    ret_Vertex.x = (qt_Vertex.x)*(qt_Vertex.x)*(qt_Vertex.x)*settingCurveC3
//            + (qt_Vertex.x)*(qt_Vertex.x)*settingCurveC2
//            + (qt_Vertex.x)*settingCurveC1 + settingCurveC0;

    //二选一
    highp float startY  = 100.0;
    //此接口由于曲率和UI效果不符，所以先封存此接口
//    if(qt_Vertex.y > startY){ //车道线曲率截断，部分为直线不做弯曲。
//        highp float deltaX = (qt_Vertex.y-startY ) * (qt_Vertex.y -startY)  * settingCurve;
//        ret_Vertex.x = qt_Vertex.x - deltaX / 500.0;
//    }

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
        tempY = aMax - (100.0- qt_Vertex.y) * (100.0 - qt_Vertex.y);
    }
    else if(qt_Vertex.y < 300.0)    // 上边线
    {
        tempY = aMax - (qt_Vertex.y - 100.0) * (qt_Vertex.y - 100.0);
    }
    else
    {
        tempY = 0.0;
    }

    ret_Vertex.x = qt_Vertex.x + tempY * settingCurve/ 200.0;

//    highp float deltaX = (qt_Vertex.y - 0.3 * height) * (qt_Vertex.y - 0.3 * height) * settingCurve;
//    ret_Vertex.x = qt_Vertex.x - deltaX / 500.0;
//    修改顶点着色器位置xyzw：vec4(0.0, -15, 10, 0.0)
//    l_Position = perspectiveMat * (ret_Vertex + vec4(0.0, -15, 10, 0.0));

    gl_Position = projectMat * modelviewMat * ret_Vertex;

}
