#pragma once


#include <string>
namespace TeaPacket::Graphics{
    class PlatformShader;
    class Shader{
        public:
        PlatformShader* platformShader;

        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();
        public:
        static std::string& ParseShaderText(std::string& text);
    };
}