#ifdef TP_WIN
#include "TeaPacket/Logging.hpp"

#include <iostream>

void TeaPacket::PrintString(std::string val) {
    std::cout << val;
}

int TeaPacket::LogInit()  {return 1;}
void TeaPacket::LogDeInit(){}

#endif