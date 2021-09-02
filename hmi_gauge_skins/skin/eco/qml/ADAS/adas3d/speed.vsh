in vec3 attr_pos;
in vec2 attr_uv0;

out highp vec2 qt_TexCoord0;

uniform mat4 modelViewProjection;

void main()
{
    qt_TexCoord0 = attr_uv0;

    highp vec4 qt_Vertex = vec4(attr_pos, 1.0);

    gl_Position = modelViewProjection * qt_Vertex;
}
