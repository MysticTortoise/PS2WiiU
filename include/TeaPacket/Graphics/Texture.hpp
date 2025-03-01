#pragma once

#include <cstddef>

namespace TeaPacket::Graphics
{
    enum TextureFilterType{
        TEXTURE_FILTER_LINEAR,
        TEXTURE_FILTER_POINT
    };

    enum TextureFormat{
        TEXTURE_FORMAT_RGBA8,
    };

    class PlatformTexture;
    class Texture{
        public:
        
        int width;
        int height;
        PlatformTexture* platformTexture;

        private:
        TextureFilterType filterType = TEXTURE_FILTER_LINEAR;
        TextureFormat format = TEXTURE_FORMAT_RGBA8;
        public:

        Texture(unsigned char* data, size_t dataSize, TextureFilterType filterType = TEXTURE_FILTER_LINEAR);
        ~Texture();

        public:
        static Texture* LoadFromFile(const char* path, TextureFilterType filterType = TEXTURE_FILTER_LINEAR);

    };
} // namespace TeaPacket::Graphics
