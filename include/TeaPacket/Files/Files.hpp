#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace TeaPacket::Files{

    int Init();
    void DeInit();

    std::string GetFilePath(const char* path);
    std::string ReadTextFile(const char* path);
    std::vector<char> ReadBinaryFile(const char* path);
}