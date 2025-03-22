#include "TeaPacket/Graphics/VideoPlayer.hpp"

#include "TeaPacket/Files/Files.hpp"
#include "TeaPacket/Files/FileStream.hpp"
#include "TeaPacket/Logging.hpp"

#include <unordered_map>

int CustomFFmpegIOStreamRead(void* ptr, uint8_t* buf, int buf_size){
    TeaPacket::Files::FileStream* stream = (TeaPacket::Files::FileStream*)ptr;
    bool endOfField = false;
    std::vector<char> vec = stream->Read(buf_size, &endOfField);
    memcpy(buf, &vec[0], buf_size);
    if(endOfField)
        return AVERROR_EOF;

    return vec.size();
}

const static std::unordered_map<int,std::ios_base::seekdir> CustomFFmpegIOStreamSeekMap = {
    {SEEK_SET, std::ios_base::beg},
    {SEEK_CUR, std::ios_base::cur},
    {SEEK_END, std::ios_base::end},
};

int64_t CustomFFmpegIOStreamSeek(void* ptr, int64_t pos, int whence){
    TeaPacket::Files::FileStream* stream = (TeaPacket::Files::FileStream*)ptr;

    if(whence == AVSEEK_SIZE){
        size_t pos = stream->CurrentPosition();
        stream->Seek(std::ios_base::end);
        size_t size = stream->CurrentPosition();
        stream->Seek(pos);
        return size;
    }

    stream->Seek(pos, CustomFFmpegIOStreamSeekMap.at(whence));
    return stream->CurrentPosition();
}

TeaPacket::Graphics::VideoPlayer::VideoPlayer(const std::string path, Texture* texture):
texture(texture)
{
    customIOStream.internalBuffer = (unsigned char*)av_malloc(32*2*1024);
    customIOStream.fileStream.Open(path);
    customIOStream.avioContext = avio_alloc_context(
        customIOStream.internalBuffer,
        sizeof(customIOStream.internalBuffer), 
        0, 
        &customIOStream.fileStream,
        CustomFFmpegIOStreamRead,
        0,
        CustomFFmpegIOStreamSeek
    );

    formatContext = avformat_alloc_context();
    //formatContext->pb = customIOStream.avioContext;
    //formatContext->flags = AVFMT_FLAG_CUSTOM_IO;

    std::vector<char> data = customIOStream.fileStream.Read(sizeof(customIOStream.internalBuffer));
    TeaPacket::PrintLine("READ");
    TeaPacket::PrintLine((unsigned char)data[0]);
    TeaPacket::PrintLine((unsigned char)data[data.size()-1]);
    TeaPacket::PrintLine(data.size());
    customIOStream.fileStream.Seek(0, std::ios::beg);

    AVProbeData probeData;
    probeData.buf = customIOStream.internalBuffer;
    probeData.buf_size = sizeof(customIOStream.internalBuffer);
    probeData.filename = "";
    PrintLine("PROBE INPUT");
    //formatContext->iformat = av_probe_input_format(&probeData, 1);

    PrintLine("OPEN INPUT");
    int result = avformat_open_input(&formatContext, "file:fs:/vol/external01/wiiu/videotest.webm", NULL, NULL);
    if(result != 0){
        char infoLog[1024];
        PrintLine("Video failed to load:");
        av_strerror(result,infoLog,sizeof(infoLog));
        PrintLine(infoLog);
        return;
    }
    PrintLine("FIND STREAM INPUT");

    result = avformat_find_stream_info(formatContext, NULL);
    PrintLine("DONE FIND STREAM INPUT");
    if(result != 0){
        char infoLog[1024];
        PrintLine("Video failed to get stream info:");
        av_strerror(result,infoLog,sizeof(infoLog));
        PrintLine(infoLog);
        return;
    }

    PrintLine("FIND VIDEO STREAM");
    for(unsigned int i = 0; i < formatContext->nb_streams; i++){
        if(formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            streamID = i;
            break;
        }
    }
    if(streamID == -1){
        PrintLine("Failed to find video stream!");
        return;
    }
    PrintLine("ALLOC SHIT");
    stream = formatContext->streams[streamID];
    decoder = avcodec_find_decoder(formatContext->streams[streamID]->codecpar->codec_id);
    if(decoder == NULL){
        PrintLine("Failed to find decoder.");
        return;
    }
    codecContext = avcodec_alloc_context3(decoder);
    avcodec_parameters_to_context(codecContext, formatContext->streams[streamID]->codecpar);
    if(result != 0){
        char infoLog[1024];
        PrintLine("Couldn't copy codec context:");
        av_strerror(result,infoLog,sizeof(infoLog));
        PrintLine(infoLog);
        return;
    }
    PrintLine("OPEN");
    result = avcodec_open2(codecContext, decoder, NULL);
    if(result != 0){
        char infoLog[1024];
        PrintLine("Video failed to open codec:");
        av_strerror(result,infoLog,sizeof(infoLog));
        PrintLine(infoLog);
        return;
    }
    avPacket = av_packet_alloc();
    avFrame = av_frame_alloc();
    texFrame = av_frame_alloc();

    size_t size = av_image_get_buffer_size(AV_PIX_FMT_RGBA, codecContext->width, codecContext->height, 32);
    internalBuffer = (uint8_t*)av_malloc(size * sizeof(uint8_t));
    av_image_fill_arrays(texFrame->data, texFrame->linesize, internalBuffer, AV_PIX_FMT_RGBA, codecContext->width, codecContext->height, 32);

    swsContext = sws_getContext(codecContext->width, codecContext->height, codecContext->pix_fmt, codecContext->width, codecContext->height, AV_PIX_FMT_RGBA, SWS_BILINEAR, NULL, NULL, NULL);

    if(texture == nullptr){
        this->texture = new Texture(NULL, codecContext->width, codecContext->height, TEXTURE_FORMAT_RGBA8);
        textureOwnedBySelf = true;
    }
    PrintLine("VIDEO DONE LOAD");
}

