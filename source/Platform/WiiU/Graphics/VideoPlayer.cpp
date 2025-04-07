#ifdef TP_WIIU
#include "TeaPacket/Graphics/VideoPlayer.hpp"
#include "wiiu/Graphics/PlatformVideoPlayer.hpp"

#include "TeaPacket/Graphics/Texture.hpp"
#include "wiiu/Graphics/PlatformTexture.hpp"

#include "TeaPacket/Files/Files.hpp"
#include "TeaPacket/Files/FileStream.hpp"
#include "TeaPacket/Logging.hpp"
#include "TeaPacket/Time.hpp"

#include <wut.h>
#include <h264/decode.h>
#include <h264/stream.h>

#include <unordered_map>
#include <cstring>
#include <cstdlib>

static void frame_callback(H264DecodeOutput *output) { }

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


TeaPacket::Graphics::VideoPlayer::VideoPlayer(const std::string path, Texture* texture):
texture(texture)
{
    platformPlayer = new PlatformVideoPlayer();
    H264Error res;


    size_t memRequirement = 0x2200000 + 0x3ff + 0x480000;
    #ifndef VSCODE // SHUT UP VSCODE
    platformPlayer->decoderMemory = std::aligned_alloc(0x400, memRequirement);
    #endif

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


    PrintLine("VIDEO DONE SETUP");
    if(texture == nullptr){
        this->texture = new Texture(NULL, width, height, TEXTURE_FORMAT_NV12);
        textureOwnedBySelf = true;
    }

}

void TeaPacket::Graphics::VideoPlayer::UpdateFrame(){
    int32_t skipable;
    for(int i = 0; i < 16; i++){
        TeaPacket::PrintLine(platformPlayer->h264Data[i]);
    }
    PrintLine("DEC EXEC");
    H264Error res = H264DECCheckSkipableFrame(platformPlayer->h264Data, platformPlayer->h264DataSize, &skipable);
    if(res != 0){
        PrintLine("ERROR: Error checking skipable frame. | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }
    PrintLine("CHECKED SKIPPABLE FRAME");
    if(skipable){return;}

    res = H264DECSetBitstream(platformPlayer->decoderMemory, platformPlayer->h264Data, platformPlayer->h264DataSize, 0);
    if(res != 0){
        PrintLine("ERROR: Error setting bitstream | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }
    PrintLine("BITSTREAM SET");
    void* scratchpad = malloc(1024*9); // Just assigning a giant-ass block of memory until i ensure i can actually call this function without crashing
    res = H264DECExecute(platformPlayer->decoderMemory, scratchpad); //texture->platformTexture->gx2Tex->surface.image);
    if(res != 0){
        PrintLine("ERROR: Error decoding. | Error Code " + std::string(H264ErrorCodes.at(res)));
        return;
    }
    PrintLine("DONE READING");
}

bool TeaPacket::Graphics::VideoPlayer::Tick(){
    UpdateFrame();
    return true;
}

TeaPacket::Graphics::VideoPlayer::~VideoPlayer(){

    delete platformPlayer;

    if(textureOwnedBySelf) { delete texture; }
}
int TeaPacket::Graphics::VideoPlayer::Init(){

    return 1;
}
#endif