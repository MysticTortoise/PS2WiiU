#pragma once
#ifdef TP_WIIU

#include "whb/gfx.h"

namespace TeaPacket::Graphics{
    class PlatformShader{
        public:
        WHBGfxShaderGroup* whbGroup;
    };
}

#endif