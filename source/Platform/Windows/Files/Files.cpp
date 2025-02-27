#ifdef TP_WIN
#include "TeaPacket/Files/Files.hpp"
#include <filesystem>
#include <string>

int TeaPacket::Files::Init(){
    std::filesystem::current_path(std::filesystem::current_path().append("assets"));
    return 1;
}

void TeaPacket::Files::DeInit(){}

std::string TeaPacket::Files::GetFilePath(const char* path){
    return path;
}

#endif