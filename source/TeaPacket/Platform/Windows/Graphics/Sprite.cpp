#ifdef TP_WIN
#include "TeaPacket/Graphics/Sprite.hpp"
#include "TeaPacket/Platform/Windows/Graphics/PlatformTextureWin.hpp"

#include "TeaPacket/Video.hpp"

#include "TeaPacket/Graphics/Shader.hpp"
#include "TeaPacket/Platform/Windows/Graphics/PlatformShaderWin.hpp"
#include "TeaPacket/Math/Vector2.hpp"
#include "TeaPacket/Math/Vector4.hpp"


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "TeaPacket/DebugMacros.hpp"

const float spriteVertexDataBase[24] = {
    -1.0f, -1.0f, 0.0f, 1.0f, // Bottom left
     1.0f, -1.0f, 1.0f, 1.0f, // Bottom Right
     1.0f,  1.0f, 1.0f, 0.0f, // Top Right
     -1.0f, -1.0f, 0.0f, 1.0f, // Bottom left
     1.0f,  1.0f, 1.0f, 0.0f, // Top Right
    -1.0f,  1.0f, 0.0f, 0.0f, // Top Left
};

unsigned int spriteVBO;
unsigned int spriteVAO;
unsigned int spritePosUniformBlock;
unsigned int spriteColUniformBlock;

float renderWidthScale; // render width in units (aka pixels)
float renderHeightScale;

TeaPacket::Graphics::Shader* TeaPacket::Graphics::Sprite::spriteShader = nullptr;

void TeaPacket::Graphics::Sprite::SpriteRendererInit(){
    glGenVertexArrays(1, &spriteVAO);
    glGenBuffers(1, &spriteVBO);

    glBindVertexArray(spriteVAO);

    glBindBuffer(GL_ARRAY_BUFFER, spriteVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertexDataBase), spriteVertexDataBase, GL_STATIC_DRAW);
    // Pos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // UV
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &spritePosUniformBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, spritePosUniformBlock);
    glBufferData(GL_UNIFORM_BUFFER, 32, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, spritePosUniformBlock);

    glGenBuffers(1, &spriteColUniformBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, spriteColUniformBlock);
    glBufferData(GL_UNIFORM_BUFFER, 16, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, 1, spriteColUniformBlock);

    Sprite::spriteShader = new Shader("shaders/sprite.vert", "shaders/sprite.frag");

    renderWidthScale = TeaPacket::resolutionWidth;
    renderHeightScale = TeaPacket::resolutionHeight;
}

void TeaPacket::Graphics::Sprite::SpriteRendererDeInit(){
    glDeleteVertexArrays(1, &spriteVAO);
    glDeleteBuffers(1, &spriteVBO);

    delete Sprite::spriteShader;
}

void TeaPacket::Graphics::Sprite::Draw(){
    glBindTexture(GL_TEXTURE_2D, texture->platformTexture->handle);
    glUseProgram(Sprite::spriteShader->platformShader->handle);

    glBindBuffer(GL_UNIFORM_BUFFER, spritePosUniformBlock);

    Math::Vector2 scaledPos = Math::Vector2(
        2*(position.x / renderWidthScale) - 1, 
        2*(position.y / renderHeightScale) - 1
    );
    Math::Vector2 scaledSize = Math::Vector2(
        (scale.x * (texture->width / renderWidthScale)), 
        (scale.y * (texture->height / renderHeightScale))
    );
    PRINT(scaledSize.x);

    glBufferSubData(GL_UNIFORM_BUFFER, 0,  8, &scaledPos);
    glBufferSubData(GL_UNIFORM_BUFFER, 8,  4, &angle);
    glBufferSubData(GL_UNIFORM_BUFFER, 16, 8, &scaledSize);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glBindBuffer(GL_UNIFORM_BUFFER, spriteColUniformBlock);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 16, &color);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindVertexArray(spriteVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
#endif