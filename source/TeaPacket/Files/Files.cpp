#include "TeaPacket/Files/Files.hpp"

#include "TeaPacket/DebugMacros.hpp"

#include <fstream>
#include <sstream>

std::string TeaPacket::Files::ReadTextFileString(const char* path){
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

const char* TeaPacket::Files::ReadTextFile(const char* path){
    std::string string = ReadTextFileString(path);
    const char* cstr = (const char*)malloc(sizeof(char) * string.size());
    memcpy((void*)cstr, string.c_str(), sizeof(char) * string.size());
    return cstr;
}