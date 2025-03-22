#pragma once

#include "TeaPacket/Graphics/Texture.hpp"
#include "TeaPacket/Files/FileStream.hpp"

extern "C"{
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

#include <string>

namespace TeaPacket::Graphics{

    class CustomFFmpegIOStream{
        public:
        TeaPacket::Files::FileStream fileStream;
        unsigned char* internalBuffer;
        AVIOContext* avioContext = nullptr;
    };

    class VideoPlayer{
        public:
        Texture* texture;

        bool loop = false;


        VideoPlayer(const std::string path, Texture* texture = nullptr);
        ~VideoPlayer();

        void UpdateFrame();
        bool Tick();

        private:
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

        bool textureOwnedBySelf = false;

        public:
        static int Init();
        static void DeInit();


    };
}