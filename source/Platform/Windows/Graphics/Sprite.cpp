#ifdef TP_WIN
#include "TeaPacket/Graphics/Sprite.hpp"
#include "Windows/Graphics/PlatformTexture.hpp"

#include "TeaPacket/Video.hpp"

#include "TeaPacket/Graphics/Shader.hpp"
#include "Windows/Graphics/PlatformShader.hpp"
#include "TeaPacket/Math/Vector2.hpp"
#include "TeaPacket/Math/Vector4.hpp"


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "TeaPacket/Logging.hpp"

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
unsigned int spriteObjectUniformBlock;
unsigned int spriteStaticUniformBlock;

glm::mat4 cameraMatrix(1.0f);

TeaPacket::Graphics::Shader* TeaPacket::Graphics::Sprite::spriteShader = nullptr;

int TeaPacket::Graphics::Sprite::Init(){
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

    glGenBuffers(1, &spriteObjectUniformBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, spriteObjectUniformBlock);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) + sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, spriteObjectUniformBlock);

    glGenBuffers(1, &spriteStaticUniformBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, spriteStaticUniformBlock);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, 1, spriteStaticUniformBlock);

    //glDepthMask(GL_FALSE);

    Sprite::spriteShader = new Shader("shaders/sprite.vert", "shaders/sprite.frag");

    return 1;
}

void TeaPacket::Graphics::Sprite::DeInit(){
    glDeleteVertexArrays(1, &spriteVAO);
    glDeleteBuffers(1, &spriteVBO);

    delete Sprite::spriteShader;
}


void TeaPacket::Graphics::Sprite::BeginRenderFromCamera(Camera* camera){
    cameraMatrix = glm::mat4(1.0f);
    cameraMatrix = glm::scale(cameraMatrix, glm::vec3(2.0f/renderScale.x, 2.0f/renderScale.y, 0));
    cameraMatrix = glm::rotate(cameraMatrix, glm::radians(camera->angle), glm::vec3(0,0,1));
    cameraMatrix = glm::translate(cameraMatrix, glm::vec3(renderScale.x * -0.5f, renderScale.y * -0.5f, 0));
    cameraMatrix = glm::translate(cameraMatrix, glm::vec3(-camera->position.x/2,-camera->position.y/2,0));
    cameraMatrix = glm::scale(cameraMatrix, glm::vec3(1/camera->scale.x,1/camera->scale.y,0));

    glClearColor(camera->bgColor.x, camera->bgColor.y, camera->bgColor.z, camera->bgColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void TeaPacket::Graphics::Sprite::Draw(){
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

    glBindBuffer(GL_UNIFORM_BUFFER, spriteObjectUniformBlock);
    glBufferSubData(GL_UNIFORM_BUFFER, 0,  sizeof(glm::mat4), glm::value_ptr(objectMat));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::vec4), &color);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glBindBuffer(GL_UNIFORM_BUFFER, spriteStaticUniformBlock);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(cameraMatrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindVertexArray(spriteVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
#endif