#ifdef TP_WIN
#include "TeaPacket/Logging.hpp"

#include <iostream>
#include <fstream>

static std::ofstream dump("log.txt");

void TeaPacket::PrintString(std::string val) {
    std::cout << val;
    dump << val;
}

int TeaPacket::LogInit()  {return 1;}
void TeaPacket::LogDeInit(){}

#endif