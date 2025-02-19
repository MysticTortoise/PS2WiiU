#ifdef TP_WIN
#include "TeaPacket/TeaPacket.hpp"
#include "TeaPacket/Video.hpp"

#include "TeaPacket/DebugMacros.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <filesystem>
#include "TeaPacket/Graphics/Sprite.hpp"
#include "TeaPacket/Graphics/Texture.hpp"

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
    #ifdef TP_DEBUG
        std::filesystem::current_path(std::filesystem::current_path().parent_path().append("assets"));
    #else
        std::filesystem::current_path(std::filesystem::current_path().append("assets"));
    #endif
}

int TeaPacket::Initialize(){
    if(GraphicsInit() == -1) { return -1; }
    FSInit();
    
    Graphics::Sprite::SpriteRendererInit();

    Graphics::Texture* tex = new Graphics::Texture("test.png");
    sprite = Graphics::Sprite(tex);

    return 1;
}

bool TeaPacket::ShouldRun(){
    return !glfwWindowShouldClose(window);
}

void TeaPacket::Delay(){}

void TeaPacket::Update(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    sprite.Draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TeaPacket::DeInitialize(){
    glfwTerminate();

    Graphics::Sprite::SpriteRendererDeInit();
}





#endif