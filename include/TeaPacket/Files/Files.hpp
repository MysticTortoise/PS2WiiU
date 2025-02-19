#pragma once

#include <string>

namespace TeaPacket::Files{
    std::string ReadTextFileString(const char* path);
    const char* ReadTextFile(const char* path);
}