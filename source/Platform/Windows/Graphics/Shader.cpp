#ifdef TP_WIN
#include "TeaPacket/Graphics/Shader.hpp"
#include "Windows/Graphics/PlatformShader.hpp"

#include "Windows/Graphics/PlatformTexture.hpp"

#include "TeaPacket/Files/Files.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "TeaPacket/Logging.hpp"

#include <string>

using namespace TeaPacket;

TeaPacket::Graphics::Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath){
    std::string vertexShaderString = Files::ReadTextFile(vertexShaderPath);
    const char* vertexShaderCode = vertexShaderString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    #ifdef TP_DEBUG
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        TeaPacket::PrintLine("Vertex shader " + std::string(vertexShaderPath) + " failed to compile! Error Log: " + infoLog);
    }
    #endif
    std::string fragmentShaderString = Files::ReadTextFile(fragmentShaderPath);
    const char* fragmentShaderCode = fragmentShaderString.c_str();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    #ifdef TP_DEBUG
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        TeaPacket::PrintLine("Fragment shader " + std::string(fragmentShaderPath) + " failed to compile! Error Log: " + infoLog);
    }
    #endif

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    #ifdef TP_DEBUG
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        TeaPacket::PrintLine("Program built by " + std::string(vertexShaderPath) + " and " + std::string(fragmentShaderPath) + " failed to link! Error Log: " + infoLog);
    }
    #endif
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    platformShader = new PlatformShader();
    platformShader->handle = program;
}

void TeaPacket::Graphics::Shader::Use(){
    glUseProgram(platformShader->handle);
}

void TeaPacket::Graphics::Shader::SetTexture(Texture* tex, int slot){
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, tex->platformTexture->handle);
}

TeaPacket::Graphics::Shader::~Shader(){
    glDeleteProgram(platformShader->handle);
    
    delete platformShader;
}

#endif