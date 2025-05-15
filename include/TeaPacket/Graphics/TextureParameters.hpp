#pragma once

namespace TeaPacket::Graphics{
    enum TextureFilterType{
        TEXTURE_FILTER_LINEAR,
        TEXTURE_FILTER_POINT
    };

    enum TextureFormat{
        TEXTURE_FORMAT_RGBA8,
        TEXTURE_FORMAT_R8,
        TEXTURE_FORMAT_RG8,
    };

    enum TextureSwizzleChannelType{
        TEXTURE_CHANNEL_R = 0,
        TEXTURE_CHANNEL_G = 1,
        TEXTURE_CHANNEL_B = 2,
        TEXTURE_CHANNEL_A = 3,
        TEXTURE_CHANNEL_CONST_0 = 4,
        TEXTURE_CHANNEL_CONST_1 = 5
    };

    struct UnsafeTextureParameters{ // DO NOT USE UNLESS YOU KNOW WHAT YOU'RE DOING
        void* overrideData = nullptr;
    };

    struct TextureParameters{
        unsigned int width  = 0;
        unsigned int height = 0;

        TextureFilterType filterType = TEXTURE_FILTER_LINEAR;
        TextureFormat format = TEXTURE_FORMAT_RGBA8;

        TextureSwizzleChannelType swizzleMap[4] = {TEXTURE_CHANNEL_R, TEXTURE_CHANNEL_G, TEXTURE_CHANNEL_B, TEXTURE_CHANNEL_A};

        void* data;

        UnsafeTextureParameters unsafeParameters;
    };
}