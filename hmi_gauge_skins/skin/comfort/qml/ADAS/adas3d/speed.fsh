in highp vec2 qt_TexCoord0;
out highp vec4 FragColor;
highp vec4 retColor;

void main()
{
  if(qt_TexCoord0.y < settingTime*0.005 || qt_TexCoord0.y > (settingTime+100)*0.005)
    {
        retColor = vec4(0.0,0.0,0.0,0.0);
    }
    else
    {
        highp vec2 textureCoord;
        textureCoord.x = qt_TexCoord0.x;
        textureCoord.y = (qt_TexCoord0.y-settingTime*0.005)*2.0;
        retColor = texture(speedTexture, textureCoord);
    }

    if (retColor.a == 0.0)
    {
        retColor = vec4(0.0,0.0,0.0,0.0);
    }
    else
    {
        retColor = vec4(retColor.rgb * retColor.a, retColor.a);
    }
    FragColor = mix(retColor, vec4(0.125,0.149,0.298, 1.0), 0.5);

//    FragColor = vec4(1.0,0.0,0.0,1.0);
}
