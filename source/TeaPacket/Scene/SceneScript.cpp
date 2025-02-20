#include "TeaPacket/Scene/SceneScript.hpp"

#include <stdexcept>

using namespace TeaPacket::Scene;

template<class T> 
T* TeaPacket::Scene::LoadScene(){
    static_assert(std::is_base_of<SceneScript,T>::value, "Attempt to load scene of a non-SceneScript type!");
    SceneScript* script = new T();
    script->Load();

    readiedScenes.push_back(script);
}

template<class T>
void TeaPacket::Scene::SetActiveScene(bool unloadOld){
    static_assert(std::is_base_of<SceneScript,T>::value, "Attempt to set active scene to a non-SceneScript type!");

    currentScene->Stop();
    if(unloadOld){
        currentScene->Deload();
        for(size_t i = 0; i < readiedScenes.size(); i++){
            if(readiedScenes[i] == currentScene){
                readiedScenes.erase(readiedScenes.begin() + i);
            }
        }
        delete currentScene;
    }
    currentScene = nullptr;

    for(SceneScript* scene : readiedScenes){
        if(dynamic_cast<T*>(scene) == nullptr) { continue; }
        currentScene = scene;
        return;
    }
    if(currentScene == nullptr){
        currentScene = LoadScene<T>();
    }
    currentScene->Start();
}


void TeaPacket::Scene::SceneScript::Load() {}
void TeaPacket::Scene::SceneScript::Start() {}
void TeaPacket::Scene::SceneScript::Update() {}
void TeaPacket::Scene::SceneScript::Draw() {}
void TeaPacket::Scene::SceneScript::Stop() {}
void TeaPacket::Scene::SceneScript::Deload() {}