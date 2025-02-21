#pragma once

#include "TeaPacket/Scene/SceneScript.hpp"

#include "TeaPacket/Graphics/Texture.hpp"
#include "TeaPacket/Graphics/Sprite.hpp"

namespace PostShift2
{
    class TestScene : public TeaPacket::Scene::SceneScript{
        public:
        void Load() override;
        void Update() override;
        void Draw() override;
        void Deload() override;
        private:

        TeaPacket::Graphics::Texture* testTex1;
        TeaPacket::Graphics::Texture* testTex2;

        TeaPacket::Graphics::Sprite sprite1;
        TeaPacket::Graphics::Sprite sprite2;

        TeaPacket::Graphics::Camera camera;
    };
} // namespace PostShift2
