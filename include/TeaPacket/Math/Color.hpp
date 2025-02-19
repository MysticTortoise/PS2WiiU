#pragma once

#include "TeaPacket/Math/Vector4.hpp"

namespace TeaPacket::Math {
    union Color
    {
        Vector4 vec;
        {
            float r,
        }
    };

}