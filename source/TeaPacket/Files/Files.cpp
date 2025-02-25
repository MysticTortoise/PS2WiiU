#include "TeaPacket/Files/Files.hpp"

#include "TeaPacket/Logging.hpp"

#include <fstream>
#include <sstream>


std::string TeaPacket::Files::ReadTextFile(const char* path){
    std::ifstream t(GetFilePath(path), std::ios::in);
    std::stringstream buffer;
    buffer << t.rdbuf();
    t.close();
    return buffer.str();
}

const char* TeaPacket::Files::ReadBinaryFile(const char* path, size_t* size){
    std::ifstream t(GetFilePath(path), std::ios::in | std::ios::binary);
    *size = t.tellg();
    t.seekg(std::ios::end);
    *size = (size_t)t.tellg() - *size;
    t.seekg(std::ios::beg);
    char* buffer = new char[*size];
    t.read(buffer, *size);
    t.close();
    return buffer;
}