#pragma once
#ifdef TP_WIIU

#include <gx2/texture.h>
#include <gx2/sampler.h>

#include <unordered_map>

namespace TeaPacket::Graphics
{
    class PlatformTexture{
        public:
        GX2Texture* gx2Tex;
        GX2Sampler* gx2Sampler;
    };

    extern const std::unordered_map<TextureFormat, GX2SurfaceFormat> TPFormatToGXFormat;
    extern const std::unordered_map<TextureFilterType, GX2TexXYFilterMode> TPFilterToGXFilter;
} // namespace TeaPacket::Graphics
#endif