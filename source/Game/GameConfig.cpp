#include "TeaPacket/Video.hpp"
#include "TeaPacket/Graphics/Sprite.hpp"

#include "TeaPacket/Scene/SceneScript.hpp"

#include "Game/Scenes/TestScene.hpp"

using namespace TeaPacket;

TeaPacket::Scene::SceneScript* TeaPacket::Scene::currentScene = new PostShift2::TestScene();


int TeaPacket::Video::resolutionHeight = 720;
int TeaPacket::Video::resolutionWidth = 1280;
const char* TeaPacket::windowTitle = "Post-Shift 2";

Math::Vector2 TeaPacket::Graphics::renderScale(1280, 720);