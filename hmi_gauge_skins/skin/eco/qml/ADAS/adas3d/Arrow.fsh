#version 320 es

uniform highp float settingTime;

uniform highp int   settingLaneCycles;
uniform highp float settingLaneWidth;

uniform highp float settingLanePos;
uniform highp int   settingLaneType;
uniform highp int   settingIsMirrored;

uniform highp float settingCutRoad;

uniform highp int   settingLaneLuminousEnable;

uniform sampler2D   singleDashOfLaneWithLumination;

uniform highp vec4 laneSetColor;
uniform highp vec4 laneSetLuminousColor;

uniform highp float   settingCarFrontBottomAlarmGradual1;
uniform highp float   settingCarFrontBottomAlarmGradual2;

highp float luminousWidth;

in highp vec2 qt_TexCoord0;
out highp vec4 FragColor;

highp vec4 mixSampleColorWithLaneColor( const highp vec2 coord,
                                        const highp vec3 laneColor,
                                        const highp int luminousEnable,
                                        const highp vec3 laneLuminousColor) {


    highp float sampleAlpha;

    //    return texture(singleDashOfLaneWithLumination, coord);

    sampleAlpha = texture(singleDashOfLaneWithLumination, coord).a;//图片 坐标

    highp vec4 transparent = vec4(laneLuminousColor * sampleAlpha, sampleAlpha); // 箭头和透明区域

    highp vec2 my_TexCoord0 = vec2(0.0, 0.0);
    highp float bottomLine = 0.070;  //下线
    highp float topLine = 0.3;  //上线
    highp float lenLine = 0.235;  //差值
    highp float gradualLen = 0.2; //渐变值

    my_TexCoord0.y = (qt_TexCoord0.y - bottomLine) / lenLine;  // 提升为0-1

    if(settingCarFrontBottomAlarmGradual1 != 0.0 && settingCarFrontBottomAlarmGradual2 == 1.0)
    {
        // part 1
        if(my_TexCoord0.y < settingCarFrontBottomAlarmGradual1)
        {
            sampleAlpha = 1.0;
        }
        else if(my_TexCoord0.y > settingCarFrontBottomAlarmGradual1 + gradualLen)
        {
            sampleAlpha = 0.0;
        }
        else
        {
            //减去偏移量settingCarFrontBottomAlarmGradual1
            // my_TexCoord0.y 0.2-0.5   settingCarFrontBottomAlarmGradual1=0.2
//            (my_TexCoord0.y - settingCarFrontBottomAlarmGradual1) // 0-0.3=>1-0
              sampleAlpha = 1.0 - (my_TexCoord0.y - settingCarFrontBottomAlarmGradual1) / gradualLen;   // 0-1=>1-0
//            sampleAlpha = (1 - (my_TexCoord0.y - settingCarFrontBottomAlarmGradual1)) / (settingCarFrontBottomAlarmGradual1);
        }
    }
    else if(settingCarFrontBottomAlarmGradual1 == 1.0 && settingCarFrontBottomAlarmGradual2 != 0.0)
    {
        // part 2
        // settingCarFrontBottomAlarmGradual2 1-0
        if(my_TexCoord0.y > (1.0 - settingCarFrontBottomAlarmGradual2) + gradualLen){
            sampleAlpha = 1.0;
        }
        else if(my_TexCoord0.y <  1.0 - settingCarFrontBottomAlarmGradual2)
        {
            sampleAlpha = 0.0;
        }
        else{
            //my_TexCoord0.y 0.2-0.5  settingCarFrontBottomAlarmGradual2=0.8
//             (my_TexCoord0.y - (1-settingCarFrontBottomAlarmGradual2)) // 0-0.3=>0-1
               sampleAlpha = (my_TexCoord0.y - (1.0-settingCarFrontBottomAlarmGradual2))  / gradualLen;   // 0-1
//            sampleAlpha = (my_TexCoord0.y - (1 - settingCarFrontBottomAlarmGradual2)) / (settingCarFrontBottomAlarmGradual2);
        }
    }
    else{
        sampleAlpha = 0.0;
    }

    //备份透明度（车道线+三角 跑动）
//    if(sampleAlpha < settingTime/100) sampleAlpha = 0.0;
//    else{
//        sampleAlpha = coord.y - settingTime/100;
//    }

    transparent = vec4(vec3(transparent) *sampleAlpha, 0.0);//渐变

    return transparent; //premultipled

}

highp vec4 drawLane( const highp float lanePos,
                     const highp int laneType,
                     const highp int isMirrored,
                     const highp int luminousEnable,
                     const highp vec4 originalColor)
{
    if (laneType == 0) return originalColor;

    highp float startX, stopX;

    if (isMirrored == 0)
    {
        startX = clamp(lanePos - settingLaneWidth/2.0, 0.0, 1.0);
        stopX  = clamp(lanePos + settingLaneWidth/2.0 + luminousWidth, 0.0, 1.0);
    }
    else
    {
        startX = clamp(lanePos - settingLaneWidth/2.0 - luminousWidth, 0.0, 1.0);
        stopX  = clamp(lanePos + settingLaneWidth/2.0, 0.0, 1.0);
    }

    if (qt_TexCoord0.x > stopX || qt_TexCoord0.x < startX)
        return originalColor;

    highp vec3 laneColor = laneSetColor.xyz;
    highp vec3 laneLuminousColor = laneSetLuminousColor.xyz;

    highp vec2 textureCoord = qt_TexCoord0;

    if(isMirrored == 0) {
        textureCoord.x = (qt_TexCoord0.x -startX) / (stopX - startX);
    } else {
        textureCoord.x = (stopX - qt_TexCoord0.x) / (stopX - startX);
    }

    //rh 固定车道线长度 截取在0.065 - 0.29 之间
    if(qt_TexCoord0.y < 0.065 || qt_TexCoord0.y > 0.29)   //描画区域，调整车道线长度
    {
        return originalColor;
    }
//    else
    {

        //	step(a, x)	Returns (x >= a) ? 1 : 0
        // fract 取小数
        // laneType =1 虚线；=2 实线
        // 虚线每次描绘都是[0-0.5],[0+settingTime , 0.5+settingTime],size=0.5

        //比大小step()
//        textureCoord.y = step(2.5, float(laneType))*0.5 + (1.0-step(2.5, float(laneType)))*(fract(qt_TexCoord0.y*40.0)*0.5 + settingTime*0.005);
//        textureCoord.y = 1*0.5 ;
        textureCoord.y = (1.0)*(fract(qt_TexCoord0.y*40.0)*0.5 + settingTime*0.005);

//        textureCoord.y = textureCoord.y/2 + settingTime*0.005;
    }


    return mixSampleColorWithLaneColor(textureCoord,
                                   laneColor,
                                   luminousEnable,
                                   laneLuminousColor);
}

void main() {
    luminousWidth = 123.0 / 35.0 * settingLaneWidth;

    highp vec4 retColor = vec4(0.0, 0.0, 0.0, 0.0);
    retColor = drawLane( settingLanePos,
                         settingLaneType,
                         settingIsMirrored,
                         settingLaneLuminousEnable,
                         retColor);

    FragColor = retColor;
}
