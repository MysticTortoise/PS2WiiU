#version 450

layout(location = 0) in vec2 TexCoord;
layout(location = 1) in vec4 Color;

layout(location = 0) out vec4 FragColor;

layout(binding = 0) uniform sampler2D plane1Texture;
layout(binding = 1) uniform sampler2D plane2Texture;

layout(binding = 2, std140) uniform textureData
{
    int texFormat;
};

#include "shaders/inc/colorConversions.glsl"

vec4 sampleColor(vec2 uv){
    switch(texFormat){
        case TEX_RGBA:
            return texture(plane1Texture, uv);
        case TEX_NV12:
            return yuv_to_rgb(vec4(texture(plane1Texture,uv).r, texture(plane2Texture,uv).rg, 1.0));
    }
}

void main()
{
    FragColor = sampleColor(TexCoord) * Color;
}