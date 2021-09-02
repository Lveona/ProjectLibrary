#version 430

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
    if(settingCarFrontBottomAlarmEnable == 0) return originalColor;

    if(qt_TexCoord0.x < leftBorder || qt_TexCoord0.x > rightBorder) return originalColor;

    highp float dis = startPos - qt_TexCoord0.y;
    if(dis <= 0.0) return originalColor;

    if(qt_TexCoord0.y < 0.15) return originalColor;

    highp float opacity = clamp((2.2 * (rightBorder - leftBorder) - dis) / ( 2.2 * (rightBorder - leftBorder)), 0.0, 1.0);

    highp vec4 alarmColor = settingCarFrontBottomAlarmColor;

    return mix(originalColor, alarmColor, opacity);
}
highp vec4 drawCarFrontBottom(const highp float leftBorder,
                       const highp float rightBorder,
                       const highp vec4 originalColor)
{
//    if(qt_TexCoord0.x < leftBorder || qt_TexCoord0.x > rightBorder) return originalColor;
//    if((qt_TexCoord0.x-(deltaRight-deltaLeft)/150000.0) < leftBorder || qt_TexCoord0.x > rightBorder) return originalColor;
    if((qt_TexCoord0.x + deltaCurve/150000.0) < leftBorder || (qt_TexCoord0.x + deltaCurve/150000.0) > rightBorder) return originalColor;

    return mix(originalColor, vec4(0.125,0.149,0.298, 1.0), 1.0-qt_TexCoord0.y);
}

void main() {
    highp vec4 retColor = vec4(0.0, 0.0, 0.0, 0.0);
//    retColor = drawCarFrontBottom(0.3010 - settingLaneWidth/2.0,
//                       0.6990 + settingLaneWidth/2.0,
//                       retColor);
    retColor = drawCarFrontBottomAlarm(settingLane1Pos - settingLaneWidth/2.0,
                         settingLane2Pos + settingLaneWidth/2.0,
                         settingCarFrontBottomAlarmStartPos,
                         retColor);
    FragColor = retColor;
}
