#pragma once

#include "TeaPacket/Math/Vector2.hpp"
#include "TeaPacket/Math/Vector4.hpp"

namespace TeaPacket::Graphics
{
    class Camera{
        public:
        Math::Vector2 position = Math::Vector2(0,0);
        float angle = 0;
        Math::Vector2 scale = Math::Vector2(1,1);

        Math::Vector4 bgColor = Math::Vector4(0,0,0,1);
    };
} // namespace TeaPacket::Graphics
