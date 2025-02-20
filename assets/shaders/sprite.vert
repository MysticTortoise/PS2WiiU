#version 450

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

layout(binding = 0, std140) uniform uTransformData
{
    vec2 uf_pos; //   8   0
    vec2 uf_anchor; // 8  8
    float uf_rot; //  4 -> 8  16
    vec2 uf_scale; // 8   24
    //28
};
layout(binding = 1, std140) uniform uColorData{
    vec4 uf_color; // 16  0
};

layout(location = 0) out vec2 TexCoord;
layout(location = 1) out vec4 Color;

void main()
{
    vec2 transformedPos = aPos;

    // I really should use matrices but.. honestly i dont want to bug the poor people of FTU anymore so this will do for now.
    transformedPos += vec2(uf_anchor.x, -uf_anchor.y);

    // Scale
    transformedPos *= uf_scale;

    // Rotate
    float s = sin(uf_rot);
    float c = cos(uf_rot);
    transformedPos.x = transformedPos.x * c - transformedPos.y * s;
    transformedPos.y = transformedPos.x * s + transformedPos.y * c;

    // Transform
    transformedPos += vec2(uf_pos.x, -uf_pos.y);

    TexCoord = aTexCoord;
    gl_Position = vec4(transformedPos.x, transformedPos.y, 0.0f, 1.0f);


    Color = uf_color;
}