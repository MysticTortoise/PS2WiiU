#ifdef TP_WIN
#include "TeaPacket/Graphics/Shader.hpp"
#include "TeaPacket/Platform/Windows/Graphics/PlatformShaderWin.hpp"

#include "TeaPacket/Files/Files.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "TeaPacket/DebugMacros.hpp"

#include <string>

using namespace TeaPacket;

TeaPacket::Graphics::Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath){
    std::string vertexShaderString = Files::ReadTextFileString(vertexShaderPath);
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
        ERROR("Vertex shader " << vertexShaderPath << " failed to compile! Error Log: " << infoLog);
    }
    #endif
    std::string fragmentShaderString = Files::ReadTextFileString(fragmentShaderPath);
    const char* fragmentShaderCode = fragmentShaderString.c_str();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    #ifdef TP_DEBUG
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        ERROR("Fragment shader " << fragmentShaderPath << " failed to compile! Error Log: " << infoLog);
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
        ERROR("Program built by " << fragmentShaderPath << " and " << vertexShaderPath << " failed to link! Error Log: " << infoLog);
    }
    #endif
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    platformShader = new PlatformShader();
    platformShader->handle = program;
}

#endif