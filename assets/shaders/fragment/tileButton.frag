uniform sampler2D uTexture;
uniform float uTime;
uniform bool hovering;
void main()
{
    vec4 pixel = texture(uTexture, gl_TexCoord[0].xy);
    if (hovering)
    {
        pixel.rgb += (cos(uTime*3) + 1.0) / 13.0 + 0.1;
    }

    gl_FragColor = gl_Color * pixel;
}