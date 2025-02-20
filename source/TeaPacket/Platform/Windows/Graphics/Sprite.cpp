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
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
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

glm::mat4 cameraMatrix(1.0f);

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
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, NULL, GL_STATIC_DRAW);
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


void TeaPacket::Graphics::Sprite::BeginRenderFromCamera(Camera* camera){
    cameraMatrix = glm::mat4(1.0f);
    cameraMatrix = glm::scale(cameraMatrix, glm::vec3(2.0f/renderWidthScale, 2.0f/renderHeightScale, 0));
    cameraMatrix = glm::rotate(cameraMatrix, glm::radians(camera->angle), glm::vec3(0,0,1));
    cameraMatrix = glm::translate(cameraMatrix, glm::vec3(renderWidthScale * -0.5f, renderHeightScale * -0.5f, 0));
    cameraMatrix = glm::translate(cameraMatrix, glm::vec3(-camera->position.x/2,-camera->position.y/2,0));
    cameraMatrix = glm::scale(cameraMatrix, glm::vec3(1/camera->scale.x,1/camera->scale.y,0));

    camera->position.x++;
}

void TeaPacket::Graphics::Sprite::Draw(){
    position.x = 1280/2;
    position.y = 720/2;
    angle = 0;
    anchor.y = 0;

    glBindTexture(GL_TEXTURE_2D, texture->platformTexture->handle);
    glUseProgram(Sprite::spriteShader->platformShader->handle);

    glm::mat4 objectMat(1.0f);
    glm::vec3 anchorOffset(anchor.x, -anchor.y, 0);
    glm::vec3 pixelSize(texture->width, texture->height, 0);

    objectMat = glm::translate(objectMat, ((glm::vec3)position) + anchorOffset * pixelSize);
    objectMat = glm::scale(objectMat,pixelSize);
    objectMat = glm::translate(objectMat, -anchorOffset);
    objectMat = glm::rotate(objectMat, glm::radians(angle), glm::vec3(0,0,1));
    objectMat = glm::scale(objectMat, glm::vec3(scale.x*0.5f,scale.y*0.5f,0));
    objectMat = glm::translate(objectMat, anchorOffset);

    glBindBuffer(GL_UNIFORM_BUFFER, spritePosUniformBlock);
    glBufferSubData(GL_UNIFORM_BUFFER, 0,  sizeof(glm::mat4), glm::value_ptr(objectMat));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4),  sizeof(glm::mat4), glm::value_ptr(cameraMatrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glBindBuffer(GL_UNIFORM_BUFFER, spriteColUniformBlock);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 16, &color);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindVertexArray(spriteVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
#endif