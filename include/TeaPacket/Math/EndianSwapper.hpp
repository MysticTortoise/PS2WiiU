#pragma once

#include <stdint.h>
#include <algorithm>

template <typename T, std::size_t S>
struct helper {};

template <typename T>
struct helper<T, 1> {
    using type = uint8_t;
};
template <typename T>
struct helper<T, 2> {
    using type = uint16_t;
};
template <typename T>
struct helper<T, 4> {
    using type = uint32_t;
};
template <typename T>
struct helper<T, 8> {
    using type = uint64_t;
};

template <typename T>
using int_type = typename helper<T, sizeof(T)>::type;

uint16_t inline _swapU16(uint16_t v) {
    return (v>>8) | (v<<8);
}

int16_t inline _swapS16(int16_t v) {
    return (v>>8) | (v<<8);
}

uint32_t inline _swapU32(uint32_t v) {
    return ((v>>24)&0xff) | ((v<<8)&0xff0000) | ((v>>8)&0xff00) | ((v<<24)&0xff000000);
}

int32_t inline _swapS32(int32_t v) {
    return ((v>>24)&0xff) | ((v<<8)&0xff0000) | ((v>>8)&0xff00) | ((v<<24)&0xff000000);
}

uint32_t inline _swapF32(const float v)
{
    return __builtin_bswap32(*(uint32_t*)&v);
}

float ReverseFloat( const float inFloat );

uint32_t FloatToUINTBitcas(const float v);