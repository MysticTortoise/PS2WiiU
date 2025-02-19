#ifdef TP_WIN
#include "TeaPacket/Graphics/Sprite.hpp"
#include "TeaPacket/Platform/Windows/Graphics/PlatformTextureWin.hpp"

#include "TeaPacket/Graphics/Shader.hpp"
#include "TeaPacket/Platform/Windows/Graphics/PlatformShaderWin.hpp"


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "TeaPacket/DebugMacros.hpp"

const float spriteVertexDataBase[16] = {
    -1.0f, -1.0f, 0.0f, 1.0f,
     1.0f, -1.0f, 1.0f, 1.0f,
     1.0f,  1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 0.0f,
};

unsigned int spriteVBO;
unsigned int spriteVAO;
unsigned int spritePosUniformBlock;

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
    glBufferData(GL_UNIFORM_BUFFER, 20, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BLOCK, 0, spritePosUniformBlock);

    Sprite::spriteShader = new Shader("shaders/sprite.vert", "shaders/sprite.frag");
}

void TeaPacket::Graphics::Sprite::SpriteRendererDeInit(){
    glDeleteVertexArrays(1, &spriteVAO);
    glDeleteBuffers(1, &spriteVBO);

    delete Sprite::spriteShader;
}

void TeaPacket::Graphics::Sprite::Draw(){
    glBindTexture(GL_TEXTURE_2D, texture->platformTexture->handle);
    glUseProgram(Sprite::spriteShader->platformShader->handle);
    glBindVertexArray(spriteVAO);

    glBindBuffer(GL_UNIFORM_BUFFER, spritePosUniformBlock);
    glBufferSubData(GL_UNIFORM_BUFFER,)

    glDrawArrays(GL_TRIANGLES, 0, 4);
    glBindVertexArray(0);
}
#endif