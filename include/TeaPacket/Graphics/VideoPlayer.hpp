#pragma once

#include "TeaPacket/Graphics/Texture.hpp"

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
        bool Tick();

        private:
        bool textureOwnedBySelf = false;

        public:
        static int Init();
        static void DeInit();


    };
}