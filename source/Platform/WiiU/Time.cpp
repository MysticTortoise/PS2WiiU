#ifdef TP_WIIU
#include "TeaPacket/Time.hpp"

#include <coreinit/time.h>

double TeaPacket::Timing::GetTimeDouble(){
    return 0;
}
unsigned long long TeaPacket::Timing::GetTimeSeconds(){
    return OSTicksToSeconds(OSGetTick());
}
unsigned long long TeaPacket::Timing::GetTimeMilliseconds(){
    return OSTicksToMilliseconds(OSGetTick());
}
unsigned long long TeaPacket::Timing::GetTimeMicroseconds(){
    return OSTicksToMicroseconds(OSGetTick());
}
unsigned long long TeaPacket::Timing::GetTimeNanoseconds(){
    return OSTicksToNanoseconds(OSGetTick());
}
#endif