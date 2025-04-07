#pragma once

namespace TeaPacket::Timing{

    double GetTimeDouble();

    unsigned long long GetTimeSeconds();
    unsigned long long GetTimeMilliseconds();
    unsigned long long GetTimeMicroseconds();
    unsigned long long GetTimeNanoseconds();
}