#include "TeaPacket/Logging.hpp"

template<typename T>
void TeaPacket::Print(T val){
    Print(std::to_string(val));
}

void TeaPacket::Print(char* val){
    Print(std::string(val));
}

void TeaPacket::Print(const char* val){
    Print(std::string(val));
}