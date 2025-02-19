#include "TeaPacket/TeaPacket.hpp"

int main()
{
    if (TeaPacket::Initialize() == 1)
    {
        while (TeaPacket::ShouldRun())
        {
            TeaPacket::Update();
            TeaPacket::Delay();
        }
    }

    TeaPacket::DeInitialize();
}