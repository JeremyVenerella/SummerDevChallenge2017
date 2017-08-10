#version 440

in vec2 vertPos;
in vec4 vertexColor;
in vec2 vertexUV;
out vec4 fragmentColor;
out vec2 fragPos;
out vec2 fragUV;

void main(){
    gl_Position.xy = vertPos;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    fragPos = vertPos;
    fragmentColor = vertexColor;
    fragUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}