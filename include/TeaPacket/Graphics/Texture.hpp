#pragma once


namespace TeaPacket::Graphics
{
    class PlatformTexture;
    class Texture{
        public:
        
        int width;
        int height;
        int channelCount;
        PlatformTexture* platformTexture;

        Texture(const char* path);
        ~Texture();

    };
} // namespace TeaPacket::Graphics
