#ifdef TP_WIN
#include "TeaPacket/Time.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

double TeaPacket::Timing::GetTimeDouble(){
    return glfwGetTime();
}
unsigned long long TeaPacket::Timing::GetTimeSeconds(){
    return (unsigned long long)glfwGetTime();
}
unsigned long long TeaPacket::Timing::GetTimeMilliseconds(){
    return (unsigned long long)(glfwGetTime()*1000ull);
}
unsigned long long TeaPacket::Timing::GetTimeMicroseconds(){
    return (unsigned long long)(glfwGetTime()*1000000ull);
}
unsigned long long TeaPacket::Timing::GetTimeNanoseconds(){
    return (unsigned long long)(glfwGetTime()*1000000000ull);
}
#endif