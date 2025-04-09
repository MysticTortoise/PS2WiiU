#version 450

layout(location = 0) in vec2 TexCoord;
layout(location = 1) in vec4 Color;

layout(location = 0) out vec4 FragColor;

layout(binding = 0) uniform sampler2D yPlaneTex;
layout(binding = 1) uniform sampler2D uvPlaneTex;

void main()
{
    float y = texture(yPlaneTex, TexCoord).r;
    vec2 uv = texture(uvPlaneTex, TexCoord).rg;
    vec3 rgb = vec3(
        y + 1.402 * uv.x,
        y - 0.344 * uv.x - 0.714 * uv.y,
        y + 1.772 * uv.x
        );
    FragColor = vec4(rgb,1.0) * Color;
}