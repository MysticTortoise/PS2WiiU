#include "Game/Scenes/VideoTest.hpp"

#include "TeaPacket/Logging.hpp"

#include <cmath>
using namespace TeaPacket;
using namespace TeaPacket::Graphics;

extern "C"{
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}



void PostShift2::VideoTest::Load(){

    videoPlayer = new VideoPlayer("videotest.webm");

    sprite1.texture = videoPlayer->texture;

    
    sprite1.position.x = 1280/2;
    sprite1.position.y = 720/2;

    camera.bgColor = Math::Vector4(1,0,0);
}

#include "TeaPacket/Files/Files.hpp"
#include "stb/stb_image.h"
using namespace TeaPacket::Graphics;


void PostShift2::VideoTest::Update(){

}

void PostShift2::VideoTest::Draw(int screenIndex){
    if(screenIndex == 1){return;}
    TeaPacket::Graphics::Sprite::BeginRenderFromCamera(&camera);
    videoPlayer->UpdateFrame();
    sprite1.Draw();
}

void PostShift2::VideoTest::Deload(){
}