#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include <array>

#include "TeaPacket/Math/EndianSwapper.hpp"
#include "TeaPacket/Logging.hpp"

namespace TeaPacket::Files {

    class FileStream {
    public:
        FileStream(std::string path);
        FileStream();
        ~FileStream();

        void Open(std::string path);
        std::vector<char> Read(size_t count, bool* endOfField = nullptr);
        void ReadToBuff(size_t count, char* buffer, bool* endOfField = nullptr);
        void Seek(std::streampos address);
        void Seek(std::streamoff offset, std::ios_base::seekdir way);
        void Skip(std::streamoff amount);
        size_t CurrentPosition();

        template<typename T>
        inline T ReadVal() {
            T val;
            std::vector<char> data = Read(sizeof(T));
            memcpy(&val, &data[0], sizeof(T));
            return val;
        };

        template<size_t size>
        inline std::array<char, size> Read() {
            std::array<char, size> arr;
            std::vector<char> vec = Read(size);
            std::move(vec.begin(), vec.end(), arr.begin());
            return arr;
        }

    private:
        std::ifstream* ifstream = nullptr;

    public:
        int16_t ReadSInt16BigEndian();
        uint16_t ReadUInt16BigEndian();
        int32_t ReadSInt24BigEndian();
        uint32_t ReadUInt24BigEndian();
        int32_t ReadSInt32BigEndian();
        uint32_t ReadUInt32BigEndian();
        int64_t ReadSInt64BigEndian();
        uint64_t ReadUInt64BigEndian();

        int16_t ReadSInt16LittleEndian();
        uint16_t ReadUInt16LittleEndian();
        int32_t ReadSInt24LittleEndian();
        uint32_t ReadUInt24LittleEndian();
        int32_t ReadSInt32LittleEndian();
        uint32_t ReadUInt32LittleEndian();
        int64_t ReadSInt64LittleEndian();
        uint64_t ReadUInt64LittleEndian();
    };
}