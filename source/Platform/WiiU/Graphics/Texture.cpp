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

using namespace TeaPacket::Graphics;

namespace {
    static GX2SurfaceFormat GetGXFormatFromTPFormat(TextureFormat format) {
        switch (format) {
        case TEXTURE_FORMAT_RGBA8:
            return GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
        case TEXTURE_FORMAT_R8:
            return GX2_SURFACE_FORMAT_UNORM_R8;
        case TEXTURE_FORMAT_RG8:
            return GX2_SURFACE_FORMAT_UNORM_R8_G8;
        }
        return GX2_SURFACE_FORMAT_INVALID;
    }

    static int GetChannelCountFromTPFormat(TextureFormat format) {
        switch (format) {
        case TEXTURE_FORMAT_RGBA8:
            return 4;
        case TEXTURE_FORMAT_R8:
            return 1;
        case TEXTURE_FORMAT_RG8:
            return 2;
        }
        return -1;
    }

    static GX2TexXYFilterMode GetGXFilterFromTPFormat(TextureFilterType filter) {
        switch (filter) {
        case TEXTURE_FILTER_POINT:
            return GX2_TEX_XY_FILTER_MODE_POINT;
        case TEXTURE_FILTER_LINEAR:
        default:
            return GX2_TEX_XY_FILTER_MODE_LINEAR;
        }
    }
}

TeaPacket::Graphics::Texture::Texture(unsigned char* data, unsigned int width, unsigned int height, TextureFormat format, TextureFilterType filterType) :
    width(width),
    height(height),
    platformTexture(new PlatformTexture()),
    filterType(filterType),
    format(format)
{
    PrintLine("MAKE GX2TEX");
    GX2Texture tex;
    GX2Texture* texture = &tex;
    PrintLine(texture == nullptr);
    PrintLine("A!!!");
    texture->surface.width = width;
    texture->surface.height = height;
    texture->surface.depth = 1;
    texture->surface.mipLevels = 1;
    texture->surface.format = GetGXFormatFromTPFormat(format); // TODO: Formats
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
    PrintLine("SETUP DONE");
    texture->surface.image = MEMAllocFromDefaultHeapEx(texture->surface.imageSize, texture->surface.alignment);

    if(texture->surface.image == nullptr){
        PrintLine("OOM! FUCK!!!");
    }
    

    if (!data) {
        data = (unsigned char*)malloc(GetMemSizeOfTextureFormat(format, width, height));
        memset(data, 0, GetMemSizeOfTextureFormat(format, width, height));
    }
    size_t widthSizeInBytes = (sizeof(char) * GetChannelCountFromTPFormat(format) * width);
    for (unsigned int y = 0; y < height; y++) {
        size_t offset = y * texture->surface.pitch;
        uint32_t* firstPixel = (uint32_t*)texture->surface.image + offset;
        memcpy(firstPixel, (data + widthSizeInBytes * y), widthSizeInBytes);
    }

    GX2Sampler* sampler = new GX2Sampler();
    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, GetGXFilterFromTPFormat(filterType));

    platformTexture->gx2Tex = texture;
    platformTexture->gx2Sampler = sampler;
}

TeaPacket::Graphics::Texture::~Texture() {
    MEMFreeToDefaultHeap(platformTexture->gx2Tex->surface.image);
    delete platformTexture;
}

bool TeaPacket::Graphics::Texture::UpdateContents(unsigned char* data){
    size_t widthSizeInBytes = (sizeof(char) * 4 * width);
    for (unsigned int y = 0; y < height; y++) {
        size_t offset = y * platformTexture->gx2Tex->surface.pitch;
        uint32_t* firstPixel = (uint32_t*)platformTexture->gx2Tex->surface.image + offset;
        memcpy(firstPixel, (data + widthSizeInBytes * y), widthSizeInBytes);
    }
    return true;
}

#endif