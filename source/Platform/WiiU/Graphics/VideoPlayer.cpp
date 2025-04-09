#ifdef TP_WIIU
#include "TeaPacket/Graphics/VideoPlayer.hpp"
#include "wiiu/Graphics/PlatformVideoPlayer.hpp"

#include "TeaPacket/Graphics/Texture.hpp"
#include "wiiu/Graphics/PlatformTexture.hpp"
#include "TeaPacket/Graphics/Shader.hpp"

#include "TeaPacket/Files/Files.hpp"
#include "TeaPacket/Files/FileStream.hpp"
#include "TeaPacket/Logging.hpp"
#include "TeaPacket/Time.hpp"

#include <wut.h>
#include <coreinit/memdefaultheap.h>
#include <h264/decode.h>
#include <h264/stream.h>

#include <unordered_map>
#include <cstring>
#include <cstdlib>

#define H264_MEM_REQUIREMENT (0x2200000 + 0x3ff + 0x480000)
#define H264_MEM_ALIGNMENT 0x400
#define H264_FRAME_SIZE(w, h) (((w) * (h) * 3) >> 1)
#define H264_FRAME_PITCH(w) (((w) + 0xff) & ~0xff)
#define H264_FRAME_HEIGHT(h) (((h) + 0xf) & ~0xf)

static void frame_callback(H264DecodeOutput *output) {}

static const std::unordered_map<H264Error, const char*> H264ErrorCodes = {
    {H264_ERROR_OK, "H264 OK"},
    {H264_ERROR_INVALID_PPS, "INVALID PICTURE  PARAMETER SET"},
    {H264_ERROR_INVALID_SPS, "INVALID SEQUENCE PARAMETER SET"},
    {H264_ERROR_INVALID_SLICEHEADER, "INVALID SLICE HEADER"},
    {H264_ERROR_GENERIC, "GENERIC UNDETERMINABLE ERROR"},
    {H264_ERROR_INVALID_PARAMETER, "INVALID PARAMETERS PASSED"},
    {H264_ERROR_OUT_OF_MEMORY, "OUT OF MEMORY"},
    {H264_ERROR_INVALID_PROFILE, "INVALID H264 PROFILE - MUST BE: 66, 77, 100"}
};

TeaPacket::Graphics::Shader* TeaPacket::Graphics::VideoPlayer::customShader = nullptr;


TeaPacket::Graphics::VideoPlayer::VideoPlayer(const std::string path, Texture* texture):
texture(texture)
{
    platformPlayer = new PlatformVideoPlayer();
    H264Error res;


    size_t memRequirement = 0x2200000 + 0x3ff + 0x480000;
    platformPlayer->decoderMemory = malloc(memRequirement);

    res = H264DECCheckMemSegmentation(platformPlayer->decoderMemory, memRequirement);
    if(res != 0){
        PrintLine("ERROR: Invalid memory segmentation. | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }

    res = H264DECInitParam(memRequirement, platformPlayer->decoderMemory);
    if(res != 0){
        PrintLine("ERROR: Error initializing decoder. | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }

    res = H264DECSetParam_FPTR_OUTPUT(platformPlayer->decoderMemory, frame_callback);
    if(res != 0){
        PrintLine("ERROR: Error setting callback function. | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }

    res = H264DECSetParam_OUTPUT_PER_FRAME(platformPlayer->decoderMemory, 1);
    if(res != 0){
        PrintLine("ERROR: Error setting OUTPUT_PER_FRAME | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }

    res = H264DECOpen(platformPlayer->decoderMemory);
    if(res != 0){
        PrintLine("ERROR: Error opening decoder | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }

    res = H264DECBegin(platformPlayer->decoderMemory);
    if(res != 0){
        PrintLine("ERROR: Error preparing decoder | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }

    std::vector<char> charData = Files::ReadBinaryFile(path.c_str());
    platformPlayer->h264Data = (uint8_t*)malloc(charData.size() * sizeof(char));
    platformPlayer->h264DataSize = charData.size() * sizeof(char);
    memcpy(platformPlayer->h264Data, &charData[0], platformPlayer->h264DataSize);

    for(int i = 0; i < 16; i++){
        TeaPacket::PrintLine(platformPlayer->h264Data[i]);
    }
    int32_t width, height;

    res = H264DECGetImageSize(platformPlayer->h264Data, platformPlayer->h264DataSize, 0, &width, &height);
    if(res != 0){
        PrintLine("ERROR: Error reading image dimensions | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }

    PrintLine("MAKE BASE TEX");
    unsigned char* texSpace = (unsigned char*)MEMAllocFromDefaultHeapEx(H264_FRAME_SIZE(H264_FRAME_PITCH(width),height), H264_MEM_ALIGNMENT);
    PrintLine("GOOD ALLOC");
    this->texture = new Texture(NULL, width, height, TEXTURE_FORMAT_R8);
    PrintLine("MAKE UV TEX");
    platformPlayer->uvTexture = new Texture(NULL, width/2, height/2, TEXTURE_FORMAT_RGBA8);
    PrintLine("ALL TEXS MADE");

    MEMFreeToDefaultHeap(this->texture->platformTexture->gx2Tex->surface.image);
    MEMFreeToDefaultHeap(platformPlayer->uvTexture->platformTexture->gx2Tex->surface.image);

    this->texture->platformTexture->gx2Tex->surface.image = texSpace;
    platformPlayer->uvTexture->platformTexture->gx2Tex->surface.image = texSpace + this->texture->platformTexture->gx2Tex->surface.imageSize;

}

void TeaPacket::Graphics::VideoPlayer::UpdateFrame(){
    int32_t skipable;
    H264Error res = H264DECCheckSkipableFrame(platformPlayer->h264Data, platformPlayer->h264DataSize, &skipable);
    if(res != 0){
        PrintLine("ERROR: Error checking skipable frame. | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }
    if(skipable){return;}

    res = H264DECSetBitstream(platformPlayer->decoderMemory, platformPlayer->h264Data, platformPlayer->h264DataSize, 0);
    if(res != 0){
        PrintLine("ERROR: Error setting bitstream | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }
    res = H264DECExecute(platformPlayer->decoderMemory, texture->platformTexture->gx2Tex->surface.image);
    if(res == 0){
        PrintLine("ERROR: Error decoding. | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }
}

bool TeaPacket::Graphics::VideoPlayer::Tick(){
    UpdateFrame();
    return true;
}

void TeaPacket::Graphics::VideoPlayer::PrepareToDraw(){
    customShader->Use();
    customShader->SetTexture(platformPlayer->uvTexture, 1);
}

TeaPacket::Graphics::VideoPlayer::~VideoPlayer(){

    delete platformPlayer->uvTexture;
    delete platformPlayer;
    delete texture;
}
int TeaPacket::Graphics::VideoPlayer::Init(){
    customShader = new Shader("shaders/sprite.vert", "shaders/nv12sprite.frag");
    return 1;
}
#endif