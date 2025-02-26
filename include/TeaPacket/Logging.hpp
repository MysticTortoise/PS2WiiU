#pragma once

#include <string>
#ifndef TP_DEBUG
#define Print(V)
#endif

namespace TeaPacket{
    void PrintString(std::string val);

    template<typename T>
    inline void Print(T val){
        PrintString(std::to_string(val));
    }

    inline void Print(std::string val){
        PrintString(val);
    }
    
    inline void Print(char* val){
        PrintString(std::string(val));
    }
    inline void Print(const char* val){
        PrintString(std::string(val));
    }

    int LogInit();
    void LogDeInit();
}

