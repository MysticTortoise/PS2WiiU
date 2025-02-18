#ifdef TP_WIN
#include "TeaPacket/TeaPacket.hpp"
#include "TeaPacket/Video.hpp"

#include "TeaPacket/DebugMacros.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace TeaPacket;

GLFWwindow* window = nullptr;

int TeaPacket::Initialize(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

bool TeaPacket::ShouldRun(){
    return !glfwWindowShouldClose(window);
}

void TeaPacket::Delay(){}

void TeaPacket::Update(){
    glfwPollEvents();
}

void TeaPacket::DeInitialize(){
    glfwTerminate();
}





#endif