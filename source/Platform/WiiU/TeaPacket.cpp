#ifdef TP_WIIU
#include "TeaPacket/TeaPacket.hpp"
#include "TeaPacket/Video.hpp"

#include <whb/proc.h>

using namespace TeaPacket;

bool TeaPacket::ShouldRun(){
    return WHBProcIsRunning();
}

void TeaPacket::Delay(){}


#endif