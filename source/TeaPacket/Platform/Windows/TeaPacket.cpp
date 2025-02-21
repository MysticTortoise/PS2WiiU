#ifdef TP_WIN
#include "TeaPacket/TeaPacket.hpp"
#include "TeaPacket/Video.hpp"

#include "TeaPacket/DebugMacros.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <filesystem>
#include "TeaPacket/Scene/SceneScript.hpp"
#include "TeaPacket/Graphics/Sprite.hpp"

using namespace TeaPacket;

GLFWwindow* window = nullptr;

Graphics::Sprite sprite;

int GraphicsInit(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(TeaPacket::resolutionWidth, TeaPacket::resolutionHeight, windowTitle, NULL, NULL);
    if(window == NULL){
        ERROR("Failed to create window!");
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        ERROR("Failed to initialize GLAD!");
        return -1;
    }
    return 1;
}
void FSInit(){
    std::filesystem::current_path(std::filesystem::current_path().append("assets"));
}

int TeaPacket::Initialize(){
    if(GraphicsInit() == -1) { return -1; }
    FSInit();
    
    Graphics::Sprite::SpriteRendererInit();

    Scene::currentScene->Load();
    Scene::currentScene->Start();

    return 1;
}

bool TeaPacket::ShouldRun(){
    return !glfwWindowShouldClose(window);
}

void TeaPacket::Delay(){}

void TeaPacket::Update(){
    Scene::currentScene->Update();
    Scene::currentScene->Draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TeaPacket::DeInitialize(){
    glfwTerminate();

    Graphics::Sprite::SpriteRendererDeInit();
}





#endif