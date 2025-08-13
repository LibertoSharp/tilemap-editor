precision mediump float;
uniform float uTime;
uniform vec2 uResolution;
varying vec2 vUV;

void main() {
    vec2 uv = vUV;
    vec3 col = 0.5 + 0.5 * cos(uTime + uv.xyx + vec3(0, 2, 4));
    gl_FragColor = vec4(col, 1.0);
}
