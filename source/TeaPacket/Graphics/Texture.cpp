#include "TeaPacket/Graphics/Texture.hpp"

#include "TeaPacket/Files/Files.hpp"

using TeaPacket::Graphics::Texture;

Texture* TeaPacket::Graphics::Texture::LoadFromFile(const char* path, TextureFilterType filterType){
    std::vector<char> data = TeaPacket::Files::ReadBinaryFile(path);
    Texture* tex = new Texture((unsigned char*)data.data(), data.size() * sizeof(data[0]), filterType);
    return tex;
}
