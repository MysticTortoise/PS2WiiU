#ifdef TP_WIN
#include "TeaPacket/Graphics/Texture.hpp"
#include "Windows/Graphics/PlatformTexture.hpp"

#include "TeaPacket/DebugMacros.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"

TeaPacket::Graphics::Texture::Texture(const char* path){
    unsigned int handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data = stbi_load(path, &width, &height, &channelCount, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
    } else {
        ERROR("Failed to load texture " << path);
    }
    stbi_image_free(data);

    platformTexture = new PlatformTexture();
    platformTexture->handle = handle;
}

TeaPacket::Graphics::Texture::~Texture(){
    glDeleteTextures(1, &platformTexture->handle);

    delete platformTexture;
}

#endif