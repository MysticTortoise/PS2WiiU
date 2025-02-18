#pragma once
#include "TeaPacket/Assets/Asset.hpp"
namespace TeaPacket
{
    class Sprite
    {
    public:
        int x;
        int y;
        int width;
        int height;
        Asset* sprite;
    };
}