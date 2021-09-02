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

    //��ѡһ
//    ret_Vertex.x = (qt_Vertex.x)*(qt_Vertex.x)*(qt_Vertex.x)*settingCurveC3
//            + (qt_Vertex.x)*(qt_Vertex.x)*settingCurveC2
//            + (qt_Vertex.x)*settingCurveC1 + settingCurveC0;

    //��ѡһ
    highp float startY  = 100.0;
    //�˽ӿ��������ʺ�UIЧ�������������ȷ��˽ӿ�
//    if(qt_Vertex.y > startY){ //���������ʽضϣ�����Ϊֱ�߲���������
//        highp float deltaX = (qt_Vertex.y-startY ) * (qt_Vertex.y -startY)  * settingCurve;
//        ret_Vertex.x = qt_Vertex.x - deltaX / 500.0;
//    }

    //rh UI�ṩ���ʶ�Ӧ����������Ч��
    highp float tempY = 0.0;
    highp float imgHeight = 100.0;
    highp float aMax = 50.0*50.0; // �M�����ƫ��

    if(qt_Vertex.y < 44.0)    // �±���
    {
        tempY = 0.0;
    }
    else if(qt_Vertex.y < 100.0)   //����λ��
    {
        tempY = aMax - (100.0- qt_Vertex.y) * (100.0 - qt_Vertex.y);
    }
    else if(qt_Vertex.y < 300.0)    // �ϱ���
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
//    �޸Ķ�����ɫ��λ��xyzw��vec4(0.0, -15, 10, 0.0)
//    l_Position = perspectiveMat * (ret_Vertex + vec4(0.0, -15, 10, 0.0));

    gl_Position = projectMat * modelviewMat * ret_Vertex;

}
