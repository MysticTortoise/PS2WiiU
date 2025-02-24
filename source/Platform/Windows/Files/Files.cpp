#include "TeaPacket/Files/Files.hpp"
#include <filesystem>

int TeaPacket::Files::Init(){
    std::filesystem::current_path(std::filesystem::current_path().append("assets"));
    return 1;
}