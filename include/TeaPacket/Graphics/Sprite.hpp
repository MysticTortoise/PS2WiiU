#pragma once

#include "TeaPacket/Graphics/Texture.hpp"
#include "TeaPacket/Graphics/Shader.hpp"
#include "TeaPacket/Graphics/Camera.hpp"
#include "TeaPacket/Math/Vector2.hpp"
#include "TeaPacket/Math/Vector4.hpp"

namespace TeaPacket::Graphics
{
    class Sprite
    {
    public:
        TeaPacket::Math::Vector2 position = TeaPacket::Math::Vector2(0,0);
        TeaPacket::Math::Vector2 scale = TeaPacket::Math::Vector2(1,1);
        float angle = 0;
        TeaPacket::Math::Vector2 anchor = TeaPacket::Math::Vector2(0,0);

        TeaPacket::Math::Vector4 color;

        
        Texture* texture;

        Sprite(Texture* texture = nullptr);
        void Draw();

        static Shader* spriteShader;
        
        static void SpriteRendererInit();
        static void SpriteRendererDeInit();
        static void BeginRenderFromCamera(Camera* camera);
    };

    extern TeaPacket::Math::Vector2 renderScale;
}