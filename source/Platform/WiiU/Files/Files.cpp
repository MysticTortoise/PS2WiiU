#ifdef TP_WIIU
#include "TeaPacket/Files/Files.hpp"
#include <filesystem>

#include <romfs-wiiu.h>

int TeaPacket::Files::Init(){
    romfsInit();
    return 1;
}

void TeaPacket::Files::DeInit(){
    romfsExit();
}

std::string TeaPacket::Files::GetFilePath(const char* path){
    std::string string = "romfs:/";
    string.append(path);
    return string;
}
#endif