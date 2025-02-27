#ifdef TP_WIIU
#include "TeaPacket/Graphics/Sprite.hpp"
#include "wiiu/Graphics/PlatformTexture.hpp"

#include "TeaPacket/Video.hpp"

#include "TeaPacket/Graphics/Shader.hpp"
#include "WiiU/Graphics/PlatformShader.hpp"
#include "TeaPacket/Math/Vector2.hpp"
#include "TeaPacket/Math/Vector4.hpp"

#include <gx2/shaders.h>
#include <gx2/draw.h>
#include <gx2r/draw.h>

#include <gx2/registers.h>
#include <gx2/mem.h>
#include "TeaPacket/Math/EndianSwapper.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "TeaPacket/Logging.hpp"


const static float spritePositionDataBase[24] = {
    -1.0f, -1.0f,  // Bottom left
     1.0f, -1.0f,  // Bottom Right
     1.0f,  1.0f,  // Top Right
    -1.0f, -1.0f,  // Bottom left
     1.0f,  1.0f,  // Top Right
    -1.0f,  1.0f,  // Top Left
};

const static float spriteUVDataBase[12] = {
    0.0f, 1.0f,    // Bottom left
    1.0f, 1.0f,    // Bottom Right
    1.0f, 0.0f,    // Top Right
    0.0f, 1.0f,    // Bottom left
    1.0f, 0.0f,    // Top Right
    0.0f, 0.0f,    // Top Left
};

TeaPacket::Graphics::Shader* TeaPacket::Graphics::Sprite::spriteShader = nullptr;

static GX2RBuffer positionBuffer = {};
static GX2RBuffer uvBuffer = {};

alignas(0x100) uint32_t TeaPacket::Graphics::Sprite::staticUniformBlock[16] = {};

int TeaPacket::Graphics::Sprite::Init(){
    spriteShader = new Shader("shaders/sprite.vert", "shaders/sprite.frag");

    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);

    WHBGfxInitShaderAttribute(spriteShader->platformShader->whbGroup, "aPos", 0, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    WHBGfxInitShaderAttribute(spriteShader->platformShader->whbGroup, "aTexCoord", 1, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    WHBGfxInitFetchShader(spriteShader->platformShader->whbGroup);

    positionBuffer.flags = (GX2RResourceFlags)(GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ);
    positionBuffer.elemSize = 2 * sizeof(float);
    positionBuffer.elemCount = 6;
    GX2RCreateBuffer(&positionBuffer);
    void *posUploadBuffer = GX2RLockBufferEx(&positionBuffer, GX2R_RESOURCE_BIND_NONE);
    memcpy(posUploadBuffer, spritePositionDataBase, positionBuffer.elemSize * positionBuffer.elemCount);
    GX2RUnlockBufferEx(&positionBuffer, GX2R_RESOURCE_BIND_NONE);

    // Send Texture Coords
    uvBuffer.flags = (GX2RResourceFlags)(GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ);
    uvBuffer.elemSize = 2 * sizeof(float);
    uvBuffer.elemCount = 6;
    GX2RCreateBuffer(&uvBuffer);
    void *coordsUploadBuffer = GX2RLockBufferEx(&uvBuffer, GX2R_RESOURCE_BIND_NONE);
    memcpy(coordsUploadBuffer, spriteUVDataBase, uvBuffer.elemSize * uvBuffer.elemCount);
    GX2RUnlockBufferEx(&uvBuffer, GX2R_RESOURCE_BIND_NONE);

    return 1;
}

void TeaPacket::Graphics::Sprite::DeInit(){
    
}


void TeaPacket::Graphics::Sprite::BeginRenderFromCamera(Camera* camera){
    WHBGfxClearColor(camera->bgColor.x, camera->bgColor.y, camera->bgColor.z, camera->bgColor.w);

    GX2SetFetchShader(&(spriteShader->platformShader->whbGroup->fetchShader));
    GX2SetVertexShader(spriteShader->platformShader->whbGroup->vertexShader);
    GX2SetPixelShader(spriteShader->platformShader->whbGroup->pixelShader);
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);

    GX2RSetAttributeBuffer(&positionBuffer, 0, positionBuffer.elemSize, 0);
    GX2RSetAttributeBuffer(&uvBuffer, 1, uvBuffer.elemSize, 0);

    glm::mat4 cameraMatrix(1.0f);
    cameraMatrix = glm::scale(cameraMatrix, glm::vec3(2.0f/renderScale.x, 2.0f/renderScale.y, 0));
    cameraMatrix = glm::rotate(cameraMatrix, glm::radians(camera->angle), glm::vec3(0,0,1));
    cameraMatrix = glm::translate(cameraMatrix, glm::vec3(renderScale.x * -0.5f, renderScale.y * -0.5f, 0));
    cameraMatrix = glm::translate(cameraMatrix, glm::vec3(-camera->position.x/2,-camera->position.y/2,0));
    cameraMatrix = glm::scale(cameraMatrix, glm::vec3(1/camera->scale.x,1/camera->scale.y,0));
    for(size_t i = 0; i < 16; i++){
        staticUniformBlock[i] = _swapF32(glm::value_ptr(cameraMatrix)[i]);
    }
    GX2SetVertexUniformBlock(1, sizeof(staticUniformBlock), (void*)staticUniformBlock);
    GX2Invalidate((GX2InvalidateMode)(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK), staticUniformBlock, sizeof(staticUniformBlock));
}

void TeaPacket::Graphics::Sprite::Draw(){
    GX2SetFetchShader(&(spriteShader->platformShader->whbGroup->fetchShader));
    GX2SetVertexShader(spriteShader->platformShader->whbGroup->vertexShader);
    GX2SetPixelShader(spriteShader->platformShader->whbGroup->pixelShader);
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);

    glm::mat4 objectMat(1.0f);
    glm::vec3 anchorOffset(anchor.x, -anchor.y, 0); 
    glm::vec3 pixelSize(texture->width, texture->height, 0);

    objectMat = glm::translate(objectMat, ((glm::vec3)position) + anchorOffset * pixelSize);
    objectMat = glm::scale(objectMat,pixelSize);
    objectMat = glm::translate(objectMat, -anchorOffset);
    objectMat = glm::rotate(objectMat, glm::radians(angle), glm::vec3(0,0,1));
    objectMat = glm::scale(objectMat, glm::vec3(scale.x*0.5f,scale.y*0.5f,0));
    objectMat = glm::translate(objectMat, anchorOffset);

    for(size_t i = 0; i < 16; i++){
        objectUniformBlock[i] = _swapF32(glm::value_ptr(objectMat)[i]);
    }

    //memcpy(matrixUniformBlock, testMatrix, sizeof(testMatrix));
    GX2SetVertexUniformBlock(0, sizeof(objectUniformBlock), (void*)objectUniformBlock);
    GX2Invalidate((GX2InvalidateMode)(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK), objectUniformBlock, sizeof(objectUniformBlock));

    GX2SetPixelTexture(texture->platformTexture->gx2Tex, spriteShader->platformShader->whbGroup->pixelShader->samplerVars[0].location);
    GX2SetPixelSampler(texture->platformTexture->gx2Sampler, spriteShader->platformShader->whbGroup->pixelShader->samplerVars[0].location);

    GX2DrawEx(GX2_PRIMITIVE_MODE_TRIANGLES, 6, 0, 1);
}   
#endif