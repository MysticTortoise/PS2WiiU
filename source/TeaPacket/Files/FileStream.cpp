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
    TeaPacket::PrintLine(val);
    ifstream->seekg(std::ios::beg);
}

std::vector<char> TeaPacket::Files::FileStream::Read(size_t count, bool* endOfField){
    std::vector<char> buffer(count);
    ifstream->read(&buffer[0],count);
    TeaPacket::PrintLine("READ");
    TeaPacket::PrintLine((unsigned char)buffer[0]);
    TeaPacket::PrintLine((unsigned char)buffer[buffer.size()-1]);
    TeaPacket::PrintLine(buffer.size());
    //TeaPacket::PrintLine(CurrentPosition());

    if(endOfField != nullptr) { *endOfField = ifstream->eof(); }
    if(ifstream->eof()){
        ifstream->clear();
    }
    if(ifstream->bad()){
        PrintLine("READ FAILED");
        PrintLine(strerror(errno));
    }
    //PrintLine("READ DONE");
    return buffer;
}

void TeaPacket::Files::FileStream::Seek(std::streampos address){
    ifstream->seekg(address);
}
void TeaPacket::Files::FileStream::Seek(std::streamoff offset, std::ios_base::seekdir way){
    TeaPacket::PrintLine("SEEK TO:");
    TeaPacket::PrintLine(offset);
    TeaPacket::PrintLine("FROM:");
    TeaPacket::PrintLine(CurrentPosition());
    ifstream->seekg(offset, way);
}

size_t TeaPacket::Files::FileStream::CurrentPosition(){
    return ifstream->tellg();
}