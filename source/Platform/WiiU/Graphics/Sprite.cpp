#ifdef TP_WIIU
#include "TeaPacket/Graphics/Sprite.hpp"
#include "Windows/Graphics/PlatformTexture.hpp"

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


const float spritePositionDataBase[24] = {
    -1.0f, -1.0f,  // Bottom left
     1.0f, -1.0f,  // Bottom Right
     1.0f,  1.0f,  // Top Right
    -1.0f, -1.0f,  // Bottom left
     1.0f,  1.0f,  // Top Right
    -1.0f,  1.0f,  // Top Left
};

const float spriteUVDataBase[12] = {
    0.0f, 1.0f,    // Bottom left
    1.0f, 1.0f,    // Bottom Right
    1.0f, 0.0f,    // Top Right
    0.0f, 1.0f,    // Bottom left
    1.0f, 0.0f,    // Top Right
    0.0f, 0.0f,    // Top Left
};

TeaPacket::Graphics::Shader* TeaPacket::Graphics::Sprite::spriteShader = nullptr;

GX2RBuffer positionBuffer = {};
GX2RBuffer uvBuffer = {};

#define ONEFLIPPED  0x00, 0x00, 0xF8, 0x03
#define SCALEFLIPPED 0x00, 0x00, 0x00, 0x3F
#define ZEROFLIPPED 0x00, 0x00, 0x00, 0x00

char testMatrix[sizeof(float)*16] = {
    SCALEFLIPPED, ZEROFLIPPED, ZEROFLIPPED, ZEROFLIPPED,
    ZEROFLIPPED, SCALEFLIPPED, ZEROFLIPPED, ZEROFLIPPED,
    ZEROFLIPPED, ZEROFLIPPED, SCALEFLIPPED, ZEROFLIPPED,
    ZEROFLIPPED, ZEROFLIPPED, ZEROFLIPPED, ONEFLIPPED
};

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
}



void TeaPacket::Graphics::Sprite::Draw(){
    alignas(0x100) uint32_t matrixUniformBlock[16] = {
        _swapF32(0.5), _swapF32(0.0), _swapF32(0.0), _swapF32(0.0),
        _swapF32(0.0), _swapF32(0.5), _swapF32(0.0), _swapF32(0.0),
        _swapF32(0.0), _swapF32(0.0), _swapF32(0.5), _swapF32(0.0),
        _swapF32(0.0), _swapF32(0.0), _swapF32(0.0), _swapF32(1.0),
    };

    glm::mat4 glMatrix = glm::mat4(1.0f);
    #define SCALEOF 0.75f
    glMatrix = glm::scale(glMatrix, glm::vec3(SCALEOF,SCALEOF,SCALEOF));
    for(int i = 0; i < sizeof(matrixUniformBlock) / sizeof(matrixUniformBlock[0]); i++){
        matrixUniformBlock[i] = _swapF32(glm::value_ptr(glMatrix)[i]);
    }

    //memcpy(matrixUniformBlock, testMatrix, sizeof(testMatrix));
    GX2SetVertexUniformBlock(0, sizeof(matrixUniformBlock), (void*)matrixUniformBlock);
    GX2Invalidate((GX2InvalidateMode)(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK), matrixUniformBlock, sizeof(matrixUniformBlock));

    GX2DrawEx(GX2_PRIMITIVE_MODE_TRIANGLES, 6, 0, 1);
}   
#endif