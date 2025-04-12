#include "TeaPacket/Graphics/Texture.hpp"

#include "TeaPacket/Logging.hpp"
#include "stb/stb_image.h"
#include "TeaPacket/Files/Files.hpp"

using TeaPacket::Graphics::Texture;

Texture* TeaPacket::Graphics::Texture::LoadFromFile(const char* path, const TextureParameters& parameters){
    std::vector<char> data = TeaPacket::Files::ReadBinaryFile(path);

    int width, height, channelCount;

    unsigned char* imageData = stbi_load_from_memory((unsigned char*)data.data(), data.size(), &width, &height, &channelCount, STBI_rgb_alpha);

    TextureParameters params = TextureParameters(parameters);
    params.width = width;
    params.height = height;
    params.format = TEXTURE_FORMAT_RGBA8;
    params.data = imageData;

    Texture* tex = new Texture(params);
    tex->parameters.width = width;
    tex->parameters.height = height;

    // Delete no longer necessary data
    stbi_image_free(imageData);
    return tex;
}
