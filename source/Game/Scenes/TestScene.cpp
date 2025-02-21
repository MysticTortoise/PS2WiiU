#include "Game/Scenes/TestScene.hpp"

#include "TeaPacket/DebugMacros.hpp"

#include <cmath>
using namespace TeaPacket;

void PostShift2::TestScene::Load(){
    testTex1 = new Graphics::Texture("test.png");
    testTex2 = new Graphics::Texture("test2.png");

    sprite1.texture = testTex1;
    sprite2.texture = testTex2;

    
    sprite1.position.y = 720/2;

    sprite2.position.x = 1280/2;
    sprite2.position.y = 720/4;
}

void PostShift2::TestScene::Update(){
    sprite1.position.x = (sin(sprite1.angle/20) * 1280/2) + 1280/2;
    sprite1.angle++;
}

void PostShift2::TestScene::Draw(){
    TeaPacket::Graphics::Sprite::BeginRenderFromCamera(&camera);
    sprite1.Draw();
    sprite2.Draw();
}

void PostShift2::TestScene::Deload(){
    delete testTex1;
    delete testTex2;
}