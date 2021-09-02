#version 320 es

uniform highp float settingLaneWidth;
uniform highp float settingLane1Pos;
uniform highp float settingLane2Pos;

uniform highp float settingCarFrontBottomAlarmStartPos;
uniform highp int   settingCarFrontBottomAlarmEnable;
uniform highp vec4  settingCarFrontBottomAlarmColor;

in highp vec2 qt_TexCoord0;
in highp float deltaCurve;
out highp vec4 FragColor;


highp vec4 drawCarFrontBottomAlarm( const highp float leftBorder,
                                    const highp float rightBorder,
                                    const highp float startPos,
                                    const highp vec4 originalColor) {

//    if(qt_TexCoord0.x<(0.3)) return vec4(1.0, 0.0, 0.0, 0.0);
//    if(qt_TexCoord0.x<(0.5)) return vec4(0.0, 1.0, 0.0, 0.0);
//    if(qt_TexCoord0.x<(0.7)) return vec4(0.0, 0.0, 1.0, 0.0);
//    return vec4(1.0, 1.0, 1.0, 0.0);

    if(settingCarFrontBottomAlarmEnable == 0) return originalColor;

    if(qt_TexCoord0.x < leftBorder || qt_TexCoord0.x > rightBorder) return originalColor;

    highp float dis = 0.30 - qt_TexCoord0.y;
    if(dis <= 0.0) return originalColor;

    if(qt_TexCoord0.y < 0.07) return originalColor;

    //乘2 作用实从0-2
    highp float opacity = (clamp((0.70 * (rightBorder - leftBorder) - dis) / (0.70 * (rightBorder - leftBorder)), 0.0, 1.0)  * 2.0);
    //下边渐变+上边渐变
    if(opacity > 1.0) opacity = 2.0 - opacity;

    highp vec4 alarmColor = settingCarFrontBottomAlarmColor;

    return mix(originalColor, alarmColor, opacity);
}
//highp vec4 drawCarFrontBottom(const highp float leftBorder,
//                       const highp float rightBorder,
//                       const highp vec4 originalColor)
//{
//    if((qt_TexCoord0.x + deltaCurve/150000.0) < leftBorder || (qt_TexCoord0.x + deltaCurve/150000.0) > rightBorder) return originalColor;

//    return mix(originalColor, vec4(0.125,0.149,0.298, 1.0), 1.0-qt_TexCoord0.y);
//}

void main() {
    highp vec4 retColor = vec4(0.0, 0.0, 0.0, 0.0);

    //settingLane0Pos起始车道线位置
    //settingLane1Pos终止车道线位置
    retColor = drawCarFrontBottomAlarm(settingLane1Pos - settingLaneWidth/2.0,
                        settingLane2Pos + settingLaneWidth/2.0,
                         settingCarFrontBottomAlarmStartPos,
                         retColor);

    FragColor = retColor;
}
