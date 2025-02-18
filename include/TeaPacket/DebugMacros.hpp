#pragma once
#ifdef TP_DEBUG

#ifdef TP_WIN
#include <iostream>

#define PRINT(MSG) std::cout << MSG << std::endl
#define ERROR(MSG) PRINT("ERROR: " << MSG << std::endl)

#endif // TP_WIN

#endif 