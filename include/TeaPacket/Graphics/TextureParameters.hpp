#pragma once

namespace TeaPacket::Graphics{
    enum TextureFilterType{
        TEXTURE_FILTER_LINEAR,
        TEXTURE_FILTER_POINT
    };

    enum TextureFormat{
        TEXTURE_FORMAT_RGBA8,
    };

    struct TextureParameters{
        unsigned int width  = 0;
        unsigned int height = 0;

        TextureFilterType filterType = TEXTURE_FILTER_LINEAR;
        TextureFormat format = TEXTURE_FORMAT_RGBA8;

        void* data;
    };
}