void TeaPacket::Graphics::VideoPlayer::UpdateFrame(){
    bool foundFrame = false;
    while(av_read_frame(formatContext, avPacket) >= 0){
        if(avPacket->stream_index != streamID) { continue; }
        int result = avcodec_send_packet(codecContext, avPacket);
        if(result < 0){
            PrintLine("Error sending packet for decoding.");
            char infoLog[1024];
            av_strerror(result,infoLog,sizeof(infoLog));
            PrintLine(infoLog);
            return;
        }
        result = avcodec_receive_frame(codecContext, avFrame);
        if(result < 0){
            PrintLine("Error decoding.");
            char infoLog[1024];
            av_strerror(result,infoLog,sizeof(infoLog));
            PrintLine(infoLog);
            return;
        }
        foundFrame = true;
        break;
    }

    if(!foundFrame){
        PrintLine("NO FRAME FOUND!");
    }

    if(!foundFrame && loop){
        av_seek_frame(formatContext, streamID, 0, AVSEEK_FLAG_FRAME);
        UpdateFrame();
        return;
    }

    sws_scale(swsContext, avFrame->data, avFrame->linesize, 0, codecContext->height, texFrame->data, texFrame->linesize);
    texture->UpdateContents(texFrame->data[0]);
}

bool TeaPacket::Graphics::VideoPlayer::Tick(){
    UpdateFrame();
    return true;
}

TeaPacket::Graphics::VideoPlayer::~VideoPlayer(){

    av_packet_unref(avPacket);
    av_free(internalBuffer);
    av_frame_free(&texFrame);
    av_free(texFrame);
    av_frame_free(&avFrame);
    av_free(avFrame);
    avcodec_close(codecContext);
    avformat_close_input(&formatContext);


    //avformat_close_input(&formatContext);
    //avformat_free_context(formatContext);
    //avcodec_close(codecContext);
    //sws_freeContext(swsContext);
    //av_packet_unref(avPacket);
    //av_frame_free(&avFrame);
    //av_free(avFrame);
    //av_free(texFrame);
    //av_free(internalBuffer);
    av_free(customIOStream.avioContext);
    av_free(customIOStream.internalBuffer);

    if(textureOwnedBySelf) { delete texture; }
}

void FFmpegPrint(void* ptr, int level, const char* text, va_list vl){
    if(level <= AV_LOG_ERROR){
        TeaPacket::Print("ERROR: ");
    } else if(level <= AV_LOG_WARNING){
        TeaPacket::Print("WARNING: ");
    }
    char buffer[2048];
    vsnprintf(buffer, sizeof(buffer), text, vl);
    TeaPacket::Print(buffer);
}

int TeaPacket::Graphics::VideoPlayer::Init(){
    av_log_set_level(AV_LOG_DEBUG);
    av_log_set_callback(FFmpegPrint);
    return 1;
}