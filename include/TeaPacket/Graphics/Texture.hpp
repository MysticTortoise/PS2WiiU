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
        
        unsigned int width;
        unsigned int height;
        PlatformTexture* platformTexture;

        private:
        TextureFilterType filterType = TEXTURE_FILTER_LINEAR;
        TextureFormat format = TEXTURE_FORMAT_RGBA8;
        public:

        Texture(unsigned char* data, unsigned int width, unsigned int height, TextureFormat = TEXTURE_FORMAT_RGBA8, TextureFilterType filterType = TEXTURE_FILTER_LINEAR);
        ~Texture();

        // Update the contents of a Texture. MUST be the same width, height, and format.
        bool UpdateContents(unsigned char* data);

        public:
        static Texture* LoadFromFile(const char* path, TextureFilterType filterType = TEXTURE_FILTER_LINEAR);

    };
} // namespace TeaPacket::Graphics
