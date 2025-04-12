#pragma once

#include <cstddef>
#include "TeaPacket/Graphics/TextureParameters.hpp"

namespace TeaPacket::Graphics
{


    class PlatformTexture;
    class Texture{
        public:
        
        TextureParameters parameters;
        PlatformTexture* platformTexture;

        private:
        public:

        Texture(const TextureParameters& parameters);
        ~Texture();

        // Update the contents of a Texture. MUST be the same width, height, and format.
        bool UpdateContents(unsigned char* data);

        public:
        static Texture* LoadFromFile(const char* path, const TextureParameters& parameters = {});

    };
} // namespace TeaPacket::Graphics
