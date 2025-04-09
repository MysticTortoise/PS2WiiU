#pragma once
#ifdef TP_WIIU

#include "TeaPacket/Files/FileStream.hpp"
#include <cstdint>

namespace TeaPacket::Graphics{

    class PlatformVideoPlayer{
        public:
        void* decoderMemory;
        uint8_t* h264Data;
        size_t h264DataSize;

        Texture* uvTexture;
    };
}
#endif