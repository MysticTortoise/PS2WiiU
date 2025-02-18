#include "TeaPacket/TeaPacket.hpp"

int main()
{
    int result = TeaPacket::Initialize();
    if (result == 1)
    {
        while (TeaPacket::ShouldRun())
        {
            TeaPacket::Update();
            TeaPacket::Delay();
        }
    }

    TeaPacket::DeInitialize();
}