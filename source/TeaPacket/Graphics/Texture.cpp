#include "TeaPacket/Graphics/Texture.hpp"

#include "TeaPacket/Logging.hpp"
#include "stb/stb_image.h"
#include "TeaPacket/Files/Files.hpp"

using TeaPacket::Graphics::Texture;

Texture* TeaPacket::Graphics::Texture::LoadFromFile(const char* path, TextureFilterType filterType){
    std::vector<char> data = TeaPacket::Files::ReadBinaryFile(path);

    int width, height, channelCount;

    unsigned char* imageData = stbi_load_from_memory((unsigned char*)data.data(), data.size(), &width, &height, &channelCount, STBI_rgb_alpha);

    Texture* tex = new Texture(imageData, width, height, TEXTURE_FORMAT_RGBA8, filterType);
    tex->width = width;
    tex->height = height;

    // Delete no longer necessary data
    stbi_image_free(imageData);
    return tex;
}
