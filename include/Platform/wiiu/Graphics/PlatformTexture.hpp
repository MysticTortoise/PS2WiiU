#pragma once
#ifdef TP_WIIU

#include <gx2/texture.h>
#include <gx2/sampler.h>

namespace TeaPacket::Graphics
{
    class PlatformTexture{
        public:
        GX2Texture* gx2Tex;
        GX2Sampler* gx2Sampler;
    };
} // namespace TeaPacket::Graphics
#endif