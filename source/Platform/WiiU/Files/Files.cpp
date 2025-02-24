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