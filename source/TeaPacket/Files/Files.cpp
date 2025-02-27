#include "TeaPacket/Files/Files.hpp"

#include "TeaPacket/Logging.hpp"

#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>


std::string TeaPacket::Files::ReadTextFile(const char* path){
    std::ifstream t(GetFilePath(path), std::ios::in);
    std::stringstream buffer;
    buffer << t.rdbuf();
    t.close();
    return buffer.str();
}

std::vector<char> TeaPacket::Files::ReadBinaryFile(const char* path){
    std::ifstream fs(TeaPacket::Files::GetFilePath(path), std::ios::in | std::ios::binary);
    std::vector<char> data((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    return data;
}