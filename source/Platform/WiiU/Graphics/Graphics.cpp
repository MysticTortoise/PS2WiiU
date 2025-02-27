#ifdef TP_WIIU
// Implementing
#include "TeaPacket/Graphics/Graphics.hpp"
// TeaPacket Utilities
#include "TeaPacket/Logging.hpp"
// External Libraries
#include "CafeGLSL/CafeGLSLCompiler.hpp"
#include "whb/gfx.h"
// Header Dependencies
#include "TeaPacket/Video.hpp"

#include <coreinit/debug.h>

int TeaPacket::Graphics::Init(){
    if(!GLSL_Init())  { return -1; }
    if(!WHBGfxInit()) { return -1; }
    return 1;
}

void TeaPacket::Graphics::DeInit(){
    WHBGfxShutdown();
}

void TeaPacket::Graphics::BeginRender(){
    WHBGfxBeginRender();
    WHBGfxBeginRenderTV();
}

void TeaPacket::Graphics::BeginSecondScreenRender(){
    WHBGfxFinishRenderTV();
    WHBGfxBeginRenderDRC();
}

void TeaPacket::Graphics::EndRender(){
    WHBGfxFinishRenderDRC();
    WHBGfxFinishRender();
}

#endif