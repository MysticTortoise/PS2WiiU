#pragma once

#include <string>

namespace TeaPacket::Files{

    int Init();
    void DeInit();

    std::string ReadTextFileString(const char* path);
    const char* ReadTextFile(const char* path);
}