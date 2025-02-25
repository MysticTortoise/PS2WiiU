#pragma once

namespace TeaPacket::Graphics{
    class PlatformShader;
    class Shader{
        public:
        PlatformShader* platformShader;

        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();
    };
}