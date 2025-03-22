#pragma once

#include "TeaPacket/Scene/SceneScript.hpp"

#include "TeaPacket/Graphics/VideoPlayer.hpp"
#include "TeaPacket/Graphics/Sprite.hpp"

namespace PostShift2
{
    class VideoTest : public TeaPacket::Scene::SceneScript{
        public:
        void Load() override;
        void Update() override;
        void Draw(int screenIndex = 0) override;
        void Deload() override;
        private:

        TeaPacket::Graphics::VideoPlayer* videoPlayer;

        TeaPacket::Graphics::Sprite sprite1;

        TeaPacket::Graphics::Camera camera;
    };
} // namespace PostShift2
