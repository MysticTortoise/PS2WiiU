// Implementing
#include "TeaPacket/TeaPacket.hpp"
// Header Dependencies
#include "TeaPacket/Graphics/Graphics.hpp"
#include "TeaPacket/Graphics/Sprite.hpp"
#include "TeaPacket/Files/Files.hpp"
#include "TeaPacket/Scene/SceneScript.hpp"

using namespace TeaPacket;

int TeaPacket::Initialize(){
    if(TeaPacket::Graphics::Init() < 0) { return -1; }
    if(TeaPacket::Files   ::Init() < 0) { return -1; }

    if(TeaPacket::Graphics::Sprite::Init() < 0) { return -1; }

    Scene::currentScene->Load();
    Scene::currentScene->Start();

    return 1;
}

void TeaPacket::Update(){
    Scene::currentScene->Update();
    TeaPacket::Graphics::BeginRender();
    Scene::currentScene->Draw();
    TeaPacket::Graphics::EndRender();
}

void TeaPacket::DeInitialize(){
    Scene::currentScene->Stop();
    Scene::currentScene->Deload();

    TeaPacket::Graphics::Sprite::DeInit();

    TeaPacket::Graphics::DeInit();
    TeaPacket::Files::DeInit();
}