#version 450

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

layout(location = 0) out vec2 TexCoord;
layout(location = 1) out vec4 Color;

layout(binding = 0, std140) uniform uObjectData
{
    mat4 objectMatrix;
    vec4 colorData;
};

layout(binding = 1, std140) uniform uStaticData
{
    mat4 cameraMatrix;
};

void main()
{
    TexCoord = aTexCoord;
    Color = colorData;
    gl_Position = cameraMatrix * objectMatrix * vec4(aPos,0.0,1.0);
}