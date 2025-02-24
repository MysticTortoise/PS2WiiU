#ifdef TP_WIIU
// Implementing
#include "TeaPacket/Graphics/Graphics.hpp"
// TeaPacket Utilities
#include "TeaPacket/DebugMacros.hpp"
// External Libraries
#include "CafeGLSL/CafeGLSLCompiler.hpp"
#include "whb/gfx.h"
// Header Dependencies
#include "TeaPacket/Video.hpp"


int TeaPacket::Graphics::Init(){
    if(!GLSL_Init())  { return -1; }
    if(!WHBGfxInit()) { return -1; }
}

void TeaPacket::Graphics::DeInit(){
    WHBGfxShutdown();
}

void TeaPacket::Graphics::BeginRender(){
    WHBGfxBeginRender();
}

#endif