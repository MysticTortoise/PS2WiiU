#include "Game/Scenes/TestScene.hpp"

#include "TeaPacket/Logging.hpp"

#include <cmath>
using namespace TeaPacket;

void PostShift2::TestScene::Load(){
    testTex1 = Graphics::Texture::LoadFromFile("test.png", TeaPacket::Graphics::TEXTURE_FILTER_POINT);
    testTex2 = Graphics::Texture::LoadFromFile("test2.png");

    sprite1.texture = testTex1;
    sprite2.texture = testTex2;

    
    sprite1.position.y = 720/2;
    sprite1.position.y = 720/4;

    sprite2.position.x = 1280/2;
    sprite2.position.y = 720/4;

    sprite1.scale = Math::Vector2(4,4);

    camera.bgColor = Math::Vector4(1,0,0);
    sprite2.color.w = 0.5f;
}

void PostShift2::TestScene::Update(){
    sprite1.position.x = (sin(sprite1.angle/40) * 1280/4) + 1280/2;
    sprite1.angle += 0.1f;
}

void PostShift2::TestScene::Draw(int screenIndex){
    if(screenIndex == 1){return;}
    TeaPacket::Graphics::Sprite::BeginRenderFromCamera(&camera);
    
    sprite1.Draw();
    sprite2.Draw();
}

void PostShift2::TestScene::Deload(){
    delete testTex1;
    delete testTex2;
}