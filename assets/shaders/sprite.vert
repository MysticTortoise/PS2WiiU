#version 450

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

layout(location = 0) out vec2 TexCoord;

layout(binding = 0, std140) uniform uTransformData
{
    mat4 matrix;
};

void main()
{
    TexCoord = aTexCoord;
    gl_Position = matrix * vec4(aPos,0.0,1.0);
}