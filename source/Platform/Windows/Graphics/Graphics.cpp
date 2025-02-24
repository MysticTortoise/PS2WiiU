#ifdef TP_WIN
// Implementing
#include "TeaPacket/Graphics/Graphics.hpp"
// TeaPacket Utilities
#include "TeaPacket/DebugMacros.hpp"
// External Libraries
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// Header Dependencies
#include "TeaPacket/Video.hpp"
#include "windows/Video.hpp"


int TeaPacket::Graphics::Init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    TeaPacket::Video::window = glfwCreateWindow(TeaPacket::Video::resolutionWidth, TeaPacket::Video::resolutionHeight, TeaPacket::Video::windowTitle, NULL, NULL);
    if(TeaPacket::Video::window == NULL){
        ERROR("Failed to create window!");
        return -1;
    }

    glfwMakeContextCurrent(TeaPacket::Video::window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        ERROR("Failed to initialize GLAD!");
        return -1;
    }
    return 1;
}

void TeaPacket::Graphics::DeInit(){
    glfwTerminate();
}

void TeaPacket::Graphics::BeginRender(){}

void TeaPacket::Graphics::BeginSecondScreenRender(){}

void TeaPacket::Graphics::EndRender(){
    glfwSwapBuffers(TeaPacket::Video::window);
    glfwPollEvents();
}

#endif