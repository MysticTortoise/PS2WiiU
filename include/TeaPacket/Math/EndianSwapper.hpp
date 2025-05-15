#pragma once

#include <stdint.h>
#include <algorithm>
#include <cstring>

// by mch, https://stackoverflow.com/questions/59346207/24-bit-to-32-bit-conversion-in-c
int32_t inline constexpr interpret24bitAsInt32(char* byteArray)
{     
    int32_t number =
        (((int32_t)byteArray[0]) << 16)
    |   (((int32_t)byteArray[1]) << 8)
    |   byteArray[2];
    if (number >= ((int32_t)1) << 23)
        return number - 16777216;
    return number;
}

uint16_t inline constexpr _swapU16(uint16_t v) {
    return (v>>8) | (v<<8);
}

int16_t inline constexpr _swapS16(int16_t v) {
    return (v>>8) | (v<<8);
}

uint32_t inline constexpr _swapU32(uint32_t v) {
    return ((v>>24)&0xff) | ((v<<8)&0xff0000) | ((v>>8)&0xff00) | ((v<<24)&0xff000000);
}

int32_t inline constexpr _swapS32(int32_t v) {
    return ((v>>24)&0xff) | ((v<<8)&0xff0000) | ((v>>8)&0xff00) | ((v<<24)&0xff000000);
}

uint64_t inline constexpr _swapU64(uint64_t v) {
    return _swapS32(v&0xFFFFFFFF) | _swapS32((v>>32)&0xFFFFFFFF);
}

int64_t inline constexpr _swapS64(int64_t v) {
    return _swapS32(v&0xFFFFFFFF) | _swapS32((v>>32)&0xFFFFFFFF);
}

uint32_t inline constexpr _swapF32(const float v)
{
    uint32_t r = 0;
    memcpy(&r,&v,sizeof(float));
    return _swapS32(r);
}

bool inline constexpr is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } val = {0x01020304};
    return val.c[0] == 1;
}