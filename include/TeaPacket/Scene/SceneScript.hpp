#pragma once

#include <vector>

namespace TeaPacket::Scene{
    class SceneScript{
        public:
        virtual void Load();
        virtual void Start();
        virtual void Update();
        virtual void Draw();
        virtual void Stop();
        virtual void Deload();
    };

    template <class T> T* LoadScene();
    std::vector<SceneScript*> readiedScenes = std::vector<SceneScript*>();
    SceneScript* currentScene;

    template <class T> 
    void SetActiveScene(bool unloadOld = true);
}