#pragma once

#include "TeaPacket/Graphics/Texture.hpp"
#include "TeaPacket/Graphics/Shader.hpp"

#include <string>

namespace TeaPacket::Graphics{

    class PlatformVideoPlayer;

    class VideoPlayer{
        public:
        Texture* texture;
        PlatformVideoPlayer* platformPlayer;

        bool loop = false;


        VideoPlayer(const std::string path, Texture* texture = nullptr);
        ~VideoPlayer();

        void UpdateFrame();
        void PrepareToDraw();
        bool Tick();

        public:
        static Shader* customShader;

        static int Init();
        static void DeInit();


    };
}