#ifdef TP_WIN
#include "TeaPacket/Graphics/Texture.hpp"
#include "Windows/Graphics/PlatformTexture.hpp"

#include "TeaPacket/Logging.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"

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

TeaPacket::Graphics::Texture::Texture(unsigned char* data, unsigned int width, unsigned int height, TextureFormat format, TextureFilterType filterType) :
    width(width),
    height(height),
    platformTexture(new PlatformTexture()),
    filterType(filterType),
    format(format)
{
    // Generate Texture
    unsigned int handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Set Filter Params
    GLFilter filter = GetGLFilterFromTPFilter(filterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter.magFilter);
    // Load IMG
    int channelCount;
    // TODO: Format
    format = TEXTURE_FORMAT_RGBA8;
    GLFormat glFormat = GetGLFormatFromTPFormat(format);
    // Send data
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, glFormat.channelType, width, height, 0, glFormat.channelType, glFormat.bitDepth, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        TeaPacket::Print("Failed to load texture.");
        Print(stbi_failure_reason());
    }
    // Delete no longer necessary data
    // Setup platformTexture
    platformTexture->handle = handle;
}

TeaPacket::Graphics::Texture::~Texture() {
    glDeleteTextures(1, &platformTexture->handle);

    delete platformTexture;
}
#endif