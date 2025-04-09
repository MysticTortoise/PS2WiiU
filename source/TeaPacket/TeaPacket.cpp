// Implementing
#include "TeaPacket/TeaPacket.hpp"
// Header Dependencies
#include "TeaPacket/Logging.hpp"
#include "TeaPacket/Graphics/Graphics.hpp"
#include "TeaPacket/Graphics/VideoPlayer.hpp"
#include "TeaPacket/Graphics/Sprite.hpp"
#include "TeaPacket/Files/Files.hpp"
#include "TeaPacket/Scene/SceneScript.hpp"

using namespace TeaPacket;

int TeaPacket::Initialize(){
    if(TeaPacket::       LogInit() < 0) { return -1; }
    if(TeaPacket::Files   ::Init() < 0) { return -1; }
    if(TeaPacket::Graphics::Init() < 0) { return -1; }
    if(TeaPacket::Graphics::VideoPlayer::Init() < 0) { return -1; }

    if(TeaPacket::Graphics::Sprite::Init() < 0) { return -1; }

    Scene::currentScene->Load();
    Scene::currentScene->Start();

    return 1;
}

void TeaPacket::Update(){
    Scene::currentScene->Update();
    TeaPacket::Graphics::BeginRender();
    Scene::currentScene->Draw(0);
    TeaPacket::Graphics::BeginSecondScreenRender();
    Scene::currentScene->Draw(1);
    TeaPacket::Graphics::EndRender();
}

void TeaPacket::DeInitialize(){
    Scene::currentScene->Stop();
    Scene::currentScene->Deload();

    TeaPacket::Graphics::Sprite::DeInit();

    TeaPacket::Graphics::DeInit();
    TeaPacket::Files::DeInit();
}