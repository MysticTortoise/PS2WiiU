#include "TeaPacket/Math/Vector2.hpp"


TeaPacket::Math::Vector2::Vector2(float x, float y) : 
    x(x), y(y)
{}

TeaPacket::Math::Vector2::operator glm::vec<3, float, glm::packed_highp>(){
    return glm::vec3(x,y,0);
}