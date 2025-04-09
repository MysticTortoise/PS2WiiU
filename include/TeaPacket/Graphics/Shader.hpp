#pragma once

#include "TeaPacket/Graphics/Texture.hpp"

namespace TeaPacket::Graphics{
    class PlatformShader;
    class Shader{
        public:
        PlatformShader* platformShader;

        void Use();

        void SetTexture(Texture* tex, int slot);

        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();
    };
}