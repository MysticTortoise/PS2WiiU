#ifdef TP_WIN
#include "TeaPacket/TeaPacket.hpp"
#include "TeaPacket/Video.hpp"

#include "TeaPacket/DebugMacros.hpp"

#include <whb/proc.h>

using namespace TeaPacket;

bool TeaPacket::ShouldRun(){
    return WHBProcIsRunning();
}

void TeaPacket::Delay(){}


#endif