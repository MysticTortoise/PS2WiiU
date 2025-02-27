#ifdef TP_WIIU
#include "TeaPacket/Graphics/Texture.hpp"
#include "TeaPacket/Math/EndianSwapper.hpp"

#include "wiiu/Graphics/PlatformTexture.hpp"

#include "TeaPacket/Files/Files.hpp"

#include "TeaPacket/Logging.hpp"

#include <gx2/texture.h>
#include <gx2/mem.h>
#include <cstring>
#include <coreinit/memdefaultheap.h>
#include "stb/stb_image.h"

TeaPacket::Graphics::Texture::Texture(const char* path){
    std::vector<char> pngData = TeaPacket::Files::ReadBinaryFile(path);
    uint8_t* pngLoaded = stbi_load_from_memory((unsigned char*)pngData.data(), pngData.size() * sizeof(pngData[0]), &width, &height, &channelCount, 4);
    GX2Texture* texture = new GX2Texture();

    texture->surface.width = width;
    texture->surface.height = height;
    texture->surface.depth = 1;
    texture->surface.mipLevels = 1;
    texture->surface.format = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
    texture->surface.aa = GX2_AA_MODE1X;
    texture->surface.use = GX2_SURFACE_USE_TEXTURE;
    texture->surface.dim = GX2_SURFACE_DIM_TEXTURE_2D;
    texture->surface.tileMode = GX2_TILE_MODE_LINEAR_ALIGNED;
    texture->surface.swizzle = 0;
    texture->viewFirstMip = 0;
    texture->viewNumMips = 1;
    texture->viewFirstSlice = 0;
    texture->viewNumSlices = 1;
    texture->compMap = 0x0010203;
    GX2CalcSurfaceSizeAndAlignment(&texture->surface);
    GX2InitTextureRegs(texture);
    texture->surface.image = MEMAllocFromDefaultHeapEx(texture->surface.imageSize, texture->surface.alignment);

    size_t widthSizeInBytes = (sizeof(char)*4*width);
    for(int y = 0; y < height; y++){
        size_t offset = y * texture->surface.pitch;
        uint32_t* firstPixel = (uint32_t*)texture->surface.image + offset;
        memcpy(firstPixel, (pngLoaded + widthSizeInBytes * y), widthSizeInBytes);
    }

    GX2Sampler* sampler = new GX2Sampler();
    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_POINT);

    platformTexture = new TeaPacket::Graphics::PlatformTexture();
    platformTexture->gx2Tex = texture;
    platformTexture->gx2Sampler = sampler;

    stbi_image_free(pngLoaded);
}

TeaPacket::Graphics::Texture::~Texture(){
    MEMFreeToDefaultHeap(platformTexture->gx2Tex->surface.image);
    delete platformTexture;
}

#endif