#ifdef TP_WIIU
#include "TeaPacket/Logging.hpp"

#include <coreinit/debug.h>
#include <whb/log_udp.h>
#include <whb/proc.h>

void TeaPacket::PrintString(std::string val) {
    std::string temp(val + "\n");
    OSReport(temp.c_str());
}

int TeaPacket::LogInit(){
    WHBLogUdpInit();
    WHBProcInit();
    return 1;
}
void LogDeInit(){
    WHBLogUdpDeinit();
    WHBProcShutdown();
}

#endif