#pragma once

#include <string>
#ifndef TP_DEBUG
#define Print(V)
#endif

namespace TeaPacket{
    template<typename T>
    void Print(T val);

    void Print(std::string val);
    void Print(char* val);
    void Print(const char* val);

    int LogInit();
    void LogDeInit();
}