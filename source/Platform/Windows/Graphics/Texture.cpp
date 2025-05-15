#ifdef TP_WIN
#include "TeaPacket/Graphics/Texture.hpp"
#include "Windows/Graphics/PlatformTexture.hpp"

#include "TeaPacket/Logging.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"

#include "string.h"

using namespace TeaPacket::Graphics;

namespace {
    struct GLFormat {
        GLint channelType;
        GLenum bitDepth;
    };

    struct GLFilter {
        GLint minFilter;
        GLint magFilter;
    };


    // Convert TeaPacket TextureFormat enum into a GLFormat struct.
    static GLFormat GetGLFormatFromTPFormat(TextureFormat format) {
        switch (format) {
        case TEXTURE_FORMAT_RGBA8:
        default:
            return {
                GL_RGBA,
                GL_UNSIGNED_BYTE
            };
        }
        return {};
    }
    // Conver TeaPacket TextureFilterType enum into a GLFilter struct.
    static GLFilter GetGLFilterFromTPFilter(TextureFilterType filter) {
        switch (filter) {
        case TEXTURE_FILTER_LINEAR:
            return {
                GL_LINEAR_MIPMAP_LINEAR,
                GL_LINEAR
            };
        case TEXTURE_FILTER_POINT:
            return {
                GL_NEAREST_MIPMAP_NEAREST,
                GL_NEAREST
            };
        }
        return {};
    }
}

TeaPacket::Graphics::Texture::Texture(const TextureParameters& parameters) :
    parameters(parameters),
    platformTexture(new PlatformTexture())
{
    void* data = parameters.unsafeParameters.overrideData == nullptr ? parameters.data : parameters.unsafeParameters.overrideData;
    // Generate Texture
    unsigned int handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Set Filter Params
    GLFilter filter = GetGLFilterFromTPFilter(parameters.filterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter.magFilter);
    // TODO: Format
    GLFormat glFormat = GetGLFormatFromTPFormat(parameters.format);
    glTexImage2D(GL_TEXTURE_2D, 0, glFormat.channelType, parameters.width, parameters.height, 0, glFormat.channelType, glFormat.bitDepth, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // Delete no longer necessary data
    // Setup platformTexture
    platformTexture->handle = handle;
}

TeaPacket::Graphics::Texture::~Texture() {
    glDeleteTextures(1, &platformTexture->handle);

    delete platformTexture;
}

bool TeaPacket::Graphics::Texture::UpdateContents(unsigned char* data){
    glBindTexture(GL_TEXTURE_2D, platformTexture->handle);
    GLFormat glFormat = GetGLFormatFromTPFormat(parameters.format);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, parameters.width, parameters.height, glFormat.channelType, glFormat.bitDepth, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

#endif