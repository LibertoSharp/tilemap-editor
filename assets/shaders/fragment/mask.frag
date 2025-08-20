#version 460 core
layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;

uniform sampler2D uTexture;
uniform vec4 maskRect;
out vec4 outputColor;
in vec4 gl_Color;
in vec4 gl_TexCoord[];

void main()
{
    vec4 pixel = texture(uTexture, gl_TexCoord[0].xy);
    vec2 pixelPos = gl_FragCoord.xy;
    if (pixelPos.x <= maskRect.x || pixelPos.x >= (maskRect.x + maskRect.z) || pixelPos.y <= maskRect.y || pixelPos.y >= (maskRect.y + maskRect.w))
        pixel = vec4(0,0,0,0);

    outputColor = gl_Color * pixel;
}