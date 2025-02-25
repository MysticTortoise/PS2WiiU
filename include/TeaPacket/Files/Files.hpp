#pragma once

#include <fstream>
#include <string>

namespace TeaPacket::Files{

    int Init();
    void DeInit();

    std::string GetFilePath(const char* path);
    std::string ReadTextFile(const char* path);
    const char* ReadBinaryFile(const char* path, size_t* size);
}