#version 440

in vec2 fragPos;
in vec4 fragmentColor;
in vec2 fragUV;
out vec4 color;
uniform float time;
uniform sampler2D samp2d;

void main(){

    vec4 textureColor = texture(samp2d, fragUV);
    color = textureColor * fragmentColor;
    //color = vec4(fragmentColor.r * (cos(fragPos.x + time)+1)*0.5,
    //            fragmentColor.g * (cos(fragPos.y + time)+1)*0.5,
    //            fragmentColor.b * (cos(fragPos.x *0.4 + time)+1)*0.5, 1.0);
}