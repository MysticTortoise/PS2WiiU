#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace TeaPacket::Files{

    class FileStream{
        public:
        FileStream(std::string path);
        FileStream();
        ~FileStream();

        void Open(std::string path);
        std::vector<char> Read(size_t count, bool* endOfField = nullptr);
        void Seek(std::streampos address);
        void Seek(std::streamoff offset, std::ios_base::seekdir way);
        size_t CurrentPosition();

        private:
        std::ifstream* ifstream = nullptr;
    };
}