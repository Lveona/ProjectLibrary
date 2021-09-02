#version 320 es

uniform highp float settingTime;
uniform highp float digitSpeed;

uniform highp int   settingLaneCycles;
uniform highp float settingLaneWidth;

uniform highp float settingLanePos;
uniform highp int   settingLaneType;
uniform highp int   settingIsMirrored;

uniform highp float settingCutRoad;

uniform highp int   settingLaneLuminousEnable;

uniform sampler2D   singleDashOfLaneWithLumination;
uniform sampler2D   singleDashOfLaneWithoutLumination;

uniform highp vec4 laneSetColor;
uniform highp vec4 laneSetLuminousColor;

highp float luminousWidth;

in highp vec2 qt_TexCoord0;
out highp vec4 FragColor;

highp vec4 mixSampleColorWithLaneColor( const highp vec2 coord,
                                        const highp vec3 laneColor,
                                        const highp int luminousEnable,
                                        const highp vec3 laneLuminousColor) {


    highp float sampleAlpha;

//    return texture(singleDashOfLaneWithLumination, coord);

    if(luminousEnable == 1) {
        sampleAlpha = texture(singleDashOfLaneWithLumination, coord).a;
        return vec4(laneLuminousColor * sampleAlpha, sampleAlpha); //premultipled
    } else {
        sampleAlpha = texture(singleDashOfLaneWithoutLumination, coord).a;
        return vec4(laneColor*(1.0-qt_TexCoord0.y)*sampleAlpha, (1.0-qt_TexCoord0.y)*sampleAlpha);
    }

//    if (sampleAlpha == 1.0) {
//        return vec4(laneColor*(1.0-qt_TexCoord0.y)*sampleAlpha, (1.0-qt_TexCoord0.y)*sampleAlpha);
//    } else {
//        return vec4(laneLuminousColor * sampleAlpha, sampleAlpha); //premultipled
//    }
//    if (sampleAlpha == 1.0) {
//        return vec4(laneColor, 1.0);
//    } else {
//        return vec4(laneLuminousColor * sampleAlpha, sampleAlpha); //premultipled
//    }
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

    highp vec2 textureCoord;

    if(isMirrored == 0) {
        textureCoord.x = (qt_TexCoord0.x -startX) / (stopX - startX);
    } else {
        textureCoord.x = (stopX - qt_TexCoord0.x) / (stopX - startX);
    }

    //rh 固定车道线长度 截取在0.065 - 0.30 之间
    if(digitSpeed >= 0.0 && digitSpeed < 10.0){
        if(qt_TexCoord0.y < 0.027 || qt_TexCoord0.y > 0.135)   //低速 描画区域，调整车道线长度
        {
            return originalColor;
        }
    }else if(digitSpeed >= 10.0 && digitSpeed <= 90.0){
        if(qt_TexCoord0.y < 0.065 || qt_TexCoord0.y > 0.3)   //中速 描画区域，调整车道线长度
        {
            return originalColor;
        }
    }else{
        if(qt_TexCoord0.y < 0.002 || qt_TexCoord0.y > 0.35)   //高速 描画区域，调整车道线长度
        {
            return originalColor;
        }
    }
	    //虚线/实线
        //textureCoord.y = step(1.5, float(laneType))*0.5 + (1.0-step(1.5, float(laneType)))*(fract(qt_TexCoord0.y*40.0)*0.5 + settingTime*0.005);


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
