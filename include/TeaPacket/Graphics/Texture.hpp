#pragma once


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

        Texture(const char* path, TextureFilterType filterType = TEXTURE_FILTER_LINEAR);
        ~Texture();

    };
} // namespace TeaPacket::Graphics
