#pragma once

#include "glm/vec3.hpp"

namespace TeaPacket::Math{
    class Vector2{
        public:
            float x;
            float y;

            Vector2(float x = 0, float y = 0);

            operator glm::vec3();
    };
}