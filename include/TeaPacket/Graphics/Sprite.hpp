#pragma once

#include "TeaPacket/Graphics/Texture.hpp"
#include "TeaPacket/Graphics/Shader.hpp"

namespace TeaPacket::Graphics
{
    class Sprite
    {
    public:
        float x;
        float y;
        float xScale;
        float yScale;
        float angle;
        
        
        Texture* texture;

        Sprite(Texture* texture = nullptr);
        void Draw();

        static Shader* spriteShader;
        
        static void SpriteRendererInit();
        static void SpriteRendererDeInit();
    };
}