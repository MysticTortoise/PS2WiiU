#pragma once
#ifdef TP_WIN

extern "C"{
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

#include "TeaPacket/Files/FileStream.hpp"

namespace TeaPacket::Graphics{

    class CustomFFmpegIOStream{
        public:
        TeaPacket::Files::FileStream fileStream;
        unsigned char* internalBuffer;
        AVIOContext* avioContext = nullptr;
    };

    class PlatformVideoPlayer{
        public:
        CustomFFmpegIOStream customIOStream;
        AVFormatContext* formatContext;
        AVCodecContext* codecContext;
        SwsContext* swsContext;

        AVStream* stream;
        const AVCodec* decoder;
        AVPacket* avPacket;

        AVFrame* avFrame;
        AVFrame* texFrame;
        uint8_t* internalBuffer;
        int streamID = -1;

        PlatformVideoPlayer(const std::string path);
    };
}
#endif