#version 450

layout(location = 0) in vec2 TexCoord;
layout(location = 1) in vec4 Color;

layout(location = 0) out vec4 FragColor;

layout(binding = 0) uniform sampler2D spriteTexture;

void main()
{
    FragColor = texture(spriteTexture, TexCoord);
    FragColor *= Color;
}