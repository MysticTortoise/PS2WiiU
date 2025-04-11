#ifdef TP_WIIU
#include "TeaPacket/Graphics/Shader.hpp"
#include "WiiU/Graphics/PlatformShader.hpp"

#include "TeaPacket/Files/Files.hpp"

#include <gx2/shaders.h>
#include <gx2/mem.h>
#include <whb/gfx.h>

#include "CafeGLSL/CafeGLSLCompiler.hpp"
#include "TeaPacket/Logging.hpp"

#include <string>

using namespace TeaPacket;

TeaPacket::Graphics::Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath){
    char infoLog[1024];

    std::string vertexShaderCode = Files::ReadTextFile(vertexShaderPath);
    ParseShaderText(vertexShaderCode);
    GX2VertexShader* vertexShader = GLSL_CompileVertexShader(vertexShaderCode.c_str(), infoLog, sizeof(infoLog), GLSL_COMPILER_FLAG_NONE);
    if(!vertexShader){
        TeaPacket::Print("ERROR: Failed to compile vertex shader! Info Log:" + std::string(infoLog));
    }

    std::string fragmentShaderCode = Files::ReadTextFile(fragmentShaderPath);
    ParseShaderText(fragmentShaderCode);
    GX2PixelShader* pixelShader = GLSL_CompilePixelShader(fragmentShaderCode.c_str(), infoLog, sizeof(infoLog), GLSL_COMPILER_FLAG_NONE);
    if(!pixelShader){
        TeaPacket::Print("ERROR: Failed to compile fragment shader! Info Log:" + std::string(infoLog));
    }

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, vertexShader->program, vertexShader->size);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, pixelShader->program, pixelShader->size);

    WHBGfxShaderGroup* group = new WHBGfxShaderGroup();
    group->vertexShader = vertexShader;
    group->pixelShader = pixelShader;
    
    platformShader = new PlatformShader();
    platformShader->whbGroup = group;
}

TeaPacket::Graphics::Shader::~Shader(){
    WHBGfxFreeShaderGroup(platformShader->whbGroup);

    delete platformShader;
}

#endif