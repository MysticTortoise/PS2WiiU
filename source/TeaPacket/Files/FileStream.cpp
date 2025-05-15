#include "TeaPacket/Files/FileStream.hpp"

#include "TeaPacket/Files/Files.hpp"

#include <iterator>
#include <stdint.h>
#include <cstring>

TeaPacket::Files::FileStream::FileStream(std::string path){
    Open(path);
}

TeaPacket::Files::FileStream::FileStream(){
    ifstream = nullptr;
}

TeaPacket::Files::FileStream::~FileStream(){
    delete ifstream;
}

#include "TeaPacket/Logging.hpp"

void TeaPacket::Files::FileStream::Open(std::string path){
    if(ifstream != nullptr) { delete ifstream; }
    ifstream = new std::ifstream(TeaPacket::Files::GetFilePath(path.c_str()), std::ios::binary | std::ios::in);
    unsigned char val;
    ifstream->read((char*)&val, 1);
    ifstream->seekg(std::ios::beg);
}

std::vector<char> TeaPacket::Files::FileStream::Read(size_t count, bool* endOfField){
    std::vector<char> buffer(count);
    ReadToBuff(count, &buffer[0], endOfField);
    return buffer;
}

void TeaPacket::Files::FileStream::ReadToBuff(size_t count, char* buffer, bool* endOfField){
    ifstream->read(buffer,count);

    if(endOfField != nullptr) { *endOfField = ifstream->eof(); }
    if(ifstream->eof()){
        ifstream->clear();
    }
    if(ifstream->bad()){
        PrintLine("READ FAILED");
        PrintLine(strerror(errno));
    }
}

void TeaPacket::Files::FileStream::Seek(std::streampos address){
    ifstream->seekg(address);
}
void TeaPacket::Files::FileStream::Seek(std::streamoff offset, std::ios_base::seekdir way){
    ifstream->seekg(offset, way);
}
void TeaPacket::Files::FileStream::Skip(std::streamoff offset){
    Seek(offset, std::ios_base::cur);
}

size_t TeaPacket::Files::FileStream::CurrentPosition(){
    return ifstream->tellg();
}

int16_t TeaPacket::Files::FileStream::ReadSInt16BigEndian(){
    int16_t v = ReadVal<int16_t>();
    if(is_big_endian()){
        return v;
    } else {
        return _swapS16(v);
    }
}
uint16_t TeaPacket::Files::FileStream::ReadUInt16BigEndian(){
    uint16_t v = ReadVal<uint16_t>();
    if(is_big_endian()){
        return v;
    } else {
        return _swapU16(v);
    }
}
int32_t TeaPacket::Files::FileStream::ReadSInt24BigEndian(){
    char buff[4];
    ReadToBuff(3, &buff[1]);
    uint32_t v = 0;
    memcpy(&v,buff,4);
    if(is_big_endian()){
        return v;
    } else {
        return _swapS32(v);
    }
}
uint32_t TeaPacket::Files::FileStream::ReadUInt24BigEndian(){
    char buff[4];
    ReadToBuff(3, &buff[1]);
    uint32_t v = 0;
    memcpy(&v,buff,4);
    if(is_big_endian()){
        return v;
    } else {
        return _swapU32(v);
    }
}
int32_t TeaPacket::Files::FileStream::ReadSInt32BigEndian(){
    int32_t v = ReadVal<int32_t>();
    if(is_big_endian()){
        return v;
    } else {
        return _swapS32(v);
    }
}
uint32_t TeaPacket::Files::FileStream::ReadUInt32BigEndian(){
    uint32_t v = ReadVal<uint32_t>();
    if(is_big_endian()){
        return v;
    } else {
        return _swapU32(v);
    }
}
int64_t TeaPacket::Files::FileStream::ReadSInt64BigEndian(){
    int64_t v = ReadVal<int64_t>();
    if(is_big_endian()){
        return v;
    } else {
        return _swapS64(v);
    }
}
uint64_t TeaPacket::Files::FileStream::ReadUInt64BigEndian(){
    uint64_t v = ReadVal<uint64_t>();
    if(is_big_endian()){
        return v;
    } else {
        return _swapU64(v);
    }
}

int16_t TeaPacket::Files::FileStream::ReadSInt16LittleEndian(){
    int16_t v = ReadVal<int16_t>();
    if(!is_big_endian()){
        return v;
    } else {
        return _swapS16(v);
    }
}
uint16_t TeaPacket::Files::FileStream::ReadUInt16LittleEndian(){
    uint16_t v = ReadVal<uint16_t>();
    if(!is_big_endian()){
        return v;
    } else {
        return _swapU16(v);
    }
}
int32_t TeaPacket::Files::FileStream::ReadSInt24LittleEndian(){
    char buff[4];
    ReadToBuff(3, &buff[1]);
    uint32_t v = 0;
    memcpy(&v,buff,4);
    if(!is_big_endian()){
        return v;
    } else {
        return _swapS32(v);
    }
}
uint32_t TeaPacket::Files::FileStream::ReadUInt24LittleEndian(){
    char buff[4];
    ReadToBuff(3, &buff[1]);
    uint32_t v = 0;
    memcpy(&v,buff,4);
    if(!is_big_endian()){
        return v;
    } else {
        return _swapU32(v);
    }
}
int32_t TeaPacket::Files::FileStream::ReadSInt32LittleEndian(){
    int32_t v = ReadVal<int32_t>();
    if(!is_big_endian()){
        return v;
    } else {
        return _swapS32(v);
    }
}
uint32_t TeaPacket::Files::FileStream::ReadUInt32LittleEndian(){
    uint32_t v = ReadVal<uint32_t>();
    if(!is_big_endian()){
        return v;
    } else {
        return _swapU32(v);
    }
}
int64_t TeaPacket::Files::FileStream::ReadSInt64LittleEndian(){
    int64_t v = ReadVal<int64_t>();
    if(!is_big_endian()){
        return v;
    } else {
        return _swapS64(v);
    }
}
uint64_t TeaPacket::Files::FileStream::ReadUInt64LittleEndian(){
    uint64_t v = ReadVal<uint64_t>();
    if(!is_big_endian()){
        return v;
    } else {
        return _swapU64(v);
    }
}