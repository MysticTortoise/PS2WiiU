#version 450

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

layout(binding = 0, std140) uniform uTransformData
{
    mat4 objectMatrix;
};
layout(binding = 1, std140) uniform uColorData{
    vec4 uf_color; // 16  0
};

layout(location = 0) out vec2 TexCoord;
layout(location = 1) out vec4 Color;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = objectMatrix * vec4(aPos, 0.0, 1.0);

    Color = uf_color;
}