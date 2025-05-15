#ifdef TP_WIIU
#include "TeaPacket/Graphics/Texture.hpp"
#include "TeaPacket/Math/EndianSwapper.hpp"

#include "wiiu/Graphics/PlatformTexture.hpp"

#include "TeaPacket/Files/Files.hpp"

#include "TeaPacket/Logging.hpp"

#include <cstring>
#include <unordered_map>

#include <gx2/texture.h>
#include <gx2/mem.h>
#include <gx2/utils.h>
#include <coreinit/memdefaultheap.h>
#include "stb/stb_image.h"

using namespace TeaPacket::Graphics;

const std::unordered_map<TextureFormat, GX2SurfaceFormat> TeaPacket::Graphics::TPFormatToGXFormat = {
    {TEXTURE_FORMAT_RGBA8,  GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8},
    {TEXTURE_FORMAT_R8,     GX2_SURFACE_FORMAT_UNORM_R8},
    {TEXTURE_FORMAT_RG8,    GX2_SURFACE_FORMAT_UNORM_R8_G8}
};

const std::unordered_map<TextureFilterType, GX2TexXYFilterMode> TeaPacket::Graphics::TPFilterToGXFilter = {
    {TEXTURE_FILTER_LINEAR, GX2_TEX_XY_FILTER_MODE_LINEAR},
    {TEXTURE_FILTER_POINT, GX2_TEX_XY_FILTER_MODE_POINT}
};


TeaPacket::Graphics::Texture::Texture(const TextureParameters& parameters) :
    parameters(parameters),
    platformTexture(new PlatformTexture())
{
    GX2Texture* texture = new GX2Texture();

    texture->surface.width = parameters.width;
    texture->surface.height = parameters.height;
    texture->surface.depth = 1;
    texture->surface.mipLevels = 1;
    texture->surface.format = TPFormatToGXFormat.at(parameters.format);
    texture->surface.aa = GX2_AA_MODE1X;
    texture->surface.use = GX2_SURFACE_USE_TEXTURE;
    texture->surface.dim = GX2_SURFACE_DIM_TEXTURE_2D;
    texture->surface.tileMode = GX2_TILE_MODE_LINEAR_ALIGNED;
    texture->surface.swizzle = 0;
    texture->viewFirstMip = 0;
    texture->viewNumMips = 1;
    texture->viewFirstSlice = 0;
    texture->viewNumSlices = 1;
    texture->compMap = GX2_COMP_MAP(parameters.swizzleMap[0], parameters.swizzleMap[1], parameters.swizzleMap[2], parameters.swizzleMap[3]);
    GX2CalcSurfaceSizeAndAlignment(&texture->surface);
    GX2InitTextureRegs(texture);
    if(parameters.unsafeParameters.overrideData == nullptr){
        texture->surface.image = MEMAllocFromDefaultHeapEx(texture->surface.imageSize, texture->surface.alignment);
        size_t widthSizeInBytes = (sizeof(char) * 4 * parameters.width);
        for (unsigned int y = 0; y < parameters.height; y++) {
            size_t offset = y * texture->surface.pitch;
            uint32_t* firstPixel = (uint32_t*)texture->surface.image + offset;
            memcpy(firstPixel, ((unsigned char*)(parameters.data) + widthSizeInBytes * y), widthSizeInBytes);
        }
    } else {
        texture->surface.image = parameters.unsafeParameters.overrideData;
    }
    
    GX2Sampler* sampler = new GX2Sampler();
    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, TPFilterToGXFilter.at(parameters.filterType));

    platformTexture->gx2Tex = texture;
    platformTexture->gx2Sampler = sampler;
}

TeaPacket::Graphics::Texture::~Texture() {
    MEMFreeToDefaultHeap(platformTexture->gx2Tex->surface.image);
    delete platformTexture;
}

bool TeaPacket::Graphics::Texture::UpdateContents(unsigned char* data){
    size_t widthSizeInBytes = (sizeof(char) * 4 * parameters.width);
    for (unsigned int y = 0; y < parameters.height; y++) {
        size_t offset = y * platformTexture->gx2Tex->surface.pitch;
        uint32_t* firstPixel = (uint32_t*)platformTexture->gx2Tex->surface.image + offset;
        memcpy(firstPixel, (data + widthSizeInBytes * y), widthSizeInBytes);
    }
    return true;
}

#endif