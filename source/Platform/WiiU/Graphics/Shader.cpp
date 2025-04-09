#ifdef TP_WIIU
#include "TeaPacket/Graphics/Shader.hpp"
#include "WiiU/Graphics/PlatformShader.hpp"

#include "WiiU/Graphics/PlatformTexture.hpp"

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
    GX2VertexShader* vertexShader = GLSL_CompileVertexShader(vertexShaderCode.c_str(), infoLog, sizeof(infoLog), GLSL_COMPILER_FLAG_NONE);
    //TeaPacket::PrintLine(vertexShaderCode);
    if(!vertexShader){
        TeaPacket::PrintLine("ERROR: Failed to compile vertex shader! Info Log:" + std::string(infoLog));
    }

    std::string fragmentShaderCode = Files::ReadTextFile(fragmentShaderPath);
    GX2PixelShader* pixelShader = GLSL_CompilePixelShader(fragmentShaderCode.c_str(), infoLog, sizeof(infoLog), GLSL_COMPILER_FLAG_NONE);
    //TeaPacket::PrintLine(fragmentShaderCode);
    if(!pixelShader){
        TeaPacket::PrintLine("ERROR: Failed to compile fragment shader! Info Log:" + std::string(infoLog));
    }

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, vertexShader->program, vertexShader->size);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, pixelShader->program, pixelShader->size);

    WHBGfxShaderGroup* group = new WHBGfxShaderGroup();
    group->vertexShader = vertexShader;
    group->pixelShader = pixelShader;
    
    platformShader = new PlatformShader();
    platformShader->whbGroup = group;
}

void TeaPacket::Graphics::Shader::Use(){
    GX2SetFetchShader(&(platformShader->whbGroup->fetchShader));
    GX2SetVertexShader(platformShader->whbGroup->vertexShader);
    GX2SetPixelShader(platformShader->whbGroup->pixelShader);
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);
}

void TeaPacket::Graphics::Shader::SetTexture(Texture* tex, int slot){
    GX2SetPixelTexture(tex->platformTexture->gx2Tex, platformShader->whbGroup->pixelShader->samplerVars[slot].location);
    GX2SetPixelSampler(tex->platformTexture->gx2Sampler, platformShader->whbGroup->pixelShader->samplerVars[slot].location);
}

TeaPacket::Graphics::Shader::~Shader(){
    WHBGfxFreeShaderGroup(platformShader->whbGroup);

    delete platformShader;
}

#endif