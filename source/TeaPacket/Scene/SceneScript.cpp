#include "TeaPacket/Scene/SceneScript.hpp"

using namespace TeaPacket::Scene;

template<class T> T* TeaPacket::Scene::LoadScene(){
    SceneScript* script = new T();
    script->Load();

    readiedScenes.push_back(script);
